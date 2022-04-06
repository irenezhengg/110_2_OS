/*
Team members:
資工三 方文昊 108590048
資工三 鄭琳玲 108590056
資工三 黃聖耀 108590061
電資三 李以謙 108820021
*/

#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define HISTORY_SIZE 100

static char* history[HISTORY_SIZE];
static int historyCount = 0;

static void exec(const char* line) {
	char* command = strdup(line);
	char* params[10];
	int argc = 0;
	params[argc++] = strtok(command, " ");
	while(params[argc-1] != NULL) {	
		params[argc++] = strtok(NULL, " ");
	}
	argc--;
	int background = 0;
	if(strcmp(params[argc-1], "&") == 0) {
		background = 1;
		params[--argc] = NULL;
	}
	int fd[2] = {-1, -1};
	while(argc >= 3) {
		if(strcmp(params[argc-2], ">") == 0) {
            fd[1] = open(params[argc-1], O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP|S_IWGRP);
			if(fd[1] == -1) {
				printf("open error");
				free(command);
				return;
			}
			params[argc-2] = NULL;
			argc -= 2;
		} else if(strcmp(params[argc-2], "<") == 0) {
			fd[0] = open(params[argc-1], O_RDONLY);
			if(fd[0] == -1) {
				printf("open error");
				free(command);
				return;
			}
			params[argc-2] = NULL;
			argc -= 2;
		} else {
			break;
		}
	}
	int status;
	pid_t pid = fork();
	if(pid < 0) {
		printf("fork error");
	} else if(pid == 0) {
		if(fd[0] != -1) {
				if(dup2(fd[0], STDIN_FILENO) != STDIN_FILENO) {
					printf("dup2 error");
					exit(1);
				}
			}
		if(fd[1] != -1) {
			if(dup2(fd[1], STDOUT_FILENO) != STDOUT_FILENO) {
				printf("dup2 error");
				exit(1);
			}
		}
		execvp(params[0], params);
		printf("execvp error\n");
		exit(0);
	} else {
		close(fd[0]);
		close(fd[1]);
			if(!background) {
				waitpid(pid, &status, 0);
			}
	}
	free(command);
}

static void addToHistory(const char* command) {
	if(historyCount == (HISTORY_SIZE - 1)) {
		int i;
		free(history[0]);
		for(i = 1; i < historyCount; i++) {
			history[i -1] = history[i];
		}
		historyCount--;
	}
	history[historyCount++] = strdup(command);
}

static void listHistory() {
	int i;
	for(i = historyCount - 1; i >= 0; i--) {
		printf("%i %s\n", i+1, history[i]);
	}
}

int main(int argc, char* argv[]) {
	size_t line_size = 100;
	char* line = (char*) malloc(sizeof(char)*line_size);
	if(line == NULL) {
		printf("malloc error");
		return 1;	
	}
	
	int inter = 0;
	
	while(1){
	
		if(!inter)
			printf("osh> ");
		if(getline(&line, &line_size, stdin) == -1){
			printf("getline error");
			break;
			
		}
		
		inter = 0;
		
		if(strlen(line) == 1){
			continue;
		}
		
		line[strlen(line) - 1] = '\0';
		
		if(strcmp(line, "!!") == 0){
			if(*history == 0){
			printf("No commands in history\n");
			}
			continue;
		}
		
		if(strcmp(line, "exit") == 0){break;}
		
		else if(strcmp(line, "history") == 0){listHistory();}
		
		else{
			addToHistory(line);
			exec(line);
		}
	}
	
	free(line);
	return 0;
	
}
