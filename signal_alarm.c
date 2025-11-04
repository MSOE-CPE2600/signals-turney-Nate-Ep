/**
* @file signal_alarm.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 3 November 2025
* 
* To Compile: make signal_alarm
* To Run: ./signal_alarm
*/


/**
 * File: signal_alarm.c
 * Modified by: Nathan Eppler <epplern@msoe.edu>
 * 
 * Brief summary of program: Utilizes sigaction struct and function to print
 * "Alarm handled" to the console after 5s (when the set alarm goes off)
 */

 #include <signal.h>
 #include <stdio.h>
 #include <unistd.h>

void handle_alarm() {
    printf("Alarm handled\n");
}

 int main(void) {
    alarm(5);

    struct sigaction sa = {0}; //set all fields of struct to zero
    sa.sa_handler = &handle_alarm; //set signal handler
    sigaction(SIGALRM, &sa, NULL); //set action to be done on SIGALRM

    for (int i = 0; i < 10; ++i) {
        printf("Sleeping: %ds\n", i+1);
        sleep(1);
    }

    return 0;
 }
