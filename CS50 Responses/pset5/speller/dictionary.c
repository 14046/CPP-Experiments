// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

// Global function to count number of nodes
int nodes = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);

    if (table[index] == NULL)
    {
        return false;
    }

    node *cursor = table[index];

    for (int i = 0; i < N + 1; i++)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        else
        {
            if (cursor->next == NULL)
            {
                break;
            }
            cursor = cursor->next;
        }
    }

    return false;
}

// Hashes word to a number
// Modified djib2 function from https://www.reddit.com/r/cs50/comments/eo4zro/good_hash_function_for_speller/
unsigned int hash(const char *word)
{
    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);

    while (*word != 0)
    {
    hash = ((hash << 5) + hash) + c;
    c = *word++;
    c = tolower(c);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    char word[LENGTH + 1];

    if (dict == NULL)
    {
        printf("Couldn't open dictionary");
        return false;
    }

    node *n = NULL;

    while (fscanf(dict, "%s", word) != EOF)
    {
        n = malloc(sizeof(node));

        if (n == NULL)
        {
            printf("Could not allocate memory");
            return false;
        }

        strcpy(n->word, word);
        n->next = NULL;

        unsigned int index = hash(n->word);

        if (table[index] == NULL)
        {
            table[index] = n;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }

        nodes++;
    }

    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return nodes;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i <= N + 1; i++)
    {
        if (i == N + 1)
        {
            return true;
        }
        if (table[i] == NULL)
        {
            continue;
        }
        else
        {
            node *cursor = table[i];
            node *tmp = table[i];

            while (true)
            {
                if (cursor->next == NULL)
                {
                    free(cursor);
                    break;
                }
                cursor = cursor->next;
                free(tmp);
                tmp = cursor;
            }
        }
    }

    return false;
}
