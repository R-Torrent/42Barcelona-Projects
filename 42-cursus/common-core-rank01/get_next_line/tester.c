#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int fd1, fd2, fd3;
	char *s1, *s2, *s3;

	printf("BUFFER_SIZE: %d\n\n", BUFFER_SIZE);

	if ((fd1 = open("test1.txt", O_RDONLY)) == -1)
		return 1;
	if ((fd2 = open("test2.txt", O_RDONLY)) == -1) {
		close(fd1);
		return 2;
	}
	if ((fd3 = open("test3.txt", O_RDONLY)) == -1) {
		close(fd1);
		close(fd2);
		return 3;
	}

	printf("File descriptor1: %d\n", fd1);
	printf("File descriptor2: %d\n", fd2);
	printf("File descriptor3: %d\n", fd3);

	while (s1 = get_next_line(fd1), s2 = get_next_line(fd2), s3 = get_next_line(fd3),
		s1 || s2 || s3) {
		if (s1) {
			printf("\n[%d; %zu] %s", fd1, strlen(s1), s1);
			free(s1);
		}		
		if (s2) {
			printf("\n[%d; %zu] %s", fd2, strlen(s2), s2);
			free(s2);
		}
		if (s3) {
			printf("\n[%d; %zu] %s", fd3, strlen(s3), s3);
			free(s3);
		}
	}	

	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
}
