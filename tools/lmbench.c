/**
 *  like lmbench
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>  // exit

int main() {
    pid_t pid;
    int pipefd1[2];
    // int pipefd2[2];
    pipe(pipefd1); // fd1[0] use to read, fd1[1] used to write
    // pipe(pipefd2);

    if ((pid = fork()) < 0) {
        printf("fork error\n");
        exit(0);
    } else if (pid > 0) {
        close(pipefd1[0]);
        struct timeval tv;
        gettimeofday(&tv, NULL);
        write(pipefd1[1], (void*)&tv, sizeof(tv));
    } else {
        struct timeval tv1, tv2;
        close(pipefd1[1]);
        read(pipefd1[0], (void*)&tv1, sizeof(tv1));
        gettimeofday(&tv2, NULL);
        printf("%ld usec\n", tv2.tv_usec - tv1.tv_usec);

    }
}