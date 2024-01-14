#include <stdio.h>
#include <errno.h>

#include "defines.h"
#include "core/logger.h"
#include "platform/platform.h"
#include "network/socket.h"

//@todo implement linux
#if PLPPLATFORM_LINUX

i32 socketCreate(platformSocket* platformSocket)
{
  return 0;
}

char* socketReceive(platformSocket* platformSocket)
{
  return 0;
}

void socketClose(platformSocket* platformSocket)
{

}

#endif
