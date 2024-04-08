#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 4096

int are_files_similar(const char * file1, const char * file2){

	int fd1, fd2;
	int nread1, nread2;
   	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];

    fd1 = open(file1, O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return -1;
    }

    fd2 = open(file2, O_RDONLY);
    if (fd2 == -1) {
        perror("open");
        close(fd1);
        return -1;
    }

	while (((nread1 = read(fd1, buf1, BUFFER_SIZE)) > 0) &&
           ((nread2 = read(fd2, buf2, BUFFER_SIZE)) > 0)) {
        if (nread1 != nread2 || memcmp(buf1, buf2, nread1) != 0) {
            close(fd1);
            close(fd2);
            return 1;
	}

    close(fd1);
    close(fd2);

    return 2;
}
}
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return EXIT_FAILURE;
    }


	const char *file1 = argv[1];
	const char *file2 = argv[2];

    int result = are_files_similar(file1, file2);
    if (result == -1) {
        return EXIT_FAILURE;
    } else if (result == 1) {
        printf("Files are different.\n");
    } else if (result == 2) {
        printf("Files are identical.\n");
    }

    return EXIT_SUCCESS;
}

