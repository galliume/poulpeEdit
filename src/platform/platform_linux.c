#include "platform/platform.h"

//@todo implement linux
#if PLPPLATFORM_LINUX

void platformStartup(
  platformState* platformState,
  char const* name,
  i32 x,
  i32 y,
  i32 width,
  i32 heihgt
)
{

}

void platformShutdown(platformState* platformState)
{

}

void* platformAllocate(u64 size)
{
  return 0;
}

void platformFree(void* memory)
{

}

void* platformZeroMemory(void* memory, u64 size)
{
  return 0;
}

void* platformCopyMemory(void* dest, void const* source, u64 size)
{
  return 0;
}

void* platformSetMemory(void * dest, i32 value, u64 size)
{
  return 0;
}

void platformConsoleWrite(char const* message, u8 color)
{

}

void platformConsoleWriteError(char const* message, u8 color)
{

}

f64 platformGetAbosluteTime()
{
  return 0;
}

#endif
