#include <gtk/gtk.h>
#include <Windows.h>
#include "defines.h"

#include "core/logger.h"
#include "platform/platform.h"
#include "network/socket.h"
#include "views/application.h"

extern GtkTextBuffer *socketStatusBuffer;

int
main(int argc, char **argv)
{
  // struct platformSocket platformSocket;
  // socketCreate(&platformSocket);
  
  // DWORD ms = 1000;
  // Sleep(ms);

  // char* msg = socketReceive(&platformSocket);
  // socketClose(&platformSocket);

  // PLPTRACE("Server status %s", msg);
  struct platformState platformState;
  platformStartup(&platformState, "PoulpeEdit", 100, 100, 1280, 720);

  platformState.app = plp_application_new("org.galliume.plpedit", G_APPLICATION_DEFAULT_FLAGS);

  //gtk_text_buffer_set_text(socketStatusBuffer, "yay", -1);

  g_application_run(G_APPLICATION(platformState.app), 0, NULL);
  platformShutdown(&platformState);

  return 0;
}
