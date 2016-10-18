#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float change;
    int i = 0;
    // i is the total number of coins needed.
    
    do
    {
        printf ("How much change is owed?\n$");
        change = GetFloat();
        // Prompts the user for the change.
        if (change < 0)
        {
            printf ("Please give a positive number.\n");
            // Prompts if the number is negative.
        }
    }
    while (change < 0);
    
    change = round(change * 100);
    // Multiply the change by 100 and rounds it.
    
    while (change >= 25)
    {
        change -= 25;
        // Substract 25 (quarter) when it is possible.
        i += 1;
        // Adds one to the total number of coins.
    }
    
    while (change >= 10)
    {
        change -= 10;
        i += 1;
        // Does the same thing for the dime (10).
        // Executes after the verification for the quarter.
    }
    
    while (change >= 5)
    {
        change -= 5;
        i += 1;
        // Does the same thing for the nickel.
    }
    while (change >= 1)
    {
        change -= 1;
        i += 1;
        // Does the same thing for the penny.
    }
    printf("%i\n", i);
    // Prints the total number of coins used.
}
