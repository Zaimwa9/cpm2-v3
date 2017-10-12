#include "header.h"

static void prog_daemon(const char *lockfile, const char *log_path)
{
  pid_t pid, sid;
  int i, fd, fd_lock;
  char str[7];
  
  // already a deamon case
  if (getppid() == 1)
    return;
  // First fork
  pid = fork();
  // Error handling
  if (pid < 0)
    exit(1);
  // We can terminate the parent for the first time because child now exists (fork() returns 0 to the child)
  if (pid > 0)
    exit(0);
  // Making it the session leader
  sid = setsid();
  if (sid < 0)
    exit(1);
  // Fork off for the second time
  pid = fork();
  // An error occurred
  if (pid < 0)
    exit(1);
  // Reterminate the parent
  if (pid > 0)
    exit(0);
  // Permissions
  umask(0);
  // Change the working directory
  chdir("/");
  // run program
  //system("/c/users/Wadii/Desktop/CPM2/bin/cpm2.exe ./test.exe");

  // Closing inherited file descriptors
  for (i = getdtablesize(); i >= 0; i--)
    close(i);
  // Reopening stdin, stdout, stderr
  // We redirect everything to devnull in order to send them to a harmless location
  //fd = open("/dev/null", O_RDWR, 0);
  fd = open(log_path, O_RDWR | O_CREAT, S_IRWXU);
  //close(fd);
  if (fd != -1)
  {   
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
   // if (fd > 2)
   //   close(fd);
  }
  // We need to create open the file in which we'll lock the PID
  if (lockfile && lockfile[0])
  {
    fd_lock = open(lockfile, O_RDWR | O_CREAT, S_IRWXU);
    // Waiting cause otherwise fd_lock < 0. Don't know why yet
    wait((int*)3);
    if (fd_lock < 0)
    { 
      printf("Error with lockfile creation: %s \n", strerror(errno));
      exit(1);
    }
    if (lockf(fd_lock, F_TLOCK, 0) == -1)
    {
      printf("Error locking the PID file");
      exit(1);
    }
    // formatting the PID and storing it
    sprintf(str, "%d\n", getpid());
    write(fd_lock, str, strlen(str));
  }
}

int prog_init(char *path, char *name)
{
  int sizelock, sizelog, i, fullsize;
  char *lockfile_path, *log_path, *full_path;

  i = 0;
  // All specific folders will be define in header
  sizelock = strlen(PATHLOCKS) + strlen(name) + strlen("/.pid");
  sizelog = strlen(PATHLOG) + strlen(name) + strlen("/.txt");
  fullsize = strlen(path) + strlen(name) + 1;
  lockfile_path = (char*)malloc(sizeof(char) * sizelock);
  log_path = (char*)malloc(sizeof(char) * sizelog);
  full_path = (char*)malloc(sizeof(char)* fullsize);
  strcpy(lockfile_path, PATHLOCKS);
  strcat(lockfile_path, "/");
  strcat(lockfile_path, name);
  strcat(lockfile_path, ".pid");
  strcpy(log_path, PATHLOG);
  strcat(log_path, "/");
  strcat(log_path, name);
  strcat(log_path, ".txt");
  strcpy(full_path, path);
  strcat(full_path, "/");
  strcat(full_path, name);
  prog_daemon(lockfile_path, log_path);
  free(lockfile_path);
  free(log_path);
  while (1)
  {
    if (strcmp(name, "daemonlock") != 0)
      system(full_path);
  }
  return (0);
}