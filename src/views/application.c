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
};

G_DEFINE_FINAL_TYPE(PlpApplication, plp_application, GTK_TYPE_APPLICATION)

static void
app_activate(GApplication* application)
{
  struct platformSocket platformSocket;
  socketCreate(&platformSocket);

  char* msg = socketReceive(&platformSocket);
  socketClose(&platformSocket);

  PlpApplication *app = PLP_APPLICATION(application);
  gtk_text_buffer_set_text(PLP_WINDOW(app->win)->socketStatusBuffer, msg, -1);
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

  gtk_window_present(GTK_WINDOW(app->win));
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