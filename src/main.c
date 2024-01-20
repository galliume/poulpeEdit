#include <gtk/gtk.h>

#include "defines.h"

#include "core/logger.h"
#include "platform/platform.h"
#include "views/application.h"
#include "views/window.h"

int
main(int argc, char **argv)
{
  struct platformState platformState;
  platform_startup(&platformState, "PoulpeEdit", 100, 100, 1280, 720);
  platformState.app = plp_application_new("org.galliume.plpedit", G_APPLICATION_DEFAULT_FLAGS);

  g_application_run(G_APPLICATION(platformState.app), 0, NULL);

  platform_shutdown(&platformState);

  return 0;
}
