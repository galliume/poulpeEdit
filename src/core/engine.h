#pragma once

#include <cJSON.h>

typedef struct engineConfig
{
  cJSON* paths;
  cJSON* textures;
} engineConfig;

extern void engine_load_config(engineConfig* engineConf);
extern cJSON* engine_read_config(engineConfig* engineConf);