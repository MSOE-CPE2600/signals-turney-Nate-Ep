/**
* @file send_signal.c
* @author Nathan Eppler <epplern@msoe.edu>
* @date 3 November 2025
*
* To Compile: make send_signal
* To Run: ./send_signal <pid>
*/

/**
 * File: send_signal.c
 * Modified by: Nathan Eppler <epplern@msoe.edu>
 * 
 * Brief summary of program: Sends a SIGUSR1 to the specified PID when run.
 * PID specified at command line via './send_signal <pid>'.
 */

 #include <stdlib.h>
 #include <signal.h>
 #include <stdio.h>
 #include <sys/types.h>
 #include <sys/time.h>
 #include <time.h>
 #include <errno.h>

 int main(int argc, char *argv[]) {

    if (argc == 2) {
        char *pid_str = argv[1];
        char *end;
        pid_t pid = strtod(pid_str, &end);

        if (pid_str != end) {
            //valid input
            errno = 0;
            int ret = kill(pid, 0); //test to see if PID exists

            if (ret == 0) { //PID exsits and we have permissions
                //store rand val for reciever
                struct timespec ts = {0};
                clock_gettime(CLOCK_REALTIME, &ts);
                srand(ts.tv_sec); //set random seed based on time
                union sigval sending_val = {0};
                sending_val.sival_int = rand(); //set random val to send

                sigqueue(pid, SIGUSR1, sending_val);
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

    return 0;
 }
