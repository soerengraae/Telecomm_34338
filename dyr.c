#include <stdio.h>
#include <stdbool.h>

// Define the Animal structure
struct Animal {
    char family[50];
    double weight;
    bool alive;
    char placeOfCapture[100];
    int age;
};

// Function to print the details of an Animal
void printAnimal(struct Animal a) {
    printf("Animal Information:\n");
    printf("Family: %s\n", a.family);
    printf("Weight: %.2f kg\n", a.weight);
    printf("Alive: %s\n", a.alive ? "Yes" : "No");
    printf("Place of Capture: %s\n", a.placeOfCapture);
    printf("Age: %d years\n", a.age);
    printf("\n");
}

int main() {
    // Declare and initialize two Animal instances
    struct Animal lion = {"Felidae", 190.0, true, "Masai Mara, Kenya", 8};
    struct Animal elephant = {"Elephantidae", 5400.0, true, "Chobe National Park, Botswana", 25};

    // Print their details using the printAnimal function
    printAnimal(lion);
    printAnimal(elephant);

    return 0;
}