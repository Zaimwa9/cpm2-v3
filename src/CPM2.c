#include "header.h"


int main(int argc, char **argv)
{
  char    *name, *type, *command, *binpath;
  char    cwd[1024];
  struct      stat st = {0};
 
  // Getting working directory
  if (getcwd(cwd, sizeof(cwd)) == NULL)
  {
    perror("getcwd() error");
    return (0);
  }
  // Arguments invalid
  if (argc > 3 || argc == 1)
  {
    printf("Wrong number of parameters, type --help or -h for help (Please, don't)\n");
    return (0);
  }
  else if (strcmp(argv[1], "restart") != 0 && strcmp(argv[1], "start") != 0 && strcmp(argv[1], "delete") != 0 && strcmp(argv[1], "kill") != 0 && strcmp(argv[1], "daemon_start") != 0 && strcmp(argv[1], "list") != 0) 
  {
    printf("Invalid command, type --help or -h for help (Please, don't)\n");
    return (0);
  }
  // Daemon_start
  else if (strcmp(argv[1], "daemon_start") == 0 && argc == 2)
  {
    // Initating sequency and creating folders
    if (stat(PATHLOG, &st) == -1)
      mkdir(PATHLOG, 0700);
    if (stat(PATHLOCKS, &st) == -1)
      mkdir(PATHLOCKS, 0700);
    if (control_processes("daemonlock") == 1)
    {
      printf("Error 37-B: CPM2 is already running\n");
      return (0);
    }
    name = "daemonlock";
    prog_init(cwd, name);
    return (0);
  }
  // Daemon kill
  else if (strcmp(argv[1], "kill") == 0 && argc == 2)
  {
    if (control_processes("daemonlock") == 0)
    {
      printf("Error 21-632: CPM2 not daemonized yet, please daemon_start first\n");
      return (0);
    }
    printf("hello");
    daemon_kill(name);
    return (0);
  }
  // list
  else if (strcmp(argv[1], "list") == 0 && argc == 2)
  {
    list_processes();
    return (0);
  }
  // Start feature
  else if (strcmp(argv[1], "start" ) == 0 && argc == 3)
  {
    // Checking validity of path & existence of the binary
    if (reg_compile(argv[2]) == 0)
    {
      printf("Error 193828-bis/KE: Invalid path\n");
      return (0);
    }
    if (stat(argv[2], &st) == -1)
    {
      printf("Error 2: Program does not exist\n");
      return (0);
    }
    // daemon init with process, path and name
    // Path will be define
    name = ft_name(argv[2]);
    // Checking if process already daemonized
    if (control_processes(name) == 1)
    {
      printf("Error 66: Execute all the jed... Heu, process already daemonized\n");
      return (0);
    }
    printf("Program getting daemonized\n");
    if (argv[2][0] == '.')
    {
      binpath = (char*)malloc(sizeof(cwd));
      binpath = strdup(cwd);
    } else {
      binpath = (char*)malloc(sizeof(argv[2]) - sizeof(char) * strlen(name));
      binpath = strndup(argv[2], strlen(argv[2]) - strlen(name) - 1);
    }
    prog_init(binpath, name);
    return (0);
  }
  // kill process
  else if (strcmp(argv[1], "delete") == 0 && argc == 3)
  {
    if (reg_compile(argv[2]) == 0)
    {
      printf("Error 193828-bis/KE: Invalid path\n");
      return (0);
    }
    if (stat(argv[2], &st) == -1)
    {
      printf("Error 2: Program does not exist\n");
      return (0);
    }
    name = ft_name(argv[2]);
    if (control_processes(name) == 0)
    {
      printf("Error 42: This process is not running at the moment\n");
      return (0);
    } else {
      daemon_kill(name);
      return (0);
    }
  }
  // Restart  
  else if (strcmp(argv[1], "restart") == 0 && argc == 3)
  {
    if (reg_compile(argv[2]) == 0)
    {
      printf("Error 193828-bis/KE: Invalid path\n");
      return (0);
    }
    if (stat(argv[2], &st) == -1)
    {
      printf("Error 2: Program does not exist\n");
      return (0);
    }
    if (control_processes(name) == 1)
    {
      printf("Error 42: This process is not running at the moment\n");
      return (0);
    } else {
      sprintf(command, "./kill_restart.sh %s %s", "cpm2", argv[2]);
      system(command);
      sprintf(command, "./restart.sh %s %s", "cpm2", argv[2]);
      system(command);
      return (0);
    }
  }
  return (0);
}