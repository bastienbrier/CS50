#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do
    {
        printf("Height of the pyramid (positive integer no greater than 23): ");
        height = GetInt();
        if (height < 0 || height > 23)
        {
            printf("This number is not accepted. Retry: \n");
            // Prints a message when the number not accepted..
        }
    }
    while (height < 0 || height > 23);
    
    for (int line = 0; line < height; line++)
    // This first loop prints the number of lines asked.
    {
        for (int space = height - 1 - line; space > 0; space--)
        {
            printf(" ");
            // This first loop prints the number of spaces in each line.
        }
        for (int hashes = 0; hashes < line + 2; hashes++)
        {
            printf("#");
            // This second loop prints the number of hashed after the spaces.
        }
        printf("\n");
    }
}
