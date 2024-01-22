#include "application.h"

#include "core/logger.h"
#include "platform/platform.h"
#include "network/socket.h"
#include "views/window.h"

struct _PlpApplication
{
  GtkApplication parent;
  PlpWindow* win;
  GSettings *settings;
  GtkCssProvider *provider;
  platformState* platformState;
  platformSocket* engineSocket;
};

G_DEFINE_FINAL_TYPE(PlpApplication, plp_application, GTK_TYPE_APPLICATION)

static void
app_activate(GApplication* application)
{
  PlpApplication *app = PLP_APPLICATION(application);

  app->platformState = platform_allocate(sizeof(struct platformState));
  platform_startup(app->platformState);

  if ((app->engineSocket = platform_allocate(sizeof(struct platformSocket))) == NULL) {
    PLPFATAL("Error creating platformSocket\n");
  }

  gtk_label_set_text(GTK_LABEL(PLP_WINDOW(app->win)->socketStatusLabel), "Not connected");

  gtk_window_set_title(GTK_WINDOW(app->win), "PoulpeEdit");
  gtk_window_set_default_size(GTK_WINDOW(app->win), 800, 600);
  gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(app->win), TRUE);

  gtk_window_present(GTK_WINDOW(app->win));
}

static void
app_startup(GApplication* application)
{
  PlpApplication* app = PLP_APPLICATION(application);
  GtkCssProvider *provider = gtk_css_provider_new();
  GdkDisplay *display;

  G_APPLICATION_CLASS(plp_application_parent_class)->startup(application);

  app->win = PLP_WINDOW(plp_window_new(GTK_APPLICATION(app)));

  gtk_css_provider_load_from_file(provider, g_file_new_for_path("./assets/css/styles.css"));
  display = gdk_display_get_default();
  gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  g_object_unref(provider);
  gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(app->provider),
                                               GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  GSimpleAction *act_connect = g_simple_action_new("connect", NULL);
  g_signal_connect_swapped(act_connect, "activate", G_CALLBACK(socket_connect), app);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act_connect));

  GSimpleAction *act_quit = g_simple_action_new("quit", NULL);
  g_signal_connect_swapped(act_quit, "activate", G_CALLBACK(g_application_quit), app);
  g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(act_quit));

  g_signal_connect(app->win->btnReloadSkybox, "clicked", G_CALLBACK(reload_skybox), app);

  /*GtkWidget *image = gtk_picture_new_for_filename("./assets/mpoulpe.png");
  gtk_widget_set_name(image, "mrpoulpe");

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_append(GTK_BOX(box), image);*/

  //gtk_window_set_child(GTK_WINDOW(app->win), box);

  GMenu *menubar = g_menu_new();
  GMenuItem *menu_item_menu = g_menu_item_new("Menu", NULL);
  GMenu *menu = g_menu_new();
  GMenuItem *menu_item_connect = g_menu_item_new("Connect", "app.connect");
  g_menu_append_item(menu, menu_item_connect);
  g_object_unref(menu_item_connect);
  GMenuItem *menu_item_quit = g_menu_item_new("Quit", "app.quit");
  g_menu_append_item(menu, menu_item_quit);
  g_object_unref(menu_item_quit);
  g_menu_item_set_submenu(menu_item_menu, G_MENU_MODEL(menu));
  g_object_unref(menu);
  g_menu_append_item(menubar, menu_item_menu);
  g_object_unref(menu_item_menu);

  gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menubar));
}

static void
plp_application_init(PlpApplication *app)
{
  app->provider = gtk_css_provider_new();
}

static void
plp_application_dispose(GObject *gobject)
{
  PlpApplication *app = PLP_APPLICATION(gobject);

  platform_free(app->win);
  platform_free(app->platformState);

  //g_clear_object(&app->settings);
  g_clear_object(&app->provider);
  G_OBJECT_CLASS(plp_application_parent_class)->dispose(gobject);
}

static void
plp_application_class_init(PlpApplicationClass *class)
{
  G_OBJECT_CLASS(class)->dispose = plp_application_dispose;
  G_APPLICATION_CLASS(class)->startup = app_startup;
  G_APPLICATION_CLASS(class)->activate = app_activate;
}

PlpApplication *plp_application_new(const char* application_id, GApplicationFlags flag)
{
  PlpApplication* app = PLP_APPLICATION(g_object_new(PLP_TYPE_APPLICATION, "application-id", application_id, "flags", flag, NULL));
  return app;
}

static void
socket_connect(PlpApplication* app)
{
  char* msg;

  if (0 == socketCreate(app->engineSocket)) {
    msg = socketReceive(app->engineSocket);
  } else {
    msg = "Cannot connect to PoulpeEngine";
  }
  gtk_label_set_text(GTK_LABEL(app->win->socketStatusLabel), msg);
}

static void
reload_skybox(GtkButton* btn, gpointer user_data)
{
  PlpApplication* app = PLP_APPLICATION(user_data);

  socketSend(app->engineSocket);
}