#include <pthread.h>
#include <iostream>
#include <stdlib.h>
#include<unistd.h>

using namespace std;

int *fib;
void *thread_fib(void *arg);

int main(int argc, char *argv[]){
        int n,i;
        if (argc != 2){
                cout<<"format is: ./a.out <intgervalue>"<<endl;
                exit(0);
        }
        n = atoi(argv[1]);
        if (n <=0){
                cout<<"The number of fibonacci numbers must be > 0"<<endl;
                exit(0);
        }

        n = atoi(argv[1]);
        fib = new int[n];

       pthread_t *threads = (pthread_t *) malloc(n * sizeof(pthread_t));

        pthread_attr_t attr;

         pthread_attr_init(&attr);
        for (i = 0; i < n; i++){
                 pthread_create(&threads[i], &attr, thread_fib, (void *) &i);
                sleep(1);
        }
        for (i = 0; i < n; i++){
                 pthread_join(threads[i], NULL);
        }

        cout<<"Fibonacci numbers are..."<<endl;
         for (int i=0; i<n; ++i)
                cout<<fib[i]<<endl;

        delete fib;
        pthread_exit(NULL);
    return 0;
}

void * thread_fib(void *arg){
    int i=*((int *)arg);
    if (i == 0){
        fib[i] = 0;
        pthread_exit(NULL);
    }
    else if (i == 1){
        fib[i] = 1;
        pthread_exit(NULL);
    }
    else
    {
        fib[i] = fib[i - 1] + fib[i - 2];
        pthread_exit(NULL);
    }
}
