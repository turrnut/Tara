/**
 * Author: turrnut
 * Copyrighted © turrnut under the Apache 2.0 license
 *
 * We hoped that you will use this piece of open source
 * software fairly. read the LICENSE for more details about
 * how you can use it, you have freedom to distribute and
 * use this code in your project. However, you will have to
 * state changes you made and include the orginal author of
 * this code.
 * 
 * files.c
 */
#include <stdio.h>
#include <stdlib.h>

#include "files.h"
char *readFile(const char *path)
{
  FILE *file = fopen(path, "rb");
  if (file == NULL)
  {
    printf("ERR: Can't open file \"%s\"\n", path);
    exit(1);
  }
  fseek(file, 0L, SEEK_END);
  size_t fileSize = ftell(file);
  rewind(file);

  char *buffer = (char *)malloc(fileSize + 1);
  size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
  if (bytesRead < fileSize)
  {
    printf("ERR: Can't read file \"%s\".\n", path);
    exit(1);
  }
  buffer[bytesRead] = '\0';
  if (buffer == NULL)
  {
    printf("ERR: Memory overflow while attempting to open\"%s\".\n", path);
    exit(1);
  }

  fclose(file);
  return buffer;
}