/*
Team members:
資工三 方文昊 108590048
資工三 鄭琳玲 108590056
資工三 黃聖耀 108590061
電資三 李以謙 108820021
*/

#include <thread>
#include <vector>
#include <mutex>
#include <unistd.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
using namespace std;

mutex gMutex;

sem_t smstrChair[3];
sem_t smstrStudent;
sem_t sleepingTA;

int nmbrsOfChairs = 0;
int lt = 0;

void doTeacherAssistant() {

	while(1) {
	
		sem_wait(&sleepingTA);
        	cout << "A student awakens the TA. " << endl;
        	
		while(1)
		{
			gMutex.lock();
			
			if(nmbrsOfChairs == 0) {
			
				gMutex.unlock();
				break;
			}
			sem_post(&smstrChair[lt]);
			nmbrsOfChairs--;
			
            		cout << "The student left the chair. The remaining chairs: " << 3 - nmbrsOfChairs << endl;
            		
			lt = (lt + 1) % 3;
			gMutex.unlock();
			
           		cout << "The TA is currently helping the student." << endl;
            
			sleep(3);
			sem_post(&smstrStudent);
			usleep(1000);
			
		}
	}
}

void doStudents(int stdntsNmbrs) {

	int assignmentDo;
	
	while(1) {
	
        	cout << "Student " << stdntsNmbrs << " is doing the programming assignment." << endl;
        
		assignmentDo = 3;
		sleep(assignmentDo);
		
        	cout << "Student " << stdntsNmbrs << " needs help from the TA." << endl;
        
		gMutex.lock();
		
		int chairsCnt = nmbrsOfChairs;
		
		gMutex.unlock();
		
		if(chairsCnt < 3) {
		
			if(chairsCnt == 0) {sem_post(&sleepingTA);} 
			
			else {cout << "Student " << stdntsNmbrs << " is sitting on a chair waiting for the TA to finish." << endl;}
			
			gMutex.lock();
			
			int theLt = (lt + nmbrsOfChairs) % 3;
			nmbrsOfChairs++;
			
            		cout << "The student is sitting on the chair. The remaining chairs: " << 3 - nmbrsOfChairs << endl;
            		
			gMutex.unlock();
			sem_wait(&smstrChair[theLt]);
			
            		cout << "Student " << stdntsNmbrs << " is getting help from the TA." << endl;
			sem_wait(&smstrStudent);
            		cout << "Student " << stdntsNmbrs << " left TA room." << endl;
		} 
		
		else {cout << "Student " << stdntsNmbrs << " will return another time." << endl;}
	}
}

int main(int argc, char* argv[]) {

	int studentNmbrs;
	
    	vector<thread> stdntThreads;
    	
	sem_init(&sleepingTA, 0, 0);
	sem_init(&smstrStudent, 0, 0);
	
    	for(int i = 0; i < 3; i++) {sem_init(&smstrChair[i], 0, 0);}
    	
	if(argc < 2) {
		cout << "Please input number of students." << endl;
		return 1;
	}
	
	studentNmbrs = atoi(argv[1]);
	cout << "There are " << studentNmbrs << " students." << endl;
    	thread teacherAssistant(doTeacherAssistant);
    	
    	for(int i = 0; i < studentNmbrs; i++) {stdntThreads.push_back(thread(doStudents, i));}
    
    	teacherAssistant.join();
    
    	for(int i = 0; i < stdntThreads.size(); i++) {stdntThreads[i].join();}
    
    	return 0;
}
