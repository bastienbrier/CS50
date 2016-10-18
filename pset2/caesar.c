#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{   
    if (argc != 2)
    {    
        printf("Enter the key after ./caesar\n");
        return 1;
        // Prevents the user if he does not type a key or too many arguments
    }    
    
    int k = atoi(argv[1]);
    
    if (k <= 0)
    {
        printf("Type a positive integer please.\n");
        return 1;
        // Prevents the user if the key he typed is not an integer
    }
    
    string message = GetString();
    
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        if (isalpha(message[i]))
        // Checks if the character is a letter
        // Then, 2 different codes for uppercase and lowercase letters
        {
            if (isupper(message[i]))
            {
                message[i] = (message[i] - 'A' + k) % 26 + 'A';
                // The substraction of 'A' enables to reduce the scope to 0 - 25
                // Then adding the 'A' at the end gives the ASCII value 
            }
            else if (islower(message[i]))
            {
                message[i] = (message[i] - 'a' + k) % 26 + 'a';
                // Same functioning as for the uppercase letters
                // But with different ASCII values
            }
        }
    }
    printf("%s", message);
    printf("\n");
    return 0;
    // Return 0 to signify success
}
