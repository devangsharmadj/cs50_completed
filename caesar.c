// @ author Devang Sharma
// Encryption code
#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, string argv[])
{

    int key;
    if (argc == 2)
    {
        string tempkey = argv[1] ;
        for (int i = 0 ; i < strlen(tempkey) ; i ++)
        {

            if ((int)tempkey[i] > 47 && (int)tempkey[i] < 58)
            {
                // Getting the right key
                key = atoi(argv[1]);
            }
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;

            }
        }

    }
    else
    {
        // Loop to make sure that the user puts in two things
        printf("Usage: ./caesar key\n");
        exit(1);
    }
    if (key >= 26)
    {
        // Simplifying the key
        key = (key) % 26;
    }
    else
    {
        key = (key + 0);
    }
    //int key = get_int("key: ");


    string s = get_string("plaintext: ");
    int n = strlen(s);
    char y[n];
    printf("ciphertext: ");


    for (int i = 0; i < n; i++)
    {
        int t = (int)s[i] ;
        if (64 <  t && t < 91)
        {
            // Code for lowercase letters
            if (t + key > 90)
            {
                // Code for if the letters go over z
                y[i] = (char)(t + key - 122 + 96);
            }
            else
            {
                y[i] = (char)((int)s[i] + key);
            }
        }
        else if (96 < t && t < 123)
        {
            // Code for  uppercasecase letters
            if (t + key > 122)
            {
                // Code for if the letters go over z
                y[i] = (char)(t + key - 122 + 96);
            }
            else
            {
                y[i] = (char)((int)s[i] + key);
            }
        }
        else
        {
            y[i] = s[i];
        }

    }
    for (int j = 0; j < n ; j++)
    {
        printf("%c", y[j]);
    }
    printf("\n");
    exit(0);
}
