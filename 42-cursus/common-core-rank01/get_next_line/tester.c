#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
	int fd1, fd2;
	char *s1, *s2;

	printf("BUFFER_SIZE: %d\n\n", BUFFER_SIZE);

	if ((fd1 = open("test1.txt", O_RDONLY)) == -1)
		return 1;
	if ((fd2 = open("test2.txt", O_RDONLY)) == -1) {
		close(fd1);
		return 2;
	}

	printf("File descriptor1: %d\n", fd1);
	printf("File descriptor2: %d\n\n", fd2);

	while (s1 = get_next_line(fd1), s2 = get_next_line(fd2), s1 || s2) {
		if (s1) {
			printf("\n[%d] %s", fd1, s1);
			free(s1);
		}		
		if (s2) {
			printf("\n[%d] %s", fd2, s2);
			free(s2);
		}
	}	

	close(fd1);
	close(fd2);
	return 0;
}
