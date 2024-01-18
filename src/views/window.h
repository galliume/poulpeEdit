#pragma once

#include <gtk/gtk.h>

#define PLP_TYPE_WINDOW plp_window_get_type()
G_DECLARE_FINAL_TYPE(PlpWindow, plp_window, PLP, WINDOW, GtkApplicationWindow)

GtkWidget * plp_window_new(GtkApplication *app);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
static void plp_window_dispose(GObject* gobject);
static void plp_window_init(PlpWindow* win);

#pragma clang diagnostic pop
