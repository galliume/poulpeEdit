#pragma once

#include "defines.h"

#include <cJSON.h>

typedef struct engineConfig
{
  cJSON* paths;
  cJSON* textures;
  char** levels;
  u64 levelsSize;
} engineConfig;

extern void engine_load_config(engineConfig* engineConf);
extern cJSON* engine_get_config_textures(engineConfig* engineConf);
extern char** engine_get_config_levels(engineConfig* engineConf);