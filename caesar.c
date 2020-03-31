// @ author Devang Sharma
// Encryption code
#include<cs50.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, string argv[])
{
    string s;
    int key;
    if(argc == 2)
    {
        // validate that argument is integer
        // save it into variable
        //key = get_int(argv[1]);
       // printf ("< %s >< %i >",argv[0],atoi(argv[1]));
        key = atoi(argv[1]);
    }
    else
    {
        // print error message
        return 1;
    }
    if (key>=26 )
    {
        key = (key)%26;
    }
    else
    {
        key = (key + 0);
    }
    //int key = get_int("key: ");
    int n;

    s = get_string("plaintext: ");
    n = strlen(s);
    char y[n];
    printf("ciphertext: ");
    

    for (int i = 0; i < n; i++)
    {
      int t = (int)s[i] ; 
        if (64 <  t && t < 91 )
        {
            // Code for  lowercase letters
            if (t + key > 90 )
            {
                y[i] = (char)(t + key -122+ 96);
            }
            else
            {
                y[i] = (char)((int)s[i] + key);
            }
        }
        else if (96 < t && t < 123)
        {
            // Code for  uppercasecase letters
            if (t + key > 122  )
            {
                y[i] = (char)(t + key -122+ 96);
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
}