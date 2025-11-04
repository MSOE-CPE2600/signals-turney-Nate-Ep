/**
* @file recv_signal.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 3 November 2025
*
* To Compile: make recv_signal
* To Run: ./recv_signal & 
* ^ This program is intended to run the the background.
*/

 /**
 * File: recv_signal.c
 * Modified by: Nathan Eppler <epplern@msoe.edu>
 * 
 * Brief summary of program: Waits in an infinite loop doing nothing until a 
 * SIGUSR1 is recieved. On this signal, the program prints out the sender's random
 * number. Program can be killed via $kill -SIGKILL <pid>
 *
 */

 #include <signal.h>
 #include <stdio.h>
 #include <unistd.h>

 void usr1_handler(int signum, siginfo_t *info, void *context) {
    union sigval val = info->si_value;
    printf("Random value recieved: %d\n", val.sival_int); 
    fflush(stdout); //flush the stdout stream to be printed in background
 }

 int main(void) {
    struct sigaction sa = {0}; //set all struct fields to zero
    sa.sa_sigaction = usr1_handler;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);


    while (1) {
        sleep(1);
    }

    return 0;
 }