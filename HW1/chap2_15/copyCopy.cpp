#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    string fileInit, fileExit;
    int inputFD, outputFD;
    ssize_t bytesRd, bytesWr;
    int bufferSize = 32768;
    char buffer[bufferSize];
    char fileNameExit[50], fileNameInit[50];

    cout << "Enter the name of the input file (ex: input.txt)" << endl;
    cin >> fileInit;

    cout << "Enter the name of the output file (ex: output.txt)" << endl;
    cin >> fileExit;

    strcpy(fileNameInit, fileInit.c_str());
    strcpy(fileNameExit, fileExit.c_str());

    inputFD = open(fileNameInit, O_RDONLY);
    if (inputFD == -1) {
        perror ("Error while opening Input File");
        return 2;
    }

    outputFD = open(fileNameExit, O_WRONLY | O_CREAT, 0644);
    if(outputFD == -1) {
        perror("Error while opening Output File");
        return 3;
    }

    while((bytesRd = read(inputFD, &buffer, bufferSize)) > 0){
        bytesWr = write(outputFD, &buffer, (ssize_t) bytesRd);
        if(bytesWr != bytesRd) {
            perror("Error in writing");
            return 4;
        } else {
          cout << "File has been copied successfully" << endl;
	}
    }

    close (inputFD);
    close (outputFD);
    return 0;
}
