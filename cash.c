#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    do
    {
        float cash = get_float("Change owed: ");
    }
    while (cash < 0);
    // Converting the float to an int
    int dollars = round(cash * 100);
    int change = 0;
    do
    {
        if (dollars >= 25)
        {
            dollars -= 25;
            change ++;
        }
        else if (dollars >= 10)
        {
            dollars -= 10;
            change ++;
        }
        else if (dollars >= 5)
        {
            dollars -= 5;
            change ++;
        }
        else if (dollars >= 1)
        {
            dollars -= 1;
            change ++;
        }
    }
    while (dollars > 0);
    printf("%i\n", change);
}