#include "engine.h"

#include "file.h"

#include "core/logger.h"

#include "platform/platform.h"

#include <cJSON.h>

void engine_load_config(engineConfig* engineConf)
{
  cJSON* settings = read_json_file("./config/poulpeEdit.json");

  if (NULL != settings) {
    engineConf->paths = platform_allocate(sizeof(settings));
    engineConf->paths = settings;

    cJSON* poulpeEnginePath = cJSON_GetObjectItemCaseSensitive(settings, "poulpeEnginePath");
    cJSON* textures = cJSON_GetObjectItemCaseSensitive(settings, "textures");

    if (cJSON_IsString(poulpeEnginePath) && (poulpeEnginePath->valuestring != NULL))
    {
      if (cJSON_IsString(textures) && (textures->valuestring != NULL))
      {
        i32 len = 2 + strlen(poulpeEnginePath->valuestring) + strlen(textures->valuestring);
        char* texturesPath = platform_allocate(len);
        texturesPath = platform_zero_memory(texturesPath, len);

        strncat(texturesPath, poulpeEnginePath->valuestring, strlen(poulpeEnginePath->valuestring));
        strncat(texturesPath, "/", 1);
        strncat(texturesPath, textures->valuestring, strlen(textures->valuestring));
        strncat(texturesPath, "\0", 1);

        cJSON* textures = read_json_file(texturesPath);

        engineConf->textures = platform_allocate(sizeof(textures));
        engineConf->textures = textures;

        platform_free(texturesPath);
      }
    }
  }
}

cJSON* engine_read_config(engineConfig* engineConf)
{
  return engineConf->textures;
}