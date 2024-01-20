#pragma once

#include <gtk/gtk.h>

#include "defines.h"
#include "views/application.h"

typedef struct platformState {
  void* state;
  PlpApplication* app;
  i32 status;
} platformState;

void platform_startup(
  platformState* platformState,
  char const * name,
  i32 x,
  i32 y,
  i32 width,
  i32 heihgt
);

void platform_shutdown(platformState* platformState);
void *platform_allocate(u64 size);
void platform_free(void* memory);
void *platform_zero_memory(void* memory, u64 size);
void *platform_copy_memory(void* dest, void const * source, u64 size);
void *platform_set_memory(void * dest, i32 value, u64 size);
void platform_console_write(char const* message, u8 color);
void platform_console_write_error(char const* message, u8 color);
f64 platform_get_aboslute_time(void);
void platform_sleep(i32 time);

//GTK callbacks
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
static void startup(void);
static void activate(GtkApplication* app, gpointer user_data);
#pragma clang diagnostic pop