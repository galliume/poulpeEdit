#include "platform/platform.h"

#include <Windows.h>

#if PLPPLATFORM_WINDOWS

typedef struct internalState {

} state;

static f64 clockFrequency;
static LARGE_INTEGER startTime;

GtkTextBuffer *socketStatusBuffer;

//LRESULT CALLBACK win32ProcessMessage(HWND hwnd, u32 msg, WPARAM wParam, LPARAM lParam);
void platformStartup(
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

  socketStatusBuffer = gtk_text_buffer_new(NULL);

  platformState->app = gtk_application_new("org.galliume", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(platformState->app, "activate", G_CALLBACK(activate), platformState);

  LARGE_INTEGER frequency;
  QueryPerformanceCounter(&startTime);
  clockFrequency = 1.0 / (f64)frequency.QuadPart;
  QueryPerformanceCounter(&startTime);
}

void platformShutdown(platformState* platformState)
{
  if (platformState->app)
  {
    g_object_unref(platformState->app);
  }
}

void *platformAllocate(u64 size)
{
  return malloc(size);
}

void platformFree(void* memory)
{
  free(memory);
}

void *platformZeroMemory(void* memory, u64 size)
{
  //@todo switch to _s ?
  return memset(memory, 0, size);
}

void *platformCopyMemory(void* dest, void const* source, u64 size)
{
  return memcpy(dest, source, size);
}

void *platformSetMemory(void* dest, i32 value, u64 size)
{
  return memset(dest, value, size);
}

void platformConsoleWrite(char const* message, u8 color)
{
  HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);
  static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };//color indexed with lvl error index
  SetConsoleTextAttribute(consoleHandler, levels[color]);

  OutputDebugStringA(message);//output to "output" window on VS
  u64 length = strlen(message);
  LPDWORD sizeWritten = 0;
  WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, (DWORD)length, sizeWritten, 0);
}

void platformConsoleWriteError(char const* message, u8 color)
{
  HANDLE consoleHandler = GetStdHandle(STD_ERROR_HANDLE);
  static u8 levels[6] = { 64, 4, 6, 2, 1, 8 };//color indexed with lvl error index
  SetConsoleTextAttribute(consoleHandler, levels[color]);

  OutputDebugStringA(message);//output to "output" window on VS
  u64 length = strlen(message);
  LPDWORD sizeWritten = 0;
  WriteConsoleA(GetStdHandle(STD_ERROR_HANDLE), message, (DWORD)length, sizeWritten, 0);
}

f64 platformGetAbosluteTime()
{
  LARGE_INTEGER now;
  QueryPerformanceCounter(&now);
  return (f64) now.QuadPart * clockFrequency;
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

static void
activate(GtkApplication* app, gpointer data)
{
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "PoulpeEdit");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_window_present(GTK_WINDOW(window));

  GtkWidget *view;
  view = gtk_text_view_new();
  gtk_text_view_set_buffer(GTK_TEXT_VIEW(view), socketStatusBuffer);
  gtk_widget_set_name(view, "socket_status");

  gtk_window_set_child(GTK_WINDOW(window), view);
}

#endif