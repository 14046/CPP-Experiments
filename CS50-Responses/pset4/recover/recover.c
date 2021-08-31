#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        FILE *card = fopen(argv[1], "r");
        if (card == NULL)
        {
            printf("The forensic image cannot be opened.\n");
            return 1;
        }
        
        BYTE bytes[512];
        char filename[8];
        int file = 0;
        FILE *img = NULL;
        
        bool isFirstJPEG = true;
        bool isWriting = false;
        
        while(fread(&bytes, sizeof(BYTE), 512, card) == 512)
        {
            if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
            {
                if (isFirstJPEG == true)
                {
                    isFirstJPEG = false;
                }
                else
                {
                    fclose(img);
                    isWriting = false;
                }
                sprintf(filename, "%03i.jpg", file);
                img = fopen(filename, "w");
                file++;
                fwrite(&bytes, sizeof(BYTE), 512, img);
                isWriting = true;
            }
            else
            {
                if (isWriting == true)
                {
                    fwrite(&bytes, sizeof(BYTE), 512, img);
                }
            }
        }
        fclose(card);
        fclose(img);
    }
}