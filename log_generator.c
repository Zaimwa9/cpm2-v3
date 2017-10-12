#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int i = 0;
	char c;
	int fd;

	while (i < 10)
	{
		c = i + 48;
		write(1, "log ", 4);
		write(1, &c, 1);
		c = '\n';
		write(1, &c, 1);
		i++;
	}
	return (0);
}
