#include<cs50.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#define MAX_CANDIDATES 9
#define MAX_VOTERS 9
#include<math.h>
typedef struct
{
    int votes;
    string name;
    bool eliminated;
}
candidate;
int voter_count;
int candidate_count;
int preferences[MAX_VOTERS][MAX_CANDIDATES];
candidate candidates[MAX_CANDIDATES];
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminated(int min);
bool vote(int voter, int rank, string name);
int main(int argc, string argv[])
{
    if (argc > MAX_CANDIDATES || argc < 2)
    {
        // Checking if command line arguments are valid
        printf("Usage: ./plurality candidate names(upto 9 candidates)\n");
        exit(1);
    }
    candidate_count = argc - 1;
    // Storing names of candidates in the struct array
    for (int i = 1 ; i < argc ; i++)
    {
        candidates[i - 1].name = argv[i];
        candidates[i - 1].votes = 0;
        candidates[i - 1].eliminated = false;
    }
    int n = get_int("Number of voters: ");
    string name;
    voter_count = n;
    // For loop is only for the vote function
    for (int i = 0 ; i < n ; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            name = get_string("Rank %i: ", j + 1);
            vote(i, j, name);
            if (vote(i, j, name) == false)
            {
                exit (1);
            }
        }
        printf("\n");
    }
    do
    {
        tabulate();
        find_min();
    }
    while (print_winner() == false);
    
}

bool vote(int voter, int rank, string name)
{
    // Look for candidate called 'name'
    // If candidate found update array preferences
    int found = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            // Storing the index of the candidate
            found = 1 ;
            preferences [voter][rank] = j;
            break;
        }
    }
    if (found == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void tabulate(void)
{
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].eliminated == false)
        {
            for (int j = 0; j < voter_count; j ++)
            {
                if (i == preferences[j][0])
                {
                    candidates[i].votes = candidates[i].votes + 1 ;
                }
            }
        }
        else
        {
            for (int j = 0; j < voter_count; j ++)
            {
                int valid_candidate;
                int found = 0;
                if (i == preferences[j][found])
                {
                    do
                    {
                        valid_candidate = preferences[j][found + 1];
                    }
                    while(candidates[ valid_candidate].eliminated == true);
                    valid_candidate = preferences[j][found];
                    candidates[valid_candidate].votes = candidates[valid_candidate].votes + 1;

                }
            }
        }
    }
    print_winner();
}

bool print_winner(void)
{
    int n;
    if (voter_count % 2 == 0)
    {
        n = voter_count / 2 + 1 ;
        // Finding the majority of votes
    }
    else
    {
        n = round(voter_count / 2);
    }
    //Check if there is a winner and print the winner's name
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes == n)
            {
                printf("%s\n", candidates[i].name);
                return true;
            }
        }

    }
    return false;
}

int find_min(void)
{
     int min = 100;
    // Going to find the candidate with the minimum vote
    // Going to call eliminated and is_tie function
    for (int i = 0; i < candidate_count; i ++)
    {
        if (candidates[i].eliminated == false)
        {
           
            if (min > candidates[i].votes)
            {
                min = candidates[i].votes;
            }
        }
    }
    if (is_tie(min) == true)
    {
        print_winner();
    }
    eliminated(min);
    return min;
}

bool is_tie(int min)
{
    // Going to check if all the remaining candidates are tied
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min)
        {
            return false;
            
        }
    }
    return true;


}

void eliminated(int min)
{
    // Eliminates all candidates with min votes
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}



















