#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        printf("Please give the height of the pyramid (positive integer no greater than 23): ");
        h = GetInt();
        if (h < 0 || h > 23)
        {
            printf("This number is not accepted. Retry: \n");
        }
    }
    while (h < 0 || h > 23);
    
    for (int i = 0; i < h; i++)
    {
        for (int s = h - 1 - i; s > 0; s--)
        {
            printf(" ");
        }
        for (int n = 0; n < i + 1; n++)
        {
            printf("#");
        }
        printf("  ");
        for (int m = 0; m < i + 1; m++)
        {
            printf("#");
        }
        printf("\n");
    }
}
