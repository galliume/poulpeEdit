#pragma once

#include <gtk/gtk.h>

#define PLP_TYPE_APPLICATION plp_application_get_type()
G_DECLARE_FINAL_TYPE(PlpApplication, plp_application, PLP, APPLICATION, GtkApplication)

PlpApplication * plp_application_new(const char* application_id, GApplicationFlags flag);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
static void plp_application_init(PlpApplication *app);
static void app_startup(GApplication* application);
static void app_activate(GApplication* application);
static void socket_connect(PlpApplication* app);
static void reload(char const* fn, GtkWidget* dropDown, PlpApplication* app);
static void reload_skybox(GtkWidget* dropDown, gpointer user_data, PlpApplication* app);
static void reload_level(GtkWidget* dropDown, gpointer user_data, PlpApplication* app);
#pragma clang diagnostic pop