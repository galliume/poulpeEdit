#pragma once

#include "defines.h"

typedef struct platform_socket {
  void* pimpl;
} platform_socket;

i32 socketCreate(void);
char* socketReceive(void);
void socketClose(void);
