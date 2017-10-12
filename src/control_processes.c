#include "header.h"

int  control_processes(char *proc)
{
  DIR *dir;
  struct dirent *file;
  int flag;
  
  flag = 0;
  if ((dir = opendir (PATHLOCKS)) != NULL) {
    while ((file = readdir (dir)) != NULL) {
      if (strncmp(file->d_name, proc, strlen(proc)) == 0 && ((strlen(file->d_name ) - 4) - strlen(proc) == 0))
        flag = 1;
    }
    closedir (dir);
  } else {
    printf("Failure controlling error: Repertory missing call 911 NYPDirectory\n");
    return (0);
  }
  if (flag == 1)
    return (1);
  else
    return (0);  
}