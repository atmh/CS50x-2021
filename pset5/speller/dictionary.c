// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 10000;
int count = 0;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int h = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        h = (h << 2) ^ word[i];
    }
    return h % N;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // copy to hash
    char words[LENGTH + 1];
    for (int i = 0; i < strlen(word); i++)
    {
        words[i] = tolower(word[i]);
    }
    words[strlen(word)] = '\0';
    int key = hash(words);
    node *checks = table[key];

    while (checks != NULL)
    {
        // word found
        if (strcasecmp(checks->word, words) == 0)
        {
            return true;
        }
        // otherwise
        else
        {
            checks = checks->next;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open dic
    FILE *dic = fopen(dictionary, "r");

    // if cant open
    if (dic == NULL)
    {
        return false;
    }

    // iterate through the dictionary
    char word[LENGTH + 1];
    while (fscanf(dic, "%s", word) != EOF)
    {
        // new word
        node *newNode = malloc(sizeof(node));

        // return false if failed
        if (newNode == NULL)
        {
            unload();
            return false;
        }
        // copy
        strcpy(newNode->word, word);
        newNode->next = NULL;
        int key = hash(newNode->word);
        node *head = table[key];

        // if null, create new head
        if (head == NULL)
        {
            table[key] = newNode;
            count++;
        }
        else
        {
            newNode->next = table[key];
            table[key] = newNode;
            count++;
        }
    }
    fclose(dic);
    return true;
}

// Returns number of word in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N ; i ++)
    {
        node *head = table[i];
        node *cursor = head;
        node *temp = head;

        while (cursor != NULL)
        {
            cursor = cursor -> next;
            free(temp);
            temp = cursor;
        }
    }
    return true;
}