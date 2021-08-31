#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    /* Checks if the given name matches any values within the array of candidate names,
    and increments its corresponding votecount */
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
        else
        {
            continue;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int highestVote = 0;

    // Looks through every element in an array of votes, and finds the element with the highest amount of votes
    for (int i = 0; i < (candidate_count - 1); i++)
    {
        if (candidates[i + 1].votes > candidates[highestVote].votes)
        {
            highestVote = i + 1;
        }
        else
        {
            continue;
        }
    }

    // Checks if any vote was made, and outputs 'No winners!' if no vote was made
    if (candidates[highestVote].votes > 0)
    {
        // Prints out the name of the winner whose name first appears in the 'names' field
        for (int i = 0, length = strlen(candidates[highestVote].name); i < length; i++)
        {
            printf("%c", candidates[highestVote].name[i]);
        }
        printf("\n");

        // Prints out the name(s) of any subsequent winner(s)
        for (int i = 0; i < candidate_count; i++)
        {
            if (i == highestVote)
            {
                continue;
            }
            else if (candidates[i].votes == candidates[highestVote].votes)
            {
                for (int j = 0, length = strlen(candidates[i].name); j < length; j++)
                {
                    printf("%c", candidates[i].name[j]);
                }
                printf("\n");
            }
            else
            {
                continue;
            }
        }
    }
    else
    {
        printf("No winners!\n");
    }
    return;
}