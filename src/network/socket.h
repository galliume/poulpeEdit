#pragma once

#include "defines.h"

typedef struct platformSocket {
  void* state;
} platformSocket;

i32 socketCreate(platformSocket* platformSocket);
char* socketReceive(platformSocket* platformSocket);
void socketClose(platformSocket* platformSocket);
