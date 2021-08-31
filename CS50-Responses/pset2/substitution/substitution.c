// Takes key as CLI argument, and then takes input of plaintext, to convert into ciphertext, using key

#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Global Variables
string error = "Enter a key\n";
char alphabet[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
                     'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
                    };

// Function prototypes
bool checkKey(string key);
bool checkLength(string key);
bool checkAlphabet(string key);
bool checkRecurring(string key);
void encrypt(string plaintext, string key);

int main(int argc, string argv[])
{
    // Returns error when no key is entered
    if ((argc != 2) || (checkKey(argv[1]) == false))
    {
        printf("%s", error);
        return 1;
    }
    else
    {
        // Gets plaintext input, calls function to encrpy it, and prints ciphertext output
        string plaintext = get_string("plaintext: ");
        encrypt(plaintext, argv[1]);
        return 0;
    }
}

// Verifies length, alphabet, and recurring tests
bool checkKey(string key)
{
    if (checkLength(key) == true && checkAlphabet(key) == true && checkRecurring(key) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Test to check if length of key is 26
bool checkLength(string key)
{
    if (strlen(key) == 26)
    {
        return true;
    }
    else
    {
        error = "Key must contain 26 letters\n";
        return false;
    }
}

// Test to check if key only contains alphabetical characters
bool checkAlphabet(string key)
{
    for (int i = 0; i < 26; i++)
    {
        if ((key[i] >= 65 && key[i] <= 90) || (key[i] >= 97 && key[i] <= 122))
        {
            continue;
        }
        else
        {
            error = "Key must only contain alphabetical characters";
            return false;
        }
    }
    return true;
}

// Test to see if key contains recurring characters
bool checkRecurring(string key)
{
    // Array to store capital letters, for later reversion
    int capital[25];
    for (int i = 0; i < 26; i++)
    {
        capital[i] = 0;

        // Iterates through every element of key to check every previous character, case-insensitive
    }
    for (int i = 0; i < 26; i++)
    {
        if (key[i] >= 65 && key[i] <= 90)
        {
            key[i] += 32;
            capital[i] = key[i];
        }
        if (i > 0)
        {
            for (int j = i; j > 0; j--)
            {
                if (key[i] == key[j - 1])
                {
                    error = "Key must contain one of each letter";
                    return false;
                }
            }
        }
    }

    // Reverts letters that were originally capitalized
    for (int i = 0; i < 26; i++)
    {
        if (capital[i] != 0)
        {
            key[i] = capital[i] - 32;
        }
    }
    return true;
}

// Uses key to encrypt plaintext and prints out ciphertext
void encrypt(string plaintext, string key)
{
    // Stores length of plaintext, creates ciphertext, and copies plaintext to ciphertext
    int length = strlen(plaintext);
    char ciphertext[length];
    strcpy(ciphertext, plaintext);

    // Iterates through every element, checks for corresponding letter in alphabet, and replaces it with the key-equivalent
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (ciphertext[i] == alphabet[j] || ciphertext[i] == alphabet[j] - 32 || ciphertext[i] == alphabet[j] + 32)
            {
                if (ciphertext[i] >= 65 && ciphertext[i] <= 90 && key[j] >= 65 && key[j] <= 90)
                {
                    ciphertext[i] = key[j];
                }
                else if (ciphertext[i] >= 97 && ciphertext[i] <= 122 && key[j] >= 97 && key[j] <= 122)
                {
                    ciphertext[i] = key[j];
                }
                else if (ciphertext[i] >= 65 && ciphertext[i] <= 90 && key[j] >= 97 && key[j] <= 122)
                {
                    ciphertext[i] = key[j] - 32;
                }
                else if (ciphertext[i] >= 97 && ciphertext[i] <= 122 && key[j] >= 65 && key[j] <= 90)
                {
                    ciphertext[i] = key[j] + 32;
                }
                break;
            }
        }
    }
    // Prints every element in ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < length; i++)
    {
        printf("%c", ciphertext[i]);
    }
    printf("\n");
}