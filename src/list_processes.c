#include "header.h"

void  list_processes(void) {
DIR *dir;
struct dirent *file;
struct      stat st = {0};

if ((dir = opendir (PATHLOG)) != NULL) {
  while ((file = readdir (dir)) != NULL) {
    if (strcmp(file->d_name, ".") != 0 && strcmp(file->d_name, "..") != 0)
      printf ("%s\n", file->d_name);
  }
  closedir (dir);
} else {
  printf("Failure error: Repertory missing: call 911 NYPDirectory\n");
  }
}