#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

int main (int argc, char *argv[]) {
    int pipeFields[2];
    int fileBytesLength;
    char buffer[100];
    char childBuffer[100];

    if (argc != 3) {
      perror("Filecopy: filecopy.exe [target] [destination]. \n");
      exit(1);
    }

    char* sourceFile = argv[1];
    char* finalFile = argv[2];

    if (pipe(pipeFields) < 0) {
      printf("Something went wrong when creating the pipe! %s\n", strerror(errno));
      exit(1);
    }

    switch(fork()) {

      case -1:
        printf("Error forking child process. %s\n", strerror(errno));
        exit(1);

      case 0:
        close(pipeFields[1]);
        ssize_t num_bytes_child = read(pipeFields[0], childBuffer, sizeof(childBuffer));
        close(pipeFields[0]);

        int targetDesc = open(finalFile, O_CREAT | O_WRONLY);
        write(targetDesc, childBuffer, num_bytes_child);

      default:
        close(pipeFields[0]);
        int fileInDesc = open(sourceFile, O_RDONLY);
        ssize_t num_bytes = read(fileInDesc, buffer, sizeof(buffer));
        write(pipeFields[1], buffer, num_bytes);
        close(pipeFields[1]);
    }

    return 0;
}
