#pragma once

#include <gtk/gtk.h>

struct _PlpWindow {
  GtkApplicationWindow parent;
  GtkWidget* socketStatusLabel;
  GtkWidget* skyboxDropDown;
  GtkStringList* skyboxDropDownModel;
  GtkWidget* levelDropDown;
  GtkStringList* levelDropDownModel;
};

#define PLP_TYPE_WINDOW plp_window_get_type()
G_DECLARE_FINAL_TYPE(PlpWindow, plp_window, PLP, WINDOW, GtkApplicationWindow)

GtkWidget * plp_window_new(GtkApplication *app);

extern void socket_buffer_modified_changed(GtkWidget* view, gpointer user_data);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
static void plp_window_dispose(GObject* gobject);
static void plp_window_init(PlpWindow* win);

#pragma clang diagnostic pop