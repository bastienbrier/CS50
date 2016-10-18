#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{   
    string name = GetString();
    
    printf("%c", toupper(name[0]));
    // Print the first initial of the name
    
    for(int i = 0, n = strlen(name); i < n; i++)
    {
        if (name[i] == ' ')
        {
            printf("%c", toupper(name[i + 1]));
            // If the code identifies a space
            // Prints the following letter in caps
        }
    }
    
    printf("\n");
}
