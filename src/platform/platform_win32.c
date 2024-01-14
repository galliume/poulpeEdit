#include "platform/platform.h"

#include <Windows.h>

#if PLPPLATFORM_WINDOWS

typedef struct internalState {
  GtkApplication* app;
  i32 status;
} state;

static f64 clockFrequency;
static LARGE_INTEGER startTime;

//LRESULT CALLBACK win32ProcessMessage(HWND hwnd, u32 msg, WPARAM wParam, LPARAM lParam);

b8 platformStartup(
  platformState* platformState,
  char const* name,
  i32 x,
  i32 y,
  i32 width,
  i32 heihgt
)
{
  platformState->state = malloc(sizeof(struct internalState));
  struct internalState* state = (struct internalState*)platformState->state;

  state->app = gtk_application_new("org.galliume", G_APPLICATION_DEFAULT_FLAGS);
  state->status = g_application_run(G_APPLICATION(state->app), 0, NULL);

  platformState->state = state;
  
  LARGE_INTEGER frequency;
  QueryPerformanceCounter(&startTime);
  clockFrequency = 1.0 / (f64)frequency.QuadPart;
  QueryPerformanceCounter(&startTime);

  g_signal_connect(state->app, "activate", G_CALLBACK(activate), NULL);
  g_signal_connect(state->app, "destroy", G_CALLBACK(quitApp), &state);

  return TRUE;
}

void platformShutdown(platformState* platformState)
{
  struct internalState* state = (struct internalState*) platformState->state;

  if (state->app)
  {
    g_object_unref(state->app);
    state->app = 0;
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
  return memset(dest, 0, size);
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

static void quitApp(GtkWidget *widget, gpointer data)
{
  struct platformState* platformState = (struct platformState*)data;
  platformShutdown(platformState);
}

static void
activate(GtkApplication* app, gpointer user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "PoulpeEdit");
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
  gtk_window_present(GTK_WINDOW(window));

  GtkWidget *view;
  GtkTextBuffer *buffer;
  char *text = user_data;

  view = gtk_text_view_new();
  buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
  gtk_text_buffer_set_text(buffer, text, -1);

  gtk_window_set_child(GTK_WINDOW(window), view);
}

#endif