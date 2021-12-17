#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Start, end, years variables
    int start;
    int end;
    int years = 0;

    // Prompt for start size
    do 
    {
        start = get_int("Start size: ");
    }
    while (start < 9);


    // Prompt for end size
    do 
    {
        end = get_int("End size: ");
    }
    while (end < start);


    // Calculate number of years until we reach threshold
    while (start < end) 
    {
        start = start + start / 3 - start / 4;
        years++;
    }

    // Print number of years
    printf("Years: %i", years);

}