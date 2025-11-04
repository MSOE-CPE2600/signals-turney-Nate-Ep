/**
* @file signal_sigaction.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 3 November 2025
*
* To Compile: make signal_sigaction
* To Run: ./signal_sigaction 
*/

 /**
 * File: signal_sigaction.c
 * Modified by: Nathan Eppler <epplern@msoe.edu>
 * 
 * Brief summary of program: Waits in an infinite loop doing nothing until a 
 * SIGUSR1 is recieved. On this signal, the program prints out the sender's PID
 * and then continues in the loop. The program can be killed via kill -SIGKILL <pid>.
 *
 * To Send SIGUSR1: kill -SIGUSR1 <pid>
 */

 #include <signal.h>
 #include <stdio.h>
 #include <unistd.h>

 void usr1_handler(int signum, siginfo_t *info, void *context) {
    printf("Sender PID: %d\n", info->si_pid);
    fflush(stdout);
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