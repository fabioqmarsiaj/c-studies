#include <stdio.h>

int main() {
    char name[50];
    int age;
    printf("State your name and age: \n");
    scanf("%s %d", name, &age);
    printf("Hello, %s! You have %d years old.\n", name, age);
    return 0;
}
