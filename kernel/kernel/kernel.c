#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

// Function to execute a command
void executeCommand(const char *command) {
    // Implement code to execute the specified command here.
    // For this example, we'll execute "hello" and "bye" commands.

    if (strcmp(command, "hello") == 0) {
        printf("Hello, World!\n");
    } else if (strcmp(command, "bye") == 0) {
        printf("Goodbye!\n");
    } else {
        printf("Unknown command: %s\n", command);
    }
}

// Function to read user input from GRUB
void readInput(char *buffer, int maxLength) {
    asm volatile (
        // Read user input from GRUB's command line.
        "mov $0x16, %%eax\n"
        "mov $0, %%ebx\n"            // File descriptor (stdin)
        "mov %0, %%ecx\n"            // Address of buffer
        "mov %1, %%edx\n"            // Maximum input length
        "int $0x80\n"

        // Null-terminate the input.
        "movb $0, (%0, %%eax, 1)\n"
        
        : : "m"(buffer), "i"(maxLength)
        : "eax", "ebx", "ecx", "edx"
    );
}

int main() {
    char inputBuffer[256];

    while (1) {
        // Display a prompt.
        printf("MyOS> ");

        // Read user input from GRUB
        readInput(inputBuffer, sizeof(inputBuffer));

        // Execute the user's command.
        executeCommand(inputBuffer);
    }

    return 0;
}
