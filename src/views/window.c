#include "window.h"

#include "core/logger.h"
#include "platform/platform.h"
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
  GtkWidget *body = gtk_grid_new();
  gtk_window_set_child(GTK_WINDOW(win), body);

  GtkWidget* frameTopLeft = gtk_frame_new(NULL);
  gtk_widget_set_name(frameTopLeft, "frameTopLeft");
  gtk_widget_set_halign(GTK_WIDGET(frameTopLeft), GTK_ALIGN_START);
  gtk_widget_set_vexpand(GTK_WIDGET(frameTopLeft), TRUE);
  gtk_grid_attach(GTK_GRID(body), frameTopLeft, 0, 0, 1, 1);

  GtkWidget *grid = gtk_grid_new();
  gtk_frame_set_child(GTK_FRAME(frameTopLeft), grid);

  GtkWidget* skyboxLabel = gtk_label_new("Skybox");
  gtk_grid_attach(GTK_GRID(grid), skyboxLabel, 0, 0, 1, 1);

  const char *initDropDown[2] = { "----------", NULL};
  win->skyboxDropDownModel = gtk_string_list_new((const char* const*) initDropDown);

  win->skyboxDropDown = gtk_drop_down_new(G_LIST_MODEL(win->skyboxDropDownModel), NULL);
  gtk_drop_down_set_selected(GTK_DROP_DOWN(win->skyboxDropDown), 0);

  gtk_grid_attach(GTK_GRID(grid), win->skyboxDropDown, 1, 0, 1, 1);

  GtkWidget* levelLabel = gtk_label_new("Level");
  gtk_grid_attach(GTK_GRID(grid), levelLabel, 0, 1, 1, 1);

  win->levelDropDownModel = gtk_string_list_new((const char* const*) initDropDown);

  win->levelDropDown = gtk_drop_down_new(G_LIST_MODEL(win->levelDropDownModel), NULL);
  gtk_drop_down_set_selected(GTK_DROP_DOWN(win->levelDropDown), 0);

  gtk_grid_attach(GTK_GRID(grid), win->levelDropDown, 1, 1, 1, 1);

  GtkWidget* frameTopRight = gtk_frame_new(NULL);
  gtk_widget_set_name(frameTopRight, "frameTopRight");
  gtk_widget_set_vexpand(GTK_WIDGET(frameTopRight), TRUE);
  gtk_widget_set_hexpand(GTK_WIDGET(frameTopRight), TRUE);
  gtk_widget_set_halign(GTK_WIDGET(frameTopRight), GTK_ALIGN_FILL);
  gtk_grid_attach(GTK_GRID(body), frameTopRight, 1, 0, 1, 1);

  GtkWidget* test = gtk_label_new("LevelMap");
  gtk_widget_set_halign(GTK_WIDGET(test), GTK_ALIGN_FILL);
  gtk_frame_set_child(GTK_FRAME(frameTopRight), test);

  //GtkWidget *image = gtk_picture_new_for_filename("./assets/mpoulpe.png");
  //gtk_widget_set_name(image, "mrpoulpe");
  //gtk_widget_set_halign(GTK_WIDGET(image), GTK_ALIGN_FILL);
  //gtk_frame_set_child(GTK_FRAME(frameTopRight), image);


  GtkWidget* tabsBottom = gtk_notebook_new();
  gtk_grid_attach(GTK_GRID(body), tabsBottom, 0, 1, 2, 1);

  GtkWidget* frameTextures = gtk_frame_new(NULL);
  gtk_widget_set_name(frameTextures, "frameTexture");

  GtkWidget* texturesTabLabel = gtk_label_new("Textures");

  gtk_notebook_insert_page(GTK_NOTEBOOK(tabsBottom), GTK_WIDGET(frameTextures), GTK_WIDGET(texturesTabLabel), 0);

  GtkWidget* frameSound = gtk_frame_new(NULL);
  gtk_widget_set_name(frameSound, "frameSound");

  GtkWidget* soundTabLabel = gtk_label_new("Sound");

  gtk_notebook_insert_page(GTK_NOTEBOOK(tabsBottom), GTK_WIDGET(frameSound), GTK_WIDGET(soundTabLabel), 1);

  GtkWidget* frameBottom = gtk_frame_new(NULL);
  gtk_widget_set_name(frameBottom, "frameBottom");
  gtk_grid_attach(GTK_GRID(body), frameBottom, 0, 2, 2, 1);

  GtkWidget *footer = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_widget_set_name(footer, "status_footer");
  gtk_box_set_baseline_position(GTK_BOX(footer), GTK_BASELINE_POSITION_BOTTOM);
  gtk_frame_set_child(GTK_FRAME(frameBottom), footer);

  win->socketStatusLabel = gtk_label_new("Not connected");
  gtk_widget_set_name(win->socketStatusLabel, "socket_status_label");
  gtk_box_append(GTK_BOX(footer), win->socketStatusLabel);
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
