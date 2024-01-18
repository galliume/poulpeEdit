#include "application.h"
#include "window.h"

#include "core/logger.h"

struct _PlpApplication {
  GtkApplication parent;
  PlpWindow *win;
  GSettings *settings;
  GtkCssProvider *provider;
};

G_DEFINE_FINAL_TYPE(PlpApplication, plp_application, GTK_TYPE_APPLICATION)

static void
app_activate(GApplication* application)
{
  PlpApplication *app = PLP_APPLICATION(application);

  GtkWidget *window;
  GtkTextBuffer* socketStatusBuffer = gtk_text_buffer_new(NULL);
  gtk_text_buffer_set_text(socketStatusBuffer, "socket status", -1);

  window = gtk_application_window_new(&app->parent);
  gtk_window_set_title(GTK_WINDOW(window), "PoulpeEdit");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(window), TRUE);

  GtkWidget *view;
  view = gtk_text_view_new();
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view), socketStatusBuffer);
  gtk_widget_set_name(view, "socket_status");
  gtk_window_set_child(GTK_WINDOW(window), view);
  gtk_window_present(GTK_WINDOW(app->win));
}

static void
app_startup(GApplication* application)
{
  PlpApplication *app = PLP_APPLICATION(application);
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
  //GtkApplication *app = GTK_APPLICATION(application);

  //GSimpleAction *actionQuit = g_simple_action_new("quit", NULL);
  //g_action_map_add_action(G_ACTION_MAP(app), G_ACTION(actionQuit));

  //GMenu* menu = g_menu_new();
  //GMenuItem* quit = g_menu_item_new("Quit", "app.quit");
  //g_menu_append_item(menu, quit);
  //g_object_unref(quit);

  //gtk_application_set_menubar(GTK_APPLICATION(app), G_MENU_MODEL(menu));
}

static void
plp_application_init(PlpApplication *app) {
  //app->settings = g_settings_new("com.github.galliume.plpedit");
  //g_signal_connect(app->settings, "changed::font-desc", G_CALLBACK(changed_font_cb), app);

  //GtkCssProvider* cssProvider = gtk_css_provider_new();
  //gtk_css_provider_load_from_file(cssProvider, g_file_new_for_path("./assets/css/styles.css"));

  //app->provider = cssProvider;
}

static void
app_open(GApplication* application, GFile** files, gint n_files, const gchar* hint) {
  PlpApplication *app = PLP_APPLICATION(application);

  gtk_window_present(GTK_WINDOW(app->win));
}

static void
plp_application_dispose(GObject *gobject) {
  PlpApplication *app = PLP_APPLICATION(gobject);

  //g_clear_object(&app->settings);
  g_clear_object(&app->provider);
  G_OBJECT_CLASS(plp_application_parent_class)->dispose(gobject);
}

static void
plp_application_class_init(PlpApplicationClass *class) {
  G_OBJECT_CLASS(class)->dispose = plp_application_dispose;
  G_APPLICATION_CLASS(class)->startup = app_startup;
  G_APPLICATION_CLASS(class)->activate = app_activate;
  G_APPLICATION_CLASS(class)->open = app_open;
}

PlpApplication *plp_application_new(const char* application_id, GApplicationFlags flag) {
  PlpApplication* app = PLP_APPLICATION(g_object_new(PLP_TYPE_APPLICATION, "application-id", application_id, "flags", flag, NULL));
  return app;
}