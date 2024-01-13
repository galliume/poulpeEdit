#pragma once

#include "defines.h"

#define PLP_LOG_WARN_ENABLED 1
#define PLP_LOG_INFO_ENABLED 1
#define PLP_LOG_DEBUG_ENABLED 1
#define PLP_LOG_TRACE_ENABLED 1

//#if PLP_RELEASE == 1
//#define PLP_LOG_DEBUG_ENABLED 0
//#define PLP_LOG_TRACE_ENABLED 0
//#endif

typedef enum logLevel {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 1,
  LOG_LEVEL_WARN = 2,
  LOG_LEVEL_INFO = 3,
  LOG_LEVEL_DEBUG = 4,
  LOG_LEVEL_TRACE = 5,
} plpLogLevel;

b8 initialize_logging();
void shutdown_logging();

void logOutput(enum logLevel level, char const* message, ...);

#define PLPFATAL(message, ...) logOutput(LOG_LEVEL_FATAL, message, ##__VA_ARGS__);
#define PLPERR(message, ...) logOutput(LOG_LEVEL_ERROR, message, ##__VA_ARGS__);

#if PLP_LOG_WARN_ENABLED == 1
#define PLPWARN(message, ...) logOutput(LOG_LEVEL_WARN, message, ##__VA_ARGS__);
#else
#define PLPWARN(message, ...)
#endif

#if PLP_LOG_INFO_ENABLED == 1
#define PLPINFO(message, ...) logOutput(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#else
#define PLPWARN(message, ...)
#endif

#if PLP_LOG_DEBUG_ENABLED == 1
#define PLPDEBUG(message, ...) logOutput(LOG_LEVEL_DEBUG, message, ##__VA_ARGS__);
#else
#define PLPWARN(message, ...)
#endif

#if PLP_LOG_TRACE_ENABLED == 1
#define PLPTRACE(message, ...) logOutput(LOG_LEVEL_TRACE, message, ##__VA_ARGS__);
#else
#define PLPWARN(message, ...)
#endif
