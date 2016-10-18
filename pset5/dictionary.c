/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <stdbool.h>

#include "dictionary.h"

// default dictionary
#define DICTIONARY "/home/cs50/pset5/dictionaries/large"

typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;

node* root;

int word_count = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // Initializes the variables
    int i = 0;
    int c = 0;
    node* ptr = root;
    
    // While the string is not finished
    while (word[i] != '\0')
    {
        c = tolower(word[i]);
        
        // If it is a letter
        if (c != 39)
        {
            c = c - 'a';
        }
            
        // If it is an apostrophe
        else
        {
            c = 26;
        }
        
        // If the pointer does not exist, the word is misspelled
        if (ptr->children[c] == NULL)
        {
            return false;
        }
        
        // Then, make the pointer progress to the next node
        else
        {
            ptr = ptr->children[c];
        }
        
        i++;
        
    }
    
    // If 'is_word' is true, then it is a word
    if (ptr->is_word == true)
    {
        return true;
    }
    
    // In the other case, the word is misspelled
    else
    {
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // Initializes the trie
    root = malloc(sizeof(node));
    root->is_word = NULL;
    node* ptr = NULL;
    int index = 0;
    
    // Sets the children to NULL
    for (int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }
    
    // Sets pointer to root
    ptr = root;
    
    // Opens the dictionary
    FILE* dict = fopen(dictionary, "r");
    
    if (dict == NULL)
    {
        printf("Could not open the dictionary\n");
        free(root);
        return false;
    }
    
    // Reads the dictionary
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        // 10 is the ASCII value for a new line
        if (c != 10)
        {
            // 39 is the ASCII value for the apostrophe
            if (c != 39)
            {
                index = tolower(c) - 'a';
            }
            
            else
            {
                index = 26;
            }
            
            // If the node does not exist, create it
            if (ptr->children[index] == NULL)
            {
                ptr->children[index] = malloc(sizeof(node));
            
                // If it could not create a new node
                if (ptr->children[index] == NULL)
                {
                    printf("Could not allocate memory for a new node\n");
                    
                    // Free the space that has been malloced
                    free(root);
                    free(ptr->children[index]);
                    
                    return false;
                }              
            }
           
            // Make the ith point to the next node
            ptr = ptr->children[index];
        }
        
        // If encounters a new line
        else
        {
            // Indicates that the word is over
            ptr->is_word = true;
            
            // Sets the pointer to the root for a new word
            ptr = root;
            
            // Increases the word count by one
            word_count++;
        }
        
    }
    
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{

    return word_count;
}

/**
 * Creates a recursive function to unload
 */
 
void freeNode(node* ptr)
{
    for (int i = 0; i < 27; i++)
    {
        if (ptr->children[i] != NULL)
        {
            freeNode(ptr->children[i]);
        }
    }
    
    free(ptr);
} 

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // Uses the function freeNode from the root
    freeNode(root);
    return true;
}
