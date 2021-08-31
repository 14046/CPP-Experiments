// Program implements the Coleman-Liau index to determine the reading level for text inputs

#include <cs50.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

// Prototypes
int countLetters(string text);
int countWords(string text);
int countSentences(string text);
float changeMagnitude(int quantityOne, int quantityTwo, int targetQuantityTwo);
int calculateIndex(int sentences, int words, int letters);
void printGrade();

// Global variables
int length, index;

int main(void)
{
    // Local variables
    string text;
    int letters, words, sentences;
    
    text = get_string("Text: ");
    length = strlen(text);
    letters = countLetters(text);
    words = countWords(text);
    sentences = countSentences(text);
    index = calculateIndex(sentences, words, letters);
    
    printGrade();
}

// Counts letters a-z & A-Z in a string
int countLetters(string text)
{
    int count = 0;
    
    for (int i = 0; i < length; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

// Counts words in a string, delimited by ' ' char
int countWords(string text)
{
    int count = 0;
    
    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            count++;
        }
    }
    count++;
    return count;
}

// Counts sentences in a string, delimited by chars '?', '!', and '.'
int countSentences(string text)
{
    int count = 0;
    
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '?' || text[i] == '!' || text[i] == '.')
        {
            count++;
        }
    }
    return count;
}

// Changes magnitude of ratio e.g. letters/words, sentences/words; returns first quantity in a ratio, after conversion
float changeMagnitude(int quantityOne, int quantityTwo, int targetQuantityTwo)
{
    float targetQuantityOne = (float) quantityOne / (float) quantityTwo;
    return targetQuantityOne *= targetQuantityTwo;
}

// Using the formula for the Coleman–Liau index, returns corresponding index
int calculateIndex(int sentences, int words, int letters)
{
    float result = 0.0588 * (changeMagnitude(letters, words, 100)) - 0.296 * (changeMagnitude(sentences, words, 100)) - 15.8;
    result = nearbyintf(result);
    return result;
}

// Determines whether index is <1, >= 16, or else, and prints respective grade
void printGrade()
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}