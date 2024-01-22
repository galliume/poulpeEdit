#include "window.h"

#include "core/logger.h"
#include "network/socket.h"

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
  GtkWidget *body = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_window_set_child(GTK_WINDOW(win), body);

  GtkWidget* frameTop = gtk_frame_new(NULL);
  gtk_widget_set_name(frameTop, "frameTop");
  gtk_widget_set_vexpand(frameTop, TRUE);
  gtk_box_append(GTK_BOX(body), frameTop);

  GtkWidget *boxv = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_frame_set_child(GTK_FRAME(frameTop), boxv);

  GtkWidget* reloadSkyboxLabel = gtk_label_new("Load Skybox");
  gtk_widget_set_name(win->socketStatusLabel, "load_skybox_status_label");

  win->btnReloadSkybox = gtk_button_new_with_label("Load bluesky skybox");

  gtk_box_append(GTK_BOX(boxv), reloadSkyboxLabel);
  gtk_box_append(GTK_BOX(boxv), win->btnReloadSkybox);

  GtkWidget* frameBottom = gtk_frame_new(NULL);
  gtk_widget_set_name(frameBottom, "frameBottom");
  gtk_box_append(GTK_BOX(body), frameBottom);

  GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_name(footer, "status_footer");
  gtk_box_set_baseline_position(GTK_BOX(footer), GTK_BASELINE_POSITION_BOTTOM);

  win->socketStatusLabel = gtk_label_new("Not connected");
  gtk_widget_set_name(win->socketStatusLabel, "socket_status_label");

  gtk_box_append(GTK_BOX(footer), win->socketStatusLabel);

  gtk_frame_set_child(GTK_FRAME(frameBottom), footer);
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
