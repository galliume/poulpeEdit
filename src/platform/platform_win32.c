#include "core/logger.h"

#include "platform/platform.h"

#include <Windows.h>

#if PLPPLATFORM_WINDOWS

typedef struct internalState {

} state;

static f64 clockFrequency;
static LARGE_INTEGER startTime;

//LRESULT CALLBACK win32ProcessMessage(HWND hwnd, u32 msg, WPARAM wParam, LPARAM lParam);
void platform_startup(
  platformState* platformState,
  char const* name,
  i32 x,
  i32 y,
  i32 width,
  i32 heihgt
)
{
  //platformState->state = platformAllocate(sizeof(struct internalState));
  //struct internalState* state = (struct internalState*)platformState->state;

  LARGE_INTEGER frequency;
  QueryPerformanceCounter(&startTime);
  clockFrequency = 1.0 / (f64)frequency.QuadPart;
  QueryPerformanceCounter(&startTime);
}

void platform_shutdown(platformState* platformState)
{
  if (platformState->app)
  {
    g_object_unref(platformState->app);
  }
}

void *platform_allocate(u64 size)
{
  return malloc(size);
}

void platform_free(void* memory)
{
  free(memory);
}

void *platform_zero_memory(void* memory, u64 size)
{
  //@todo switch to _s ?
  return memset(memory, 0, size);
}

void *platform_copy_memory(void* dest, void const* source, u64 size)
{
  return memcpy(dest, source, size);
}

void *platform_set_memory(void* dest, i32 value, u64 size)
{
  return memset(dest, value, size);
}

void platform_console_write(char const* message, u8 color)
{
  HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
  static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };//color indexed with lvl error index
  SetConsoleTextAttribute(consoleHandler, levels[color]);

  OutputDebugStringA(message);//output to "output" window on VS
  u64 length = strlen(message);
  LPDWORD sizeWritten = 0;
  WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, sizeWritten, 0);
}

void platform_console_write_error(char const* message, u8 color)
{
  HANDLE consoleHandler = GetStdHandle(STD_ERROR_HANDLE);
  static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };//color indexed with lvl error index
  SetConsoleTextAttribute(consoleHandler, levels[color]);

  OutputDebugStringA(message);//output to "output" window on VS
  u64 length = strlen(message);
  LPDWORD sizeWritten = 0;
  WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, sizeWritten, 0);
}

f64 platform_get_aboslute_time()
{
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (f64) now.QuadPart * clockFrequency;
}

void platform_sleep(i32 time)
{
  DWORD ms = time;
  Sleep(ms);
}
//LRESULT CALLBACK win32ProcessMessage(HWND hwnd, u32 msg, WPARAM wParam, LPARAM lParam)
//{
//  switch (msg) {
//  case WM_ERASEBKGND:
//    return 1;
//  case WM_CLOSE:
//    return 0;
//  case WM_DESTROY:
//    PostQuitMessage(0);
//    return 0;
//  //case WM_SIZE: {
//  //  RECT r;
//  //  GetClientRect(hwnd, &r);
//  //  u32 with = r.right - r.let;
//  //  u32 height = r.bottom - r.top;
//  //}break;
//  }
//
//  return DefWindowProcA(hwnd, msg, wParam, lParam);
//}


#endif