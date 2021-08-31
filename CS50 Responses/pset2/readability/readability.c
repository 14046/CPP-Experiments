// Input text to receive reading level according to the Coleman-Liau index

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

// Global variables
int letters = 0, words = 0, sentences = 0, length, readingLevel;

// Function prototypes
void counter(char text[]);
int index();
void sortGrade(int x);

int main(void)
{
    string text;

    text = get_string("Text: ");
    length = strlen(text);

    // Counts letters, words, and sentences
    counter(text);

    // Calculates index and prints out grade
    sortGrade(index());
}

// Loops through indexes of lengths and increments variables according to ASCII code
void counter(char text[])
{
    for (int i = 0; i < length; i++)
    {
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            letters++;
        }
        else if (text[i] == 32)
        {
            words++;
        }
        else if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences++;
        }
    }
    words++;
}

// Runs Coleman-Liau index
int index()
{
    float L = ((float)letters / words) * 100;
    float S = ((float)sentences / words) * 100;
    return roundf((0.0588 * L) - (0.296 * S) - 15.8);
}

// Prints corresponding grade
void sortGrade(int x)
{
    if (x > 16)
    {
        printf("Grade 16+\n");
    }
    else if (x < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %d\n", x);
    }
}
