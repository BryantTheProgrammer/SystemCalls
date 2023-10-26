/*
professor.c 

Bryant Hayden, Fall 2023
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{

    char *prog = "./student";
    char **args = NULL;
    while (1)
    {
        int status = 0;

        // create two uni-directional pipes
        // one for professor to student, one from student to professor
        int pipefd_fromchild[2];
        int pipe_fromparent[2];

        pipe(pipefd_fromchild);
        pipe(pipe_fromparent);

        // fork to create a child process
        //int pid = fork();

        // child portion
        // need two calls to dup2, two calls to close, and a call to execv
        if (fork() == 0)
        {
            dup2(pipefd_fromchild[0], STDIN_FILENO);
            //close(pipefd_fromchild[0]);

            dup2(pipe_fromparent[1], STDOUT_FILENO);
            //close(pipe_fromparent[1]);

            close(pipefd_fromchild[1]);
            close(pipe_fromparent[0]);

            if(execv(prog, args)==-1){
                perror("execv");
                exit(EXIT_FAILURE);
            }
            // NOT REACHED
        }
        // parent portion
        else
        {
            // need two calls to dup2
            dup2(pipefd_fromchild[1], STDOUT_FILENO);
            //close(pipefd_fromchild[1]);

            dup2(pipe_fromparent[0], STDIN_FILENO);
            //close(pipe_fromparent[0]);

            close(pipefd_fromchild[0]);
            close(pipe_fromparent[1]);
            // close unused half of pipes

            fprintf(stderr, "\tprof: waiting for question\n");
            fflush(stderr);

            // read a question from standard input
            char response[2];
            read(0, response, 2);

            int x;
            sscanf(response, "%d", &x);
            fprintf(stderr, "\tprof: question read: %d\n", x);
            fflush(stderr);
            //fflush(stderr);
            // printf("%", x);
            // choose an answer based on the question
            if (x == 1)
                write(1, "silly question\n", 16);
            else if (x == 2)
                write(1, "good question\n", 15);
            else if (x == 3)
                write(1, "smart question!\n", 17);
            else if (x == 4)
                write(1, "I don't know\n", 14);

            fprintf(stderr, "\tprof: wrote response\n");
            fflush(stderr);
            // wrte the response to standard output
        }
    }
}