#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

void generate_fibonacci(int n) {
    int first = 0, second = 1, next;
    for(int i = 0; i < n; i++) {
        if(i <= 1)
            next = i;
        else {
            next = first + second;
            first = second;
            second = next;
        }
        printf("%d ", next);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if(n < 0) {
        printf("You are entering a negative number,please enter a non-negative number.\n");
        return 1;
    }

    pid_t pid = fork();

    if(pid < 0) {
        perror("Fork failed");
        return 1;
    } else if(pid == 0) {
        printf("Child Process: Generating Fibonacci sequence of %d terms\n", n);
        generate_fibonacci(n);
        printf("Child Process ID: %d\n", getpid());
    } else {
        wait(NULL);
        printf("Parent Process: Child process has completed.\n");
    }

    return 0;
}
