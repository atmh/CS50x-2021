#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Variables
    long n;
    int digits = 0;
    long temp;
    bool boo = false;

    // Prompt for number
    n = get_long("Number: ");

    // count digits
    temp = n;
    int count = 0;
    int sum = 0;
    while (temp > 0)
    {
        // odd digits
        if (count % 2 == 1)
        {
            int hello = temp % 10 * 2;
            if (hello > 9)
            {
                hello -= 9;
            }
            sum += hello;
        }
        // even digits
        else
        {
            sum += temp % 10;
        }
        temp = temp / 10;
        count++;
    }

    // print validity
    if (sum % 10 == 0)
    {
        //amex
        if (count == 15 && (n / 10000000000000 == 34 || n / 10000000000000 == 37))
        {
            printf("AMEX\n");
            boo = true;
        }

        // visa
        else if (count == 13 && n / 1000000000000 == 4)
        {
            printf("VISA\n");
            boo = true;
        }

        // visa / master
        else if (count == 16)
        {
            int f = n / 100000000000000;
            if (n / 1000000000000000 == 4)
            {
                printf("VISA\n");
                boo = true;
            }
            else if (f == 51 || f == 52 || f == 53 || f == 54 || f == 55)
            {
                printf("MASTERCARD\n");
                boo = true;
            }
        }
    }
    if (!boo)
    {
        printf("INVALID\n");
    }
}