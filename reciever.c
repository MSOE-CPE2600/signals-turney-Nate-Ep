/**
* @file reciever.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 4 November 2025
* @brief Recieves the signal from server and sends the "ball" back.
*
* To Compile: make reciever
* To Run: ./reciever &
* ^ run in background
*/

#define ONE_BILLION 1000000000L

#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

/**
* @brief Handles the SIGUSR2 interrupt, sending the ball back to the server
* @param signum The signal number sent
* @param info The information sent along (the rally count)
* @param context Sigaction context
*/
void ball_reciever(int signum, siginfo_t *info, void *context) {
    pid_t ret_pid = info->si_pid;
    union sigval count = info->si_value;
    count.sival_int += 1; //increment count

    if (count.sival_int > 20) {
        //both sides have each hit 10 times, quit
        kill(ret_pid, SIGKILL); //kill other process
        exit(0);
    } else {
        //get a random number for sleeping
        struct timespec ts = {0};
        clock_gettime(CLOCK_REALTIME, &ts); //get time
        srand(ts.tv_sec);
        ts.tv_sec = 1; //sleep for a min of one sec
        ts.tv_nsec = (long)(rand() % ONE_BILLION); //generate random num, mod to keep in range
        nanosleep(&ts, NULL); //sleep for 1-2 seconds

        printf("Reciever: BOINK!\007\n\n");
        fflush(stdout);
        //send ball back to server
        sigqueue(ret_pid, SIGUSR1, count);
    }
}


int main() {
    struct sigaction sa = {0};
    sa.sa_sigaction = ball_reciever;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &sa, NULL); //set the reciever to handle SIGUSR1

    while (1) {
        sleep(1); //infinite loop
    }

    return 0;
}