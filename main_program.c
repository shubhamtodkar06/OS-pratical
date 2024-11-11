#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 10

// Function to sort the array (using Bubble Sort for simplicity)
void sort_array(int *arr, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[MAX_SIZE];
    int size;

    // Input the size of the array
    printf("Enter the number of elements in the array: ");
    scanf("%d", &size);

    // Input the elements of the array
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    // Sort the array in ascending order
    sort_array(arr, size);

    // Create a child process
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) {
        // Parent process
        // Wait for the child process to finish
        wait(NULL);
        printf("Parent: Array sorted and passed to the child process.\n");
    }
    else {
        // Child process
        // Prepare arguments for execve
        char *args[MAX_SIZE + 2];  // Array to store command-line arguments
        args[0] = "./reverse_array";  // Path to the new program to load
        for (int i = 0; i < size; i++) {
            // Convert each integer to a string and add to args
            char str[10];
            sprintf(str, "%d", arr[i]);
            args[i + 1] = strdup(str);
        }
        args[size + 1] = NULL;  // Null-terminate the arguments array

        // Execute the reverse_array program with the sorted array as arguments
        execve(args[0], args, NULL);

        // If execve fails
        perror("execve failed");
        exit(1);
    }

    return 0;
}
