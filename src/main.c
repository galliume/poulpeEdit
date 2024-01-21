#include <gtk/gtk.h>

#include "defines.h"

#include "core/logger.h"
#include "views/application.h"
#include "views/window.h"

//@todo remove #pragma clang diagnostic push

int
main(int argc, char **argv)
{
  PlpApplication* app = plp_application_new("org.galliume.plpedit", G_APPLICATION_DEFAULT_FLAGS);
  g_application_run(G_APPLICATION(app), 0, NULL);

  return 0;
}
