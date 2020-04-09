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


    if(argc > 9 || argc < 2)
    {
        printf("Give voter names\n");
        exit (1);
    }
    int candidatesCount = argc-1;
    //int g[candidatesCount];
   // string h[ candidatesCount ];
   candidates g[candidatesCount];
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

    for (int i = 0 ; i < n ; i ++ )
    {
        v[i] = get_string("Vote: ");
         m = v[i];
        vote(m, t,  candidatesCount);
    }
     print(t,  candidatesCount);
}

bool vote(string m, candidates t[], int candidatesCount)
{



        int found = 0;
        for (int j = 0 ; j < candidatesCount  ; j ++)
         {

            if (strcmp(m, t[j].names)==0)
            {

                found = 1 ;
                t[j].votes = t[j + 1].votes + 1;

                break;
            }
        }
        if ( found == 0)
        {
            printf("Invalid vote. \n");

        }

    return true;

}
void print(candidates t[], int candidatesCount)
{
    string s;
    int high =-1;


    for (int i = 0; i <  candidatesCount ; i ++)
    {
        
        
       if(high > t[i].votes)
           {
                 true;
                
           }
           else if(high < t[i].votes)
           {
               high = t[i].votes;
               s = t[i].names;
                
           }
           else if(t[i].votes == high)
           {

                s = strcat(s,t[i].names) ;
                

           }
    }
    printf("%s", s);

}



