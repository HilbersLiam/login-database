#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 13
#define MAX_INPUT_LENGTH_STRING "12"
#define MAX_LINE_LENGTH 256

int main(int argc, char* argv[]) {
	// All Variables
    FILE* fp; // File Pointer
    fp = fopen(argv[1], "r+"); // File open
    char username[MAX_INPUT_LENGTH];
    char line[MAX_LINE_LENGTH];
    char userInput[MAX_INPUT_LENGTH];
    char passInput[MAX_INPUT_LENGTH];
    int usernameFound = 0;
    int numOfAttempts = 5;
    int incorrectPassword = 0;

	// Open file check for errors
    if (fp != NULL) {
        printf("Opening \"%s\" file...\n", argv[1]);
    } else {
        printf("Error opening \"%s\" file\n", argv[1]);
        return 1;
    }
// Keep looping
while(1){
    printf("Enter username: \n");
    if (scanf("%" MAX_INPUT_LENGTH_STRING "s", userInput) != 1 || strlen(userInput) >= MAX_INPUT_LENGTH) {
        printf("Error: Invalid username input\n");
        return 1;
    }

    fseek(fp, 0, SEEK_SET); // Move the file pointer to the beginning of the file

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, "Username: ") != NULL) {
            if (sscanf(line, "Username: %" MAX_INPUT_LENGTH_STRING "s", username) == 1) {
                if (strcasecmp(username, userInput) == 0) {
                    printf("Enter password: \n");
                    if (scanf("%" MAX_INPUT_LENGTH_STRING "s", passInput) != 1 || strlen(passInput) >= MAX_INPUT_LENGTH) {
                        printf("Error: Invalid password input\n");
                        return 1;
                    }

                    if (fgets(line, sizeof(line), fp) != NULL) {
                        char storedPassword[MAX_INPUT_LENGTH];
                        if (sscanf(line, "Password: %" MAX_INPUT_LENGTH_STRING "s", storedPassword) == 1) {
                            if (strcmp(passInput, storedPassword) == 0) {
                                usernameFound = 1;
                                break;
                            } else {
                                while (numOfAttempts != 0){ // While the users attempts does not equal the number of tries available.
                                    numOfAttempts = numOfAttempts -1;
                                    if (numOfAttempts == 0){
                                        printf("Too many attempts\n");
							  printf("Login unsucessfull\n");
                                        break;
                                    }
                                    printf("Incorrect password. You have %d tries left!\n", numOfAttempts);
                                    printf("Enter Password: ");
                                    scanf("%s", passInput);
                                    
                                    if (strcmp(passInput, storedPassword) == 0) {
                                        usernameFound = 1;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (usernameFound) {
        printf("Login successful\n");
        exit(1);
    } else {
        printf("Username not found in the file\n");

        printf("Do you want to create an account? (Y/N)\n");
        char createAccount;
        scanf(" %c", &createAccount);

        if (createAccount == 'Y' || createAccount == 'y') {
            char createUser[MAX_INPUT_LENGTH];
            char createPass[MAX_INPUT_LENGTH];

            printf("Account Creation\n");
            printf("Enter desired username (Must be less than %d characters): \n", MAX_INPUT_LENGTH - 1);
            if (scanf("%" MAX_INPUT_LENGTH_STRING "s", createUser) != 1 || strlen(createUser) >= MAX_INPUT_LENGTH) {
                printf("Error: Invalid username input\n");
                return 1;
            }

            printf("Enter desired password (Must be less than %d characters): \n", MAX_INPUT_LENGTH - 1);
            if (scanf("%" MAX_INPUT_LENGTH_STRING "s", createPass) != 1 || strlen(createPass) >= MAX_INPUT_LENGTH) {
                printf("Error: Invalid password input\n");
                return 1;
            }

            fseek(fp, 0, SEEK_END); // Move the file pointer to the end of the file
            fprintf(fp, "\nUsername: %s\nPassword: %s\n", createUser, createPass);
            printf("Account created successfully\n");
        } else {
            printf("Goodbye\n");
            exit(1);
        }
    }

    
}
    fclose(fp);

    return 0;
}