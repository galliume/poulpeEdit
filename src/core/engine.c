#include "engine.h"

#include "file.h"

#include "core/logger.h"

#include "platform/platform.h"

#include <cJSON.h>

void engine_load_config(engineConfig* engineConf)
{
  u64 size = 0;
  cJSON* settings = read_json_file("./config/poulpeEdit.json", &size);

  if (NULL != settings) {
    engineConf->paths = platform_allocate(size);
    engineConf->paths = settings;

    cJSON* poulpeEnginePath = cJSON_GetObjectItemCaseSensitive(settings, "poulpeEnginePath");

    if (cJSON_IsString(poulpeEnginePath) && (poulpeEnginePath->valuestring != NULL))
    {
      cJSON* textures = cJSON_GetObjectItemCaseSensitive(settings, "textures");
      
      if (cJSON_IsString(textures) && (textures->valuestring != NULL))
      {
        u64 len = 2 + strlen(poulpeEnginePath->valuestring) + strlen(textures->valuestring);
        char* texturesPath = platform_allocate(len);
        texturesPath = platform_zero_memory(texturesPath, len);

        strncat(texturesPath, poulpeEnginePath->valuestring, strlen(poulpeEnginePath->valuestring));
        strncat(texturesPath, "/", 1);
        strncat(texturesPath, textures->valuestring, strlen(textures->valuestring));
        strncat(texturesPath, "\0", 1);

        u64 size = 0;
        cJSON* textures = read_json_file(texturesPath, &size);

        engineConf->textures = platform_allocate(size);
        engineConf->textures = textures;

        platform_free(texturesPath);
      }

      cJSON* levels = cJSON_GetObjectItemCaseSensitive(settings, "levels");

      if (cJSON_IsString(levels) && (levels->valuestring != NULL))
      {
        u64 len = 9 + strlen(poulpeEnginePath->valuestring) + strlen(levels->valuestring);
        char* levelsPath = platform_allocate(len);
        levelsPath = platform_zero_memory(levelsPath, len);

        strncat(levelsPath, poulpeEnginePath->valuestring, strlen(poulpeEnginePath->valuestring));
        strncat(levelsPath, "/", 1);
        strncat(levelsPath, levels->valuestring, strlen(levels->valuestring));
        strncat(levelsPath, "/*.json", 7);
        strncat(levelsPath, "\0", 1);

        //cJSON* textures = read_json_file(texturesPath, &size);

        engineConf->levels = platform_list_directory(levelsPath, &engineConf->levelsSize);

        for (int i = 0; i < engineConf->levelsSize; ++i) {
          PLPDEBUG("%s", engineConf->levels[i]);
        }
        platform_free(levelsPath);
      }
    }
  }
}

cJSON* engine_get_config_textures(engineConfig* engineConf)
{
  return engineConf->textures;
}

char** engine_get_config_levels(engineConfig* engineConf)
{
  return engineConf->levels;
}