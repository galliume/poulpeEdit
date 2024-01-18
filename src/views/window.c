#include "window.h"

struct _PlpWindow {
  GtkApplicationWindow parent;

};

G_DEFINE_FINAL_TYPE(PlpWindow, plp_window, GTK_TYPE_WINDOW)

static void
plp_window_dispose(GObject *gobject)
{
  gtk_widget_dispose_template(GTK_WIDGET(gobject), PLP_TYPE_WINDOW);
  G_OBJECT_CLASS(plp_window_parent_class)->dispose(gobject);
}

static void
plp_window_init(PlpWindow *win)
{

}

static void
plp_window_class_init(PlpWindowClass *class)
{
  GObjectClass *object_class = G_OBJECT_CLASS(class);
  object_class->dispose = plp_window_dispose;
}

GtkWidget *
plp_window_new(GtkApplication *app)
{
  return GTK_WIDGET(g_object_new(PLP_TYPE_WINDOW, "application", app, NULL));
}
