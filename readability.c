// @ author Devang Sharma
// Finding the U.S.A. Grade level for any text
// Using Coleman - Liau index

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

        if (((t > 96 && t < 123) || (t > 64 && t < 91)))
        {
            // Counting the number of Letters in the text
            l = l + 1;
        }
        else if (t == 46 || t == 63 || t == 33)
        {
            // Counting the numbers of sentences
            sent = sent + 1;
        }
        else if (t == 32)
        {
            // Counting the number of words
            w = w + 1;
        }

    }
    if (grade(w, sent, l) < 1)
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
// Function for the calculations
int grade(int w, int sent, int l)
{
    // Applying the Coleman-Liau index

    float L = 100 * (float)l / w;
    float S = 100 * (float)sent / w;
    float index = .0588 * L - .296 * S - 15.8;
    int result = round(index);
    return result;
}
