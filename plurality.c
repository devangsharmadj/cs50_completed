// @ author Devang Sharma
// Voting program

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    string names;
    int votes;
}
candidates;

void print(candidates t[], int candidatesCount);
bool vote(string m, candidates t[], int candidatesCount);
int main(int argc, string argv[])
{
    if (argc > 9 || argc < 2)
    {
        // Checking if command line arguments are valid
        printf("Give voter names\n");
        exit(1);
    }
    int candidatesCount = argc - 1;
    //int g[candidatesCount];
    // string h[ candidatesCount ];
    candidates t[candidatesCount];
    for (int i = 1 ; i < argc ; i++)
    {
        t[i - 1].names = argv[i];
        t[i - 1].votes = 0;
    }
    int n = get_int("Number of voters: ");
    string v[n];
    string names;
    string m;
    for (int i = 0 ; i < n ; i ++)
    {
        v[i] = get_string("Vote: ");
        m = v[i];
        vote(m, t,  candidatesCount);
    }
    print(t,  candidatesCount);
}

bool vote(string m, candidates t[], int candidatesCount)
{
    // Checking if the vote is valid
    // Updating vote total
    int found = 0;
    for (int j = 0; j < candidatesCount; j++)
    {
        if (strcmp(m, t[j].names) == 0)
        {
            found = 1 ;
            t[j].votes = t[j].votes + 1;
            break;
        }
    }
    if (found == 0)
    {
        printf("Invalid vote. \n");
    }
    return true;
}
void print(candidates t[], int candidatesCount)
{
    // Storing the highest number of votes in a variable high
    int high = -1;
    for (int i = 0; i <  candidatesCount ; i ++)
    {
        if (high > t[i].votes)
        {
            true;
        }
        else if (high < t[i].votes)
        {
            high = t[i].votes;
        }
    }
    for (int i = 0 ; i < candidatesCount ; i ++)
    {
        // If high matches the votes of the candidates
        // Print the candidates names
        if (high == t[i].votes)
        {
            printf("%s", t[i].names);
            printf("\n");
        }
    }
}



