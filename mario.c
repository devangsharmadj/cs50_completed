#include<cs50.h>
#include<stdio.h>

int main(void)
{
    int n;
    do
    {
        n=get_int("Height:");
    }
    while(n<0 || n>9 );
    for(int i=0; i<n ; i++)
    {
        for( int j=0; j<n; j++)
        {
            if(n-1-i>j)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
            
        }
        printf("\n");
    }
}
