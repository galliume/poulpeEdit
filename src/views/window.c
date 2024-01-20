#include "window.h"

#include "core/logger.h"

G_DEFINE_FINAL_TYPE(PlpWindow, plp_window, GTK_TYPE_APPLICATION_WINDOW)

static void
plp_window_dispose(GObject *gobject)
{
  gtk_widget_dispose_template(GTK_WIDGET(gobject), PLP_TYPE_WINDOW);
  G_OBJECT_CLASS(plp_window_parent_class)->dispose(gobject);
}

static void
socket_buffer_modified_changed(GtkWidget* view, gpointer user_data)
{
  GtkWidget* tv = GTK_WIDGET(view);

  GtkTextBuffer *tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
  GtkTextIter start_iter;
  GtkTextIter end_iter;
  char *contents;

  gtk_text_buffer_get_bounds(tb, &start_iter, &end_iter);
  contents = gtk_text_buffer_get_text(tb, &start_iter, &end_iter, FALSE);

  PLPTRACE("%s:%s", "tb modif", contents);
}

static void
plp_window_init(PlpWindow *win)
{
  win->socketStatusBuffer = gtk_text_buffer_new(NULL);
  gtk_text_buffer_set_text(win->socketStatusBuffer, "socket status", -1);

  gtk_window_set_title(GTK_WINDOW(win), "PoulpeEdit");
  gtk_window_set_default_size(GTK_WINDOW(win), 800, 600);
  gtk_application_window_set_show_menubar(GTK_APPLICATION_WINDOW(win), TRUE);

  GtkWidget *view;
  view = gtk_text_view_new();
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view), win->socketStatusBuffer);
  gtk_widget_set_name(view, "socket_status");
  gtk_window_set_child(GTK_WINDOW(win), view);

  g_signal_connect(win->socketStatusBuffer, "modified-changed", G_CALLBACK(socket_buffer_modified_changed), view);
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

void update(char const* msg)
{

}
