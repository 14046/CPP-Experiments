#include <cs50.h>
#include <stdio.h>

void printAir();
void printBlock();
void printHole();

char block = '#', air = ' '; /* Initializes block (#) and empty ( ) characters.
Outside of main() so that variables can be used with print() functions */

int main(void)
{
    int height; // Declares height

    // Prompts user for height value, and loops if height is negative, zero, or greater than eight
    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);

    // First loop for each printed line, until height is reached
    for (int counter1 = 1; counter1 <= height; counter1++)
    {
        // Prints air
        for (int counter2 = 0; counter2 < (height - counter1); counter2++)
        {
            printAir();
        }

        // Prints blocks
        for (int counter3 = 0; counter3 < counter1; counter3++)
        {
            printBlock();
        }

        // Prints hole
        printHole();

        // Prints blocks
        for (int counter3 = 0; counter3 < counter1; counter3++)
        {
            printBlock();
        }

        // Prints new-line to start next layer
        printf("\n");
    }
}

void printAir()
{
    printf("%c", air);
};

void printBlock()
{
    printf("%c", block);
};

void printHole()
{
    printf("%c%c", air, air);
};