//@todo tmp
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "logger.h"

b8 initialize_logging()
{
  //@todo create log file
  return 1;
}

void shutdown_logging()
{
  //@todo cleanup
}

void logOutput(enum logLevel level, char const* message, ...)
{
  const char* levelString[6] = { "[FATAL]:", "[ERROR]:", "[WARN]:", "[INFO]:", "[DEBUG]:", "[TRACE]:" };

  //b8 isError = level < 2;

  //@todo tmp
  char msg[32000];
  memset(msg, 0, sizeof(msg));

  __builtin_va_list argptr;
  va_start(argptr, message);
  vsnprintf(msg, 32000, message, argptr);
  va_end(argptr);

  char output[32000];
  sprintf(output, "%s%s\n", levelString[level], msg);

  //@todo platform specific output
  //add date
  printf("%s", output);
}