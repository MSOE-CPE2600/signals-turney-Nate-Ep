/**
* @file server.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 4 November 2025
* @brief Serves the "ball" to reciever to start the match.
*
* To Compile: make server
* To Run: ./server <pid>
*/

#define ONE_BILLION 1000000000L

#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

/**
* @brief Handles the SIGUSR1 interrupt, sending the ball back to the reciever
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

        printf("Server: BOOP!\007\n");
        fflush(stdout);
        //send ball back to server
        sigqueue(ret_pid, SIGUSR2, count);
    }
}

int main(int argc, char *argv[]) {
    struct sigaction sa = {0};
    sa.sa_sigaction = ball_reciever;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL); //set up reciever
    
    if (argc == 2) {
        char *pid_str = argv[1];
        char *end;
        pid_t pid = strtod(pid_str, &end);

        if (pid_str != end) {
            //valid input
            errno = 0;
            int ret = kill(pid, 0); //test to see if PID exists

            if (ret == 0) { //PID exsits and we have permissions
                //send starting program
                union sigval count = {0};
                count.sival_int = 1;

                printf("Server: BOOP!\007\n"); //hit initial ball to reciever
                sigqueue(pid, SIGUSR2, count);
            } else {
                printf("Error with PID: %d\n", pid);
                perror("Description"); //print error message
            }
        } else {
            printf("Invalid PID: %s\n", argv[1]);
        }
    } else {
        printf("Error: invalid number of arguments\n"
            "Expected: './send_signal <pid>'\n");
    }

    while (1) {
        sleep(1); //infinite loop
    }

    return 0;
}