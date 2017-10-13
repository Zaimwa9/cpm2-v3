#include "header.h"

// Prendra en parametre un nom de file ou fd et ira lire le pid a kill
void daemon_kill(char *name)
{
  int fd, ret, i;
  char buf;
  char *pid, *tmp, *path, *fullpath;
  struct      stat st = {0};

  fullpath = createpath(PATHLOCKS, name, 0);
  pid = (char*)malloc(sizeof(buf));
  i = 0;
  fd = open(fullpath, O_RDONLY);
  while ((ret = read(fd, &buf, 1)))
  {
    tmp = (char*)malloc(sizeof(pid));
    tmp = strdup(pid);
    free(pid);
    pid = (char*)malloc(sizeof(tmp) + 1);
    pid = strdup(tmp);
    pid[i++] = buf;
    free(tmp);
  }
  close(fd);
  printf("I'm killing %d \n", (pid_t)atoi(pid));
  // Delete the locker file 
  if (stat(fullpath, &st) != -1)
    execl("/usr/bin/rm", "rm -rf", fullpath);
  kill((pid_t)atoi(pid), SIGKILL);
}