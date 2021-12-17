#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

int main(void)
{
    string text = get_string("Text: ");
    int l_count = 0;
    int w_count = 1;
    int s_count = 0;

    // count no. of words
    for (int i = 0; i < strlen(text); i++)
    {
        // letters
        if ((tolower(text[i]) >= 'a' && tolower(text[i]) <= 'z'))
        {
            l_count++;
        }

        // words
        else if (text[i] == ' ')
        {
            w_count++;
        }

        // sentences
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            s_count++;
        }
    }

    // calculate grade
    float grade = 0.0588 * (100 * (float) l_count / (float) w_count) - 0.296 * (100 * (float) s_count / (float) w_count) - 15.8;

    // print grade
    if (grade >= 0 && grade < 16)
    {
        printf("Grade %i\n", (int) round(grade));
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Before Grade 1\n");
    }
}