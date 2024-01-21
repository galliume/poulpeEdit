#pragma once

#include <gtk/gtk.h>

#include "defines.h"
#include "views/application.h"

typedef struct platformState {
  void* state;
  i32 status;
} platformState;

void platform_startup(platformState* platformState);

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
