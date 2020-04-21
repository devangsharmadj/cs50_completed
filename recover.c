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
    FILE* outputFile;
    int size = 1;
    do
    {
        BYTE buffer[512];
        size = fread(buffer, sizeof(buffer), 1, inputFilePtr);
        for(int i = 0; i < 512; i ++)
        {
            if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
            {
                number = number + 1;
                printf("_%i_\n", number);
                //do
                //{
                    sprintf(fileName, "%03i.jpg", number);
                    FILE *fp = fopen(fileName, "wb");
                    if (fp == NULL)
                    {
                        printf("Error. Could not open file\n");
                        exit (1);
                    }
                    BYTE buffer1[512];
                    //for (int j = i + 3; j < 512; j ++)
                    //{
                        fwrite(buffer,sizeof(buffer1), 1, fp);
                        //if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
                        //{
                            fclose(fp);
                            break;
                        //}
                    //}
               // }
                //while (buffer[i] != 0xff && buffer[i + 1] != 0xd8 && buffer[i + 2] != 0xff && (buffer[i + 3] & 0xf0) != 0xe0);
            }
        }
    }
    while (size == 1);
     //if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
   //             {
    // Check if file is a Jpeg


}


