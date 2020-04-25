// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <cs50.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;
// Number of words in dictionary
unsigned int dictionary_word_count = 0; 

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Checking if the word has been found
    int found = 1;
    int hash_number = hash(word);
    // Temporary variable
    node *tmp = table[hash_number];
    while (tmp != NULL)
    {
        if (strcasecmp(word, tmp->word) == 0)
        {
            found = 0;
            break;
        }
        tmp = tmp->next;
    }
    // Returning the value of found
    return found;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Simple hash function for first letter of each word. 
    // Hash code for uppercase letters
    if ((int)word[0] > 64 && (int)word[0] < 91)
    {
        return ((int)word[0] + 32) % N;
    }
    else
    {
        return (int)word[0] % N;
    }
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Opening dictionary
    //FILE *dictionaryp = fopen(dictionary, "r");
    //if (dictionaryp == NULL)
    //{
      //  printf("Error opening dictionary\n");
       // return false;
    //}
    // Reading strings one at a time
    //int buffer;
    char *dictionary_word = "Null";
    //do
    //{
      //  buffer = fscanf(dictionaryp, "%s", dictionary_word);
        //if (buffer == EOF)
        //{
          //  break;
        //}
        // Creating a new node for each node
        node *n = malloc(sizeof(node));
        // Checking if memory allocated successfuly
        if (n == NULL)
        {
            // Printing error message
            printf("Error loading words\n");
            return false;
        }
        // Updating word count for dictionaries
        dictionary_word_count = dictionary_word_count + 1;
        // Copying dictionary word into the node;
        strcpy(n->word, dictionary_word);
        // Hashing word
        int hash_number = hash(dictionary_word);
        // Insering Node into array
        n->next = table[hash_number];
        table[hash_number] = n;
    //}
    //while (buffer != EOF);
    // Closing Dictionary
    //fclose(dictionaryp);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionary_word_count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i ++)
    {
        node *tmp = NULL;
        while (table[i] != NULL)
        {
            tmp = table[i] -> next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
