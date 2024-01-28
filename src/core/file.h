#pragma once

#include "defines.h"

#include <cJSON.h>

extern char* read_file(char const* filePath, u64 *size);
extern cJSON* read_json_file(char const* filePath, u64 *size);