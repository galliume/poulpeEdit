#pragma once

#include <gtk/gtk.h>

#include "defines.h"
#include "views/application.h"

typedef struct platformState {
  void* state;
  PlpApplication* app;
  i32 status;
} platformState;

void platformStartup(
  platformState* platformState,
  char const * name,
  i32 x,
  i32 y,
  i32 width,
  i32 heihgt
);

void platformShutdown(platformState* platformState);
void *platformAllocate(u64 size);
void platformFree(void* memory);
void *platformZeroMemory(void* memory, u64 size);
void *platformCopyMemory(void* dest, void const * source, u64 size);
void *platformSetMemory(void * dest, i32 value, u64 size);
void platformConsoleWrite(char const* message, u8 color);
void platformConsoleWriteError(char const* message, u8 color);
f64 platformGetAbosluteTime();

//GTK callbacks
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
static void startup(void);
static void activate(GtkApplication* app, gpointer user_data);
#pragma clang diagnostic pop