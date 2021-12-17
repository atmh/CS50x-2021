#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // init variables
    int n;

    // Prompt for height
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // Print pyramid
    for (int i = 1; i <= n; i++)
    {
        // spaces before #
        for (int j = n; j > i; j--)
        {
            printf(" ");
        }

        // left #
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // center spaces
        printf("  ");

        // right spaces
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}