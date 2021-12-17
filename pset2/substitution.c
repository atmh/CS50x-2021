#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void encrypt(); // convert to substituion cipher
void alpha_val(char pos, string key); // convert alphabet to 0 to 26

int main(int argc, string argv[])
{
    if (argc == 2) // 2 lines
    {
        if (strlen(argv[1]) == 26) // 26 alphabets
        {
            for (int i = 0; i < strlen(argv[1]); i++) // iterate through the string
            {
                if (!isalpha(argv[1][i])) // not alphabet
                {
                    printf("Key must contain 26 characters.\n");
                    return 1;
                }
                for (int j = i + 1 ; j < strlen(argv[1]); j++) // checking repeated element
                {
                    if (toupper(argv[1][j]) == toupper(argv[1][i]))
                    {
                        printf("Key must not contain repeated alphabets.\n");
                        return 1;
                    }
                }
            }
            encrypt(argv[1]);
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    return 0;
}


// convert to substituion cipher
void encrypt(string key)
{
    string pt = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; i < strlen(pt); i++)
    {
        if (isalpha(pt[i])) // if alphabet
        {
            char x = pt[i];
            if (islower(pt[i]))  // lower
            {
                alpha_val(tolower(x), key);
            }
            else                // upper
            {
                alpha_val(toupper(x), key);
            }
        }
        else
        {
            printf("%c", pt[i]); // special characters
        }
    }
    printf("\n");
}

// alphabet to array index
void alpha_val(char pos, string key)
{
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // alphabet

    for (int i = 0; i < strlen(alphabet); i++) // iterating through the alphabets
    {
        if (islower(pos))   // lower
        {
            if (pos == tolower(alphabet[i]))
            {
                printf("%c", tolower(key[i]));
            }
        }
        else                // upper
        {
            if (pos == toupper(alphabet[i]))
            {
                printf("%c", toupper(key[i]));
            }
        }
    }
}