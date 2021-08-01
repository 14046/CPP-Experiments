#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

// Custom function prototype
bool checkCycle(int vertice, int originalVertice);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();

    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        // Second loop is for iterating through every element
        for (int j = 0; j < candidate_count; j++)
        {
            for (int k = j + 1; k < candidate_count; k++)
            {
                if (preferences[j][k] > preferences[k][j])
                {
                    pairs[i].winner = j;
                    pairs[i].loser = k;
                    pair_count++;
                    i++;
                }
                else if (preferences[j][k] < preferences[k][j])
                {
                    pairs[i].winner = k;
                    pairs[i].loser = j;
                    pair_count++;
                    i++;
                }
                else
                {
                    continue;
                }
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int tempWinner, tempLoser;

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > preferences[pairs[i].winner][pairs[i].loser])
            {
                tempWinner = pairs[j].winner;
                tempLoser = pairs[j].loser;
                pairs[j].winner = pairs[i].winner;
                pairs[j].loser = pairs[i].loser;
                pairs[i].winner = tempWinner;
                pairs[i].loser = tempLoser;
            }
            else
            {
                continue;
            }
        }
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        for (int j = i - 1; j >= 0; j--)
        {
            if (locked[pairs[j].winner][pairs[i].winner] == true)
            {
                if (checkCycle(j, i) == true)
                {
                    locked[pairs[i].winner][pairs[i].loser] = false;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
    }
}

// (CUSTOM FUNCTION) Checks connected locks for any cycles
bool checkCycle(int vertice, int originalVertice)
{
    if (locked[pairs[originalVertice].winner][pairs[vertice].winner] == true)
    {
        return true;
    }
    else
    {
        for (int i = vertice - 1; i >= 0; i--)
        {
            if (locked[pairs[i].winner][pairs[vertice].winner] == true)
            {
                if (checkCycle(i, originalVertice) == true)
                {
                    return true;
                }
                else
                {
                    continue;
                }
            }
            else
            {
                continue;
            }
        }
        return false;
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool lock = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                lock = true;
            }
            else
            {
                continue;
            }
        }
        if (lock == false)
        {
            for (int k = 0, length = strlen(candidates[i]); k < length; k++)
            {
                printf("%c", candidates[i][k]);
            }
            printf("\n");
        }
        else
        {
            continue;
        }
    }

    return;
}