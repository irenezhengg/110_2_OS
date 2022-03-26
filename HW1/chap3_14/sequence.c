#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void seq(int number) {
    if(number == 1) {
    	printf("%d\n", number);
	    return ;
    }

    if(number % 2 == 0) {
    	printf("%d", number);
	    number /= 2;
        seq(number);
    } else {
    	printf("%d", number);
	    number = 3 * number + 1;
        seq(number);
    }

}

int main(int argc, char** argv){
    int number;
    if(argc == 2) {
        number = atoi(argv[1]);
        if(fork() == 0) {
            seq(number);
            exit(0);
        } else {
            wait(NULL);
        }
    } else {
        printf("Argument Required!\n");
    }
    return 0;
}
