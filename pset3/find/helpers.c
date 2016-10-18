/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Implement a searching algorithm
    if (n >= 0)
    {
        int lower = 0;
        int upper = n - 1;
        
        while(lower <= upper)
        {
            int middle = (lower + upper) / 2;
            
            if (values[middle] == value)
            {
                return true;
            }
            // Throws away the right side of the array
            else if (value > values[middle])
            {
                lower = middle + 1;
            }
            // Throws away the left side of the array
            else if (value < values[middle])
            {
                upper = middle - 1;
            }
        }
        return false;
    }
    else
    {
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // Implement an O(n^2) sorting algorithm: bubble sort 
    for (int i = 0; i < n - 1; i++)
    {
        int swap = 0;
        
        // Until n - 1 - i, because the end is already sorted
        for (int j = 0; j < n - 1 - i; j++)
        {
            // If the jth value is greater than the (j+1)th, swap
            if (values[j] > values[j + 1])
            {
                int tmp = values[j + 1];
                values[j + 1] = values[j];
                values[j] = tmp;
                swap++;
            }
        }
        
        // If there was no swap, the array is sorted
        if (!swap)
        {
            break;
        }
    } 
    
    return;
}
