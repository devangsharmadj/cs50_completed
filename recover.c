#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover file\n");
        return 1;
    }
    FILE *inputFilePtr = fopen(argv[1], "r");
    if (inputFilePtr == NULL)
    {
        return 1;
    }

    int number=0;
    string fileName = "File";
    FILE* outputFile;
    int size = 0;
    do
    {
        int buffer[512];
        size = fread(buffer, sizeof(buffer), 1, inputFilePtr);
        for(int i = 0; i < 512; i ++)
        {
            if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
            {
                number = number + 1;
                do
                {
                    sprintf(fileName, "%03i.jpg", number);
                    FILE *fp = fopen(fileName, "w");
            
                }
                while (buffer[i] != 0xff && buffer[i + 1] != 0xd8 && buffer[i + 2] != 0xff && (buffer[i + 3] & 0xf0) != 0xe0);
            }
        }
    } 
    while (size == 512);
     //if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
   //             {
    // Check if file is a Jpeg


}


