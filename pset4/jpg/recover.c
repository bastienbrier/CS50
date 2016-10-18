/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK 512

int main(int argc, char* argv[])
{
    // open memory card
    FILE* cardptr = fopen("card.raw", "r");
    if (cardptr == NULL)
    {
        printf("Could not open the memory card\n");
        return 2;
    }
    
    // declare the variables
    uint8_t buffer[BLOCK] = {0};
    char title[8]; 
    int jpg_number = 0;
    
    // prototype function jpg_found
    bool jpg_found(uint8_t buffer[]);
    
    // reads the memory card
    while(fread(buffer, sizeof(buffer), 1, cardptr) != 0)
    {
        
        if (jpg_found(buffer))
        {
            // name the jpg file
            sprintf(title, "%03d.jpg", jpg_number);
            jpg_number++;
            FILE* img = fopen(title, "a");
            if (img == NULL)
            {
                printf("Coult not create the file\n");
                return 3;
            }
            
            while(true)
            {
                fwrite(buffer, BLOCK, 1, img);
                
                if (fread(buffer, BLOCK, 1, cardptr) == 0)
                {
                    fclose(img);
                    break;
                }
                else
                {
                    if (jpg_found(buffer))
                    {
                        fseek(cardptr, -BLOCK, SEEK_CUR);
                        fclose(img);
                        break;
                    }
                }
            }
        }
    }
    
    // close memory card
    fclose(cardptr);
    
    // the end!
    return 0;
}

bool jpg_found(uint8_t buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
    {
        return true;
    }
    else
    {
        return false;
    }
}
