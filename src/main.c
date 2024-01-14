#include <gtk/gtk.h>
#include <Windows.h>
#include "defines.h"

#include "core/logger.h"

#include "platform/platform.h"

#include "network/socket.h"

extern GtkTextBuffer *socketStatusBuffer;

int
main(int argc, char **argv)
{
  struct platformSocket platformSocket;
  socketCreate(&platformSocket);
  
  DWORD ms = 1000;
  Sleep(ms);

  char* msg = socketReceive(&platformSocket);
  socketClose(&platformSocket);

  struct platformState platformState;
  platformStartup(&platformState, "PoulpeEdit", 100, 100, 1280, 720);

  gtk_text_buffer_set_text(socketStatusBuffer, msg, -1);

  g_application_run(G_APPLICATION(platformState.app), 0, NULL);
  platformShutdown(&platformState);

  return 0;
}
