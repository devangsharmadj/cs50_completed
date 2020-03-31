// @ author Devang Sharma
// Encryption code

#include<cs50.h>
#include<stdio.h>
#include<string.h>



int main(int argc, string argv[])

{

    string s;
    int key;
    if(argc == 2)
    {
        // validate that argument is integer
        // save it into variable key
        key = (int)argv[1];
    }
    else
    {
        // print error message
        return 1;
    }
    //int key = get_int("key: ");
    int n;

    s = get_string("plaintext: ");
    n = strlen(s);
    char y[n];
    printf("ciphertext: ");

    for (int i = 0; i < n; i++)
    {
        if ((int)s[i] > 47 && (int)s[i] < 65)
        {
            // Code for numbers
            y[i] = s[i];
        }
        else  if ((int)s[i] + key > 122)
        {
            // Code for when the integer value of lowercase number goes over z
            y[i] = (char)((int)s[i] + key - 122 + 96) ;
        }
        else
        {
            if ((int)s[i] + key > 91 && (int)s[i] + key < 96)
            {
                // Code for if the integer value goes over capital Z
                y[i] = (char)((int)s[i] + key - 91 + 65);
            }
            else
            {
                // Code for normal letters
                y[i] = (char)((int)s[i] + key);
            }
        }
        
    }
    for (int j = 0; j < n ; j++)
    {
        printf("%c", y[j]);
    }
    printf("\n");
}