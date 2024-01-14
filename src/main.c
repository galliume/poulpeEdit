#include <gtk/gtk.h>

#include "defines.h"

#include "network/socket.h"
#include "core/logger.h"

//#if PLPPLATFORM_WINDOWS == 1
//int WINAPI handler(DWORD dwCtrlType)
//{
//  if (CTRL_C_EVENT == dwCtrlType)
//  {
//    PLPTRACE("on exit");
//  }
//  return 0;
//}
//#endif

int
main(int argc, char **argv)
{
  PLPFATAL("fatal %f", 1.2f);
  PLPERR("err %f", 1.2f);
  PLPWARN("warn %f", 1.2f);
  PLPINFO("info %f", 1.2f);
  PLPDEBUG("debug %f", 1.2f);
  PLPTRACE("trace %f", 1.2f);
//#if PLPPLATFORM_WINDOWS == 1
//  SetConsoleCtrlHandler(handler, 1);
//#endif

  //char* plpSocketMsg = "Server not connected";

  //if (0 == socketCreate()) {
  //  plpSocketMsg = socketReceive();
  //}


  //socketClose();

  return 0;
}
