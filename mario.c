// @ author Devang Sharma
// Program to build 2 adjacent pyramids


#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n ;
    do
    {
        // do-while loop to make sure that the user cooperates
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    for (int i = 0; i < n; i ++)
    {
        // Loop for printing rows
        for (int j = 0; j < n ; j++)
        {
            // Loop for printing the columns of the first pyramid 
            if (n - 1 - i > j)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("  ");
        // This print is for printing the spaces between the pyramids
        for (int j = 0; j < i + 1; j++)
            // Loop for printing the columns of the second pyramid
        {
            printf("#");
        }
        // Printing new line
        printf("\n");
    }
}
