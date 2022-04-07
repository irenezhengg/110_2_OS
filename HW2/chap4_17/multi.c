#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <stdlib.h>

int num = 0;
int requiredAmount = 0;
int totalPoints  = 0;

void *count(void *X)
{
    /* initialize random numbers */
    for (num=0; num < requiredAmount; num++)
    {
        double X = (double)rand() / RAND_MAX;
        double Y = (double)rand() / RAND_MAX;

        if (((X * X) + (Y * Y)) <= 1)
        {
            totalPoints++;
        }
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    pthread_t thread;

    do
	{
        printf("Please enter a positive number \n");
        scanf("%d", &requiredAmount);
	}while (requiredAmount <= 0);

    pthread_create(&thread, NULL, &count, NULL);
    pthread_join(thread, NULL);

    double points = 4.0 * totalPoints;
    double pi = points / requiredAmount;
    printf("The approximate value of pi for the desired amount of points is: %f \n", pi);
    return 0;
}
