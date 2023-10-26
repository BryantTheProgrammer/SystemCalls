/*
professor.c starter code.

Bryant Hayden, Fall 2023

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv){
srand(time(NULL));
        //STDIN   0     usually the keyboard
        //STDOUT  1     usually the terminal where the program was run from
        //STDERR  2     usually the terminal where the program was run from
   // while (1){

        //seed your random number generator
        //sleep for a random amount between 5 and 15 seconds to simulate studying
        int amountSleep = rand()%11+5;
        sleep(amountSleep);
        fprintf(stderr, "student: studying for %d seconds\n", amountSleep);
        fflush(stderr);
        //randomize a single digit question number: 1,2,3 or 4
        int qNumber = rand()% 4 + 1;
        //write the random question number to standard output
        char mychars[2];
        sprintf(mychars, "%d", qNumber);
        fprintf(stderr, "student: asking question: %s\n", mychars);
        fflush(stderr);
        fprintf(stderr,"student: waiting for answer\n");
        fflush(stderr);
        write(1,mychars, 2);
        //write(2, mychars, 1);
       // write(2, "\n", 1);
        //wait for a response from standard input
        //write(1,mychars, 1);
        
        char response[100];
        read(0, response, 99);
        //print the response to stderr
        //while in loop this the string will not overide itself so it will keep chars that shouldn't be there
        fprintf(stderr,"student: received answer: ");
        fprintf(stderr, "%s\n***********\n", response);
        //to reset the array
        memset(response, 0, 100);
        exit(1);
    }
//}

