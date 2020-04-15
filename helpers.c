// @ author Devang Sharma
// @ Instagram filters
#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            float r = (float)image[i][j].rgbtRed;
            float g = (float)image[i][j].rgbtGreen;
            float b = (float)image[i][j].rgbtBlue;
            // Getting the average of all the colors
            int average = round((r + g + b) / 3);
            // Assigning the value to the pixel
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            // Using the Sepia formulas to get new colors
            float r = (float).393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float g = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float b = (float).272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            // Assigning new colors to original image
            r = round(r);
            g = round(g);
            b = round(b);
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }
            if (r < 0)
            {
                r = 0;
            }
            if (g < 0)
            {
                g = 0;
            }
            if (b < 0)
            {
                b = 0;
            }
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width / 2; j ++)
        {
            int r = image[i][j].rgbtRed ;
            int g = image[i][j].rgbtGreen ;
            int b = image[i][j].rgbtBlue ;

            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            image[i][width - 1 - j].rgbtRed = r;
            image[i][width - 1 - j].rgbtGreen = g;
            image[i][width - 1 - j].rgbtBlue = b;


        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    float r = 0.0;
    float b = 0.0;
    float g = 0.0;

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            //Conditions for corners
            if (i == 0 && j == 0)
            {
                // Top left corner
                r = ((float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j].rgbtRed +
                             image[i + 1][j + 1].rgbtRed)) / 4;
                b = ((float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                             image[i + 1][j + 1].rgbtBlue)) / 4;
                g = ((float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                             image[i + 1][j + 1].rgbtGreen)) / 4;
            }
            else if (i == 0 && j == width - 1)
            {
                // Top right corner
                r = ((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j].rgbtRed +
                             image[i + 1][j - 1].rgbtRed)) / 4;
                b = ((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue +
                             image[i + 1][j - 1].rgbtBlue)) / 4;
                g = ((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen +
                             image[i + 1][j - 1].rgbtGreen)) / 4;
            }
            else if (i == height - 1 && j == 0)
            {
                // Bottom left corner
                r = ((float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed +
                             image[i - 1][j + 1].rgbtRed)) / 4;
                b = ((float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                             image[i - 1][j + 1].rgbtBlue)) / 4;
                g = ((float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                             image[i - 1][j + 1].rgbtGreen)) / 4;
            }
            else if (i == height - 1 && j == width - 1)
            {
                // Bottom right corner
                r = (float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                            image[i][j - 1].rgbtRed) / 4;
                b = (float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                            image[i][j - 1].rgbtBlue) / 4;
                g = (float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                            image[i][j - 1].rgbtGreen) / 4;
            }

            // Above are all the conditions for the corners
            // Below are all the conditions for the edges
            else if (i == 0)
            {
                // Top edge
                r = ((float)(image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i][j + 1].rgbtRed +
                             image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed)) / 6;
                b = ((float)(image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i][j + 1].rgbtBlue +
                             image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue)) / 6;
                g = ((float)(image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i][j + 1].rgbtGreen +
                             image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen)) / 6;
            }
            else if (j == width - 1)
            {
                // Right edge
                r = (float)(image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed +
                            image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6;
                b = (float)(image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                            image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6;
                g = (float)(image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                            image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6;
            }
            else if (i == height - 1)
            {
                // Bottom edge
                r = (float)(image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed +
                            image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6;
                b = (float)(image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue +
                            image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6;
                g = (float)(image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen +
                            image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6;
            }
            else if (j == 0)
            {
                // Left edge
                r = (float)(image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed +
                            image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6;
                b = (float)(image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue +
                            image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6;
                g = (float)(image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen +
                            image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6;

            }
            else
            {
                r = ((float)(image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i - 1][j].rgbtRed +
                             image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed +
                             image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed)) / 9;

                b = ((float)(image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i - 1][j].rgbtBlue +
                             image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                             image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue)) / 9;

                g = ((float)(image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i - 1][j].rgbtGreen +
                             image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                             image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen)) / 9;

            }


            // Transfering data to the temp variable
            temp[i][j].rgbtRed = round(r);
            temp[i][j].rgbtBlue = round(b);
            temp[i][j].rgbtGreen = round(g);

        }
    }
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen =  temp[i][j].rgbtGreen;
            // printf("(%i,%i,%i)", temp[i][j].rgbtRed,temp[i][j].rgbtGreen,temp[i][j].rgbtBlue);
        }
    }
    return;
}
