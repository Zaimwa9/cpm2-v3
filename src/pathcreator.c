#include "header.h"

char *createpath(char *path, char *name, int isLogLock)
{
  int sizelock, sizelog;
  char *dest;
  char cwd[1024];
  
  if (isLogLock == 0)
  {
    sizelock = strlen(path) + strlen(name) + strlen("/lockers/.pid");
    dest = (char*)malloc(sizeof(char) * sizelock);
    strcpy(dest, path);
    strcat(dest, "/");
    strcat(dest, name);
    strcat(dest, ".pid");
  }
  else if (isLogLock == 1)
  {
    dest = (char*)malloc(sizeof(char) * sizelog);
    sizelog = strlen(path) + strlen(name) + strlen("/logs/.txt");
    strcpy(dest, path);
    strcat(dest, "/");
    strcat(dest, name);
    strcat(dest, ".txt");
  }
  return (dest);
}