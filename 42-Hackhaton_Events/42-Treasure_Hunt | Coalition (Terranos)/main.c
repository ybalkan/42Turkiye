#include <stdio.h>
#include <string.h>
#include "data.h"

void reveal(unsigned char *s) {
    printf("\n=================================================================\n");
    for (int i = 0; s[i]; i++) printf("%c", s[i] ^ 42);
    printf("\n=================================================================\n");
}

int main() {
    char input[10];
    
    printf("\n  _______                                  _    _             _   \n");
    printf(" |__   __|                                | |  | |           | |  \n");
    printf("    | | _ __ ___  __ _ ___ _   _ _ __ ___ | |__| |_   _ _ __ | |_ \n");
    printf("    | || '__/ _ \\/ _` / __| | | | '__/ _ \\|  __  | | | | '_ \\| __|\n");
    printf("    | || | |  __/ (_| \\__ \\ |_| | | |  __/| |  | | |_| | | | | |_ \n");
    printf("    |_||_|  \\___|\\__,_|___/\\__,_|_|  \\___||_|  |_|\\__,_|_| |_|\\__|\n");


    while (1) {
        printf("\nSelect a data size (QR) or type ‘exit’ to quit : ");
        
        if (scanf("%9s", input) != 1) {
            continue;
        }

        if (strcmp(input, "exit") == 0) {
            printf("\nExiting the system...\n");
            break;
        }
        else if (strcmp(input, "b") == 0) reveal(b);
        else if (strcmp(input, "n") == 0) reveal(n);
        else if (strcmp(input, "B") == 0) reveal(B);
        else if (strcmp(input, "KB") == 0) reveal(KB);
        else if (strcmp(input, "MB") == 0) reveal(MB);
        else if (strcmp(input, "GB") == 0) reveal(GB);
        else if (strcmp(input, "TB") == 0) reveal(TB);
        else printf("Invalid size!");
    }
    return 0;
}