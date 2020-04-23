// @ author Devang Sharma
// Program to say hello, name
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Getting name of user
    string s = get_string("What is your name: ");
    // Printing hello, name
    printf("hello, %s\n", s);
}
