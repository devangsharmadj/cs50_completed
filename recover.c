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
    FILE* image = fopen("tempfile.txt", "w");
    int size = 1;
    int temp = 0;
    for (int i = 0; i < 1024; i ++)
    {
        BYTE buffer[512];
        size = fread(buffer, sizeof(buffer), 1, inputFilePtr);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            temp = 1;
            number = number + 1;
            fclose(image);
            sprintf(fileName, "%03i.jpg", number);
            image = fopen(fileName, "w");
            fwrite(buffer, sizeof(BYTE), 512, image);
        }
        else if (temp == 1)
        {
            fwrite(buffer, sizeof(BYTE), 512, image);
        }
    }

     //if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
   //             {
    // Check if file is a Jpeg


}


