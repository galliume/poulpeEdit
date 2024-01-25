#pragma once

#include <cJSON.h>

extern char* read_file(char const* filePath);
extern cJSON* read_json_file(char const* filePath);