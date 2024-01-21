#include "platform/platform.h"

//@todo implement linux
#if PLPPLATFORM_LINUX

void platform_startup(platformState* platformState)
{

}

void platform_shutdown(platformState* platformState)
{

}

void* platform_allocate(u64 size)
{
  return 0;
}

void platform_free(void* memory)
{

}

void* platform_zero_memory(void* memory, u64 size)
{
  return 0;
}

void* platform_copy_memory(void* dest, void const* source, u64 size)
{
  return 0;
}

void* platform_set_memory(void * dest, i32 value, u64 size)
{
  return 0;
}

void platform_console_write(char const* message, u8 color)
{

}

void platform_console_write_error(char const* message, u8 color)
{

}

f64 platform_get_aboslute_time()
{
  return 0;
}

void platform_sleep(i32 time)
{

}

#endif
