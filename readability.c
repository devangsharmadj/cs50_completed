#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int grade(int w, int sent, int l);
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
    if(grade(w, sent, l) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade(w, sent, l) > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade(w, sent, l));
    }
}

int grade(int w, int sent, int l)
{

    double L = 100 * l / w;
    double S = 100 * sent / w;
    float index = .0588 * L - .296 * S - 15.8;
    int result = round(index);
    
    
    return result;

}
