#include<stdio.h>
#include<stdlib.h>
void main()
{
    int time;
    for(time=600;time>=0;time--)
    {
        printf("\n\t\t\t%d\n",time);
        sleep(1);
        system("clear");
    }//If quiz is for 10 minutes,time=10*60=600
    if(time==-1)
        exit(0);
}

