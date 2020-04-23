#include <stdio.h>
#include <cs50.h>

int main (void)
{
    float f = get_float("Change: ");
    int change = 0;
    do
    {
        if (f > .25 || f == .25)
        {
            change++;
            f = f - .25;
        }
        if (f > .10 || f == .10)
        {
            change++;
            f = f - .10;
        }
        if (f > .05 || f == .05)
        {
            change++;
            f = f - .05;
        }
        if (f > .01 || f == .01)
        {
            change++;
            f = f - .01;
        }

    }
    while(f != 0);
    printf("%i\n", change);
}
