/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4 
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    
    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if (n < 1 || n > 100)
    {
        printf("n must be an integer between 1 and 100\n");
        return 1;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // save the infile header info
    LONG old_biWidth = bi.biWidth;
    LONG old_biHeight = bi.biHeight;
    int old_padding =  (4 - (old_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // change the values
    bi.biWidth *= n;
    bi.biHeight *= n;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    
    // define the length of the scanline
    int scanlen = old_biWidth * sizeof(RGBTRIPLE);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
        
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(old_biHeight); i < biHeight; i++)
    {
        int heightcheck = 0;
        
        // iterate n times for each scanline
        while (heightcheck < n)
        {      
            
            // iterate over pixels in scanline
            for (int j = 0, biWidth = old_biWidth; j < biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // interate n times for each pixel
                for (int widthcheck = 0; widthcheck < n; widthcheck++)
                {             
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // add the padding
            for (int k = 0; k < padding; k++)
            {
                fputc(0x00, outptr);
            } 
            
            // goes at the beginning of the line
            if (heightcheck != n - 1)
            {
                fseek(inptr, -scanlen, SEEK_CUR); 
            } 
            heightcheck++; 
        }
        // skip over padding, if any
        fseek(inptr, old_padding, SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
