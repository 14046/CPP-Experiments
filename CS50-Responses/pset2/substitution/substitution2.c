/* User inputs key as the following argument in the command-line.
Program takes plaintext as input, and encrpyts it according to the provided key,
then returns the ciphertext, or encrpyted text, as the output. */

#include <cs50.h>
#include <string.h>
#include <stdio.h>

// Prototypes
bool checkAlphabetical(string input);
bool checkRecurring(string input);

int main(int argc, string argv[])
{
    // First test checks if user inputted an argument following the program name at the command-line
    if (argc == 2)
    {
        // Second test checks whether the argument, or key, has a length of 26, corresponding to the alphabet
        if (strlen(argv[1]) == 26)
        {
            // Third test checks whether the key only contains alphabetical characters
            if (checkAlphabetical(argv[1]) == true)
            {
                // Fourth test checks if there are any recurring characters in the key
                if (checkRecurring(argv[1]) == false)
                {
                    string plainText = get_string("plaintext: ");
                    int lengthAlphabet = 26, lengthPlainText = strlen(plainText);
                    char cipherText[lengthPlainText];
                    string alphabet = "abcdefghijklmnopqrstuvwxyz";
                    string key = argv[1];
    
                    /* First loop goes through every element in plainText[].
                    The second loops goes through every element in alphabet[] until there is a match with plainText[].
                    Using the element in key[] with the corresponding index position to alphabet[], indexes into
                    cipherText[] the value from key[]. This process handles case-sensitivity and special characters. */
                    
                    for (int i = 0; i < lengthPlainText; i++)
                    {
                        for (int j = 0; j < lengthAlphabet; j++)
                        {
                            if ((plainText[i] == alphabet[j]) || (plainText[i] == alphabet[j] + 32) || (plainText[i] == alphabet[j] - 32))
                            {
                                if ((plainText[i] >= 'a' && plainText[i] <= 'z') && (key[j] >= 'a' && key[j] <= 'z'))
                                {
                                    cipherText[i] = key[j];
                                    break;
                                }
                                else if ((plainText[i] >= 'A' && plainText[i] <= 'Z') && (key[j] >= 'A' && key[j] <= 'Z'))
                                {
                                    cipherText[i] = key[j];
                                    break;
                                }
                                else if ((plainText[i] >= 'a' && plainText[i] <= 'z') && (key[j] >= 'A' && key[j] <= 'Z'))
                                {
                                    cipherText[i] = key[j] + 32;
                                    break;
                                }
                                else if ((plainText[i] >= 'A' && plainText[i] <= 'Z') && (key[j] >= 'a' && key[j] <= 'z'))
                                {
                                    cipherText[i] = key[j] - 32;
                                    break;
                                }
                            }
                            else
                            {
                                cipherText[i] = plainText[i];
                                continue;
                            }
                        }
                    }
                    
                    // Prints out ciphertext by looping through each element in cipherText[]
                    printf("ciphertext: ");
                    for (int i = 0; i < lengthPlainText; i++)
                    {
                        printf("%c", cipherText[i]);
                    }
                    printf("\n");
                }
                else
                {
                    // Prints error message for repeated characters; ends program with error code 1
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
            else
            {
                // Prints error message for containing non-alphabetical characters; ends program with error code 1
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
        }
        else
        {
            // Prints error message for having a key with a length < 26 or > 26; ends program with error code 1
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        // Prints error message for having 0, or 2+ arguments at the command-line (not considering the program name itself)
        printf("Usage: ./substitution key\n");
        return 1;
    }
}


// Returns true when the input only contains alphabetical characters
bool checkAlphabetical(string input)
{
    for (int i = 0; i < 26; i++)
    {
        if (((input[i] >= 'a') && (input[i] <= 'z')) || ((input[i] >= 'A') && (input[i] <= 'Z')))
        {
            continue;
        }
        else
        {
            return false;
        }
    }
    return true;
}

// Checks for recurring characters in an input, returns true if so
bool checkRecurring(string input)
{
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if ((input[i] == input[j]) || (input[i] == input[j] + 32) || (input[i] == input[j] - 32))
            {
                return true;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}