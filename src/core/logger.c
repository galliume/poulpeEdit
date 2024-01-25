#include "logger.h"

//@todo tmp
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "platform/platform.h"

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

  b8 isError = level < LOG_LEVEL_WARN;

  //@todo tmp
  const i32 msgLength = 32000;
  char msg[msgLength];
  memset(msg, 0, sizeof(msg));

  __builtin_va_list argptr;
  va_start(argptr, message);
  vsnprintf(msg, msgLength, message, argptr);
  va_end(argptr);

  char output[msgLength];
  sprintf(output, "%s%s\n", levelString[level], msg);

  if (isError) {
    platform_console_write_error(output, level);
  } else {
    platform_console_write(output, level);
  }
}