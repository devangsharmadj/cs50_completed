// @ author Devang Sharma
// @ Recovering images from a camera's memory card

#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    FILE *inputFilePtr = fopen(argv[1], "rb");
    if (inputFilePtr == NULL)
    {
        return 1;
    }
    int number = -1;
    char fileName[8];
    FILE *image = NULL;
    int size = 1;
    do
    {
        BYTE buffer[512];
        size = fread(buffer, sizeof(buffer), 1, inputFilePtr);
        if (size == 0)
        {
            // Checking for the last image
            break;
        }
        //printf("_%i_<%i>", number, size);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Opening new file
            number = number + 1;
            if (image != NULL)
            {
                // Checking and closing file
                fclose(image);
            }
            // Getting new file name
            sprintf(fileName, "%03i.jpg", number);
            image = fopen(fileName, "w");
        }
        if (image != NULL)
        {
            fwrite(buffer, sizeof(BYTE), sizeof(buffer), image);
        }
    }
    while (size == 1);
    if (image != NULL)
    {
        fclose(image);
    }
    return 0;
    //if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
    //             {
    // Check if file is a Jpeg


}


