#include <stdio.h>

enum primaryColors { RED, GREEN, BLUE };


const char* getValue(enum primaryColors color) {
    switch (color) {
        case RED:
            return "RED";
        case GREEN:
            return "GREEN";
        case BLUE:
            return "BLUE";
        default:
            return "UNKNOWN";
    }
}


int main() {
    char name[50];
    int age, colorChoice;
    printf("State your name and age: \n");
    scanf("%s %d", name, &age);
    printf("Hello, %s! You have %d years old.\n", name, age);

    
    enum primaryColors favoriteColor;

    printf("Which is your favorite primary color? (0 for RED, 1 for GREEN, 2 for BLUE): ");
    scanf("%d", &colorChoice);

    switch (colorChoice) {
        case RED:
            favoriteColor = RED;
            printf("You chose RED!\n");
            break;
        case GREEN:
            favoriteColor = GREEN;
            printf("You chose GREEN!\n");
            break;
        case BLUE:
            favoriteColor = BLUE;
            printf("You chose BLUE!\n");
            break;
        default:
            printf("Invalid choice!\n");
            break;
    }

    printf("Your favorite color is: %s\n", getValue(favoriteColor));

    return 0;
}
