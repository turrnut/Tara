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
#include <string.h>

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

void initProject() {
    char author[100];
    char name[100];
    char description[200];
    printf("===Project Setup===\n\n");
    printf("What is the name of your project?(50 characters max) ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
    printf("What is your name?(50 characters max) ");
    fgets(author, sizeof(author), stdin);
    author[strcspn(author, "\n")] = '\0';

    printf("What is your project about?(200 Characters max) ");
    fgets(description, sizeof(description), stdin);
    description[strcspn(description, "\n")] = '\0';

    printf("\n");
    printf("initializing the project \"%s",name);
    printf("\" on the current working directory ... ");
    FILE* file_ptr = fopen(strcat((char*)name, ".tara"), "w");
    fprintf(file_ptr, "# This is a template program\n# Visit our website for more details\n\n# Hello World \ntrace(\"Hello, World!\");\n");
    fclose(file_ptr);

    FILE* config = fopen("tara.json", "w");
    fprintf(config, "\n{\n \t\"name\":\"%s\",\n\t\"author\":\"%s\",\n\t\"description\":\"%s\"\n}\n", name, author, description);
    fclose(config);
    printf("Done.\n");
}
