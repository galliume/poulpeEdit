#include "core/file.h"

#include "core/logger.h"

#include "platform/platform.h"

#include <stdio.h>
#include <errno.h>

char * read_file(char const* file_path)
{
  FILE* fp;
  char* source = NULL;

  fp = fopen(file_path, "r");

  if (NULL != fp) {
    if (fseek(fp, 0L, SEEK_END) == 0) {
      long bufsize = ftell(fp);
      if (bufsize == -1) {
        PLPERR("%s", "error while reading file size");
      }
      source = (char *)platform_allocate(sizeof(char) * (bufsize));
      source = (char *)platform_zero_memory(source, sizeof(char) * (bufsize));

      if (fseek(fp, 0L, SEEK_SET) != 0) {
        PLPERR("%s: %s", "error while reading file size", file_path);
      }
      size_t len = fread(source, sizeof(char), bufsize, fp);

      PLPTRACE("%s: %d %s: %s", "Read", len, "bytes from file", file_path);
      
      if (ferror(fp) != 0) {
        PLPERR("%s: %s", "error while reading file", file_path);
        perror("readFile");
      }
    }
  }
  fclose(fp);

  return source;
}

cJSON* read_json_file(char const* file_path)
{
  char* buffer = read_file(file_path);

  cJSON *json = cJSON_Parse(buffer);
  
  platform_free(buffer);
  
  if (NULL == json) {
    const char *error_ptr = cJSON_GetErrorPtr();
    PLPERR("%s: %s", "Error while parsing json", error_ptr);
    cJSON_Delete(json);
    return NULL;
  }
  return json;
}