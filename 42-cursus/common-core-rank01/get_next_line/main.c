#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd = open("prueba.txt", O_RDONLY);
	char *s;

	if (fd != -1) {
		while ((s = get_next_line(fd))) {
			printf("%s", s);
			free(s);
		}
		close(fd);
	}
	return 0;
}
