// Write a program that calls fork(). Before calling fork(),
// have the main process access a variable (e.g., x) and 
// set its value to something (e.g., 100). 
// What value is the variable in the child process? 
// What happens to the variable when both the child and parent change the value of x?

#include <stdio.h>  // For Standard Input/Output
#include <unistd.h> // For System Calls

#include <stdio.h>  // For Standard Input/Output
#include <unistd.h> // For System Calls

int main() {
    int x = 100;  // Initialize the variable x
    int pid = fork();  // Create a new process

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("In Child process...\n");
        printf(" Before increment: x = %d\n", x);
        x++;  // Modify x in the child process
        printf(" After increment: x = %d\n", x);
    }
    else {
        // Parent process
        printf("In Parent process...\n");
        printf(" Before decrement: x = %d\n", x);
        x--;  // Modify x in the parent process
        printf(" After decrement: x = %d\n", x);
    }

    return 0;
}

// fork() creates copy of parent process. However, child and parent process have their own private address space exclusive of each other. Both process (child and parent) can't interfare in each other's address space (memory).
// So, each maintain their own copy of variables.