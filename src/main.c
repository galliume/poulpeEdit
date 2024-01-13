#include <gtk/gtk.h>

#include "defines.h"

#include "network/socket.h"

static void
activate(GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "PoulpeEdit");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_window_present(GTK_WINDOW(window));

  GtkWidget *view;
  GtkTextBuffer *buffer;
  char *text = user_data;

  view = gtk_text_view_new();
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
  gtk_text_buffer_set_text(buffer, text, -1);

  gtk_window_set_child(GTK_WINDOW(window), view);
}

int
main(int argc, char **argv)
{
  char* plpSocketMsg = "Server not connected";

  if (0 == socketCreate()) {
    plpSocketMsg = socketReceive();
  }

  GtkApplication *app;
  int gtkStatus;

  app = gtk_application_new("org.galliume", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(activate), plpSocketMsg);
  gtkStatus = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);


  socketClose();

  return gtkStatus;
}
