#ifndef HEADER_H
# define HEADER_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <syslog.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdarg.h>
# include <dirent.h>
# include <regex.h>
# define PATHLOG "/Users/annemorel/Desktop/cpm2v2-master/logs"
# define PATHLOCKS "/Users/annemorel/Desktop/cpm2v2-master/lockers"
# define MAX_MATCHES 1

int         control_processes(char *proc);
void        daemon_kill(char *name);
static void prog_daemon(const char *lockfile, const char *log_path);
void        list_processes(void);
char        *ft_filetype(char *src);
char        *createpath(char *path, char *name, int isLogLock);
int         ft_strlen(char *str);
int         match(regex_t *pexp, char *to_find);
int         reg_compile(char *to_find);
int         prog_init(char *path, char *name);
char        *ft_name(char *path);

#endif