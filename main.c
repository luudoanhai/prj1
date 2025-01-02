#include <stdio.h>
#include <stdlib.h>
#include "Functions.h"

int main(int argc, char *argv[]) {
    int chooseMenu;
    do {
        displayMainMenu();
        scanf("%d", &chooseMenu);
        getchar();

        switch (chooseMenu) {
            case 1:
                displayStudentsMenu();
                break;
            case 2:
                printf("Coming Soon Feature 1\n");
                break;
            case 3:
                printf("Coming Soon Feature 2\n");
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid selection. Please try again.\n");
        }
    } while (chooseMenu != 0);

    return 0;
}
