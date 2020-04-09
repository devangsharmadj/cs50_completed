// @ author Devang Sharma
// Voting program

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;
int candidate_count;
candidate t[MAX];
void print_winner(void);
bool vote(string name);
int main(int argc, string argv[])
{
    if (argc > MAX || argc < 2)
    {
        // Checking if command line arguments are valid
        printf("Usage: ./plurality candidate names(upto 9 candidates)\n");
        exit(1);
    }
    candidate_count = argc - 1;
    //int g[candidatesCount];
    // string h[ candidatesCount ];
    for (int i = 1 ; i < argc ; i++)
    {
        t[i - 1].name = argv[i];
        t[i - 1].votes = 0;
    }
    int n = get_int("Number of voters: ");
    string v[n];
    string name;
    for (int i = 0 ; i < n ; i ++)
    {
        v[i] = get_string("Vote: ");
        name = v[i];
        vote(name);
        if (vote(name) == false)
        {
            printf("Invalid Vote. \n");
        }
    }
    print_winner();
}

bool vote(string name)
{
    // Checking if the vote is valid
    // Updating vote total
    int found = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, t[j].name) == 0)
        {
            found = 1 ;
            t[j].votes = t[j].votes + 1;
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
void print_winner(void)
{
    // Storing the highest number of votes in a variable high
    int high = -1;
    for (int i = 0; i < candidate_count ; i ++)
    {
        if (high < t[i].votes)
        {
            high = t[i].votes;
        }
    }
    for (int i = 0 ; i < candidate_count ; i ++)
    {
        // If high matches the votes of the candidates
        // Print the candidates names
        if (high == t[i].votes)
        {
            printf("%s\n", t[i].name);
        }
    }
}



