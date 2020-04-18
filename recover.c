#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    FILE *inputFilePtr = fopen(argv[1], "r");
    if (inputFilePtr == NULL)
    {
        return 1;
    }

    int number = 0;
    string fileName = "File";
    
    
        int buffer[512];
        int size = fread(buffer, sizeof(buffer), 1, inputFilePtr);
        FILE *outputFile;
        if (size == 0)
        {
            for (int i = 0; i < 512; i ++)
            {   
                if (buffer[i] == 0xff && buffer[i + 1] == 0xd8 && buffer[i + 2] == 0xff && (buffer[i + 3] & 0xf0) == 0xe0)
                {
                    fclose(outputFile);
                    sprintf(fileName, "%03i.jpg", number);
                   
                    outputFile = fopen(fileName , "w");
                    fwrite(buffer,512 , 1, outputFile);
                }   
            }
        }
        else
        {
            return 1;
        }
        
    
    return 0;

}
    // Check if file is a Jpeg



