#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{   
    if (argc != 2)
    {    
        printf("Enter the key after ./vigenere\n");
        return 1;
        // Prevents the user if he does not type a key or too many arguments
    }    
    
    string key = argv[1];
    
    for(int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Enter a valid string please\n");
            return 1;
            // Prevents the user if his key is not a string
        }
    } 
    
    string message = GetString();
    
    int j = 0;
    // Counter of the characters of key    

    for (int i = 0, n = strlen(message); i < n; i++)
    {
        if (isalpha(message[i]))
        // Checks if the character is a letter
        // Then, 2 different codes for uppercase and lowercase letters
        {
            if (isupper(message[i]))
            {
                int newLetter = message[i] - 'A';
                int keyLetter = (toupper(key[j % strlen(key)])) - 'A';
                message[i] = (newLetter + keyLetter) % 26 + 'A';
                // The substraction of 'A' enables to reduce the scope to 0 - 25
                // Then adding the 'A' at the end gives the ASCII value
                // We use toupper() in order to be on the scope 65 - 90
                j++;
                // Increment the counter of the key
            }
            else if (islower(message[i]))
            {
                int newLetter = message[i] - 'a';
                int keyLetter = (tolower(key[j % strlen(key)])) - 'a';
                message[i] = (newLetter + keyLetter) % 26 + 'a';
                // Same functioning as for the uppercase letters
                // But with different ASCII values
                j++;
            }
        }
    }
    printf("%s", message);
    printf("\n");
    return 0;
    // Return 0 to signify success
}
