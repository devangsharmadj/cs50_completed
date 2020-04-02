#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

string grade(int w, int sent, int l);
int main(void)

{
    string s = get_string("Text: ");
    int sent = 0;
    int l = 0;
    int w = 1;

    for (int i = 0 ; i < strlen(s) ; i ++)
    {
        int t = (int)s[i];

         if(((t > 96 && t < 123) || (t > 64 && t < 91)))
         {
             l = l + 1;
         }
         else
         {
            l = l + 0;
         }



    }
    for (int i = 0 ; i < strlen(s) ; i ++)
    {
        int t = (int)s[i];

         if(t == 46 || t == 63 || t == 33)
         {
             sent = sent + 1;
         }
         else
         {
            sent = sent + 0;
         }
    }
    for (int i = 0 ; i < strlen(s) ; i ++)
    {
        int t = (int)s[i];
        if (t == 32)
        {
            w = w + 1;
        }
        else
        {
            w = w + 0;
        }
    }
    printf(" %s\n", grade(w,sent,l));
}

string grade(int w, int sent, int l)
{

    float L = 100 * l / w;
    float S = 100 * sent / w;
    float index = .0588 * L - .296 * S - 15.8;
    int result = round(index);
    string r;
    if (result < 1)
    {
        r = "Before Grade 1";
    }
    else if (result > 16)
    {
        r = "Grade 16+";
    }
    else
    {
        r = " Grade result";
    }
    return r;

}
