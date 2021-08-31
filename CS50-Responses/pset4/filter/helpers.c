#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = round(((((double) image[i][j].rgbtBlue + (double) image[i][j].rgbtGreen + (double) image[i][j].rgbtRed) / 3)));

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE TEMP;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            TEMP.rgbtBlue = image[i][j].rgbtBlue;
            TEMP.rgbtGreen = image[i][j].rgbtGreen;
            TEMP.rgbtRed = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - j].rgbtRed;

            image[i][width - j].rgbtBlue = TEMP.rgbtBlue;
            image[i][width - j].rgbtGreen = TEMP.rgbtGreen;
            image[i][width - j].rgbtRed = TEMP.rgbtRed;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurredImage[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            float sumBlue = 0, sumGreen = 0, sumRed = 0, pixels = 0;

            for (int i = row - 1; i < row + 1; i++)
            {
                if (i < 0 || i > height)
                {
                    break;
                }
                else
                {
                    for (int j = column - 1; j < column; j++)
                    {
                        if (j < 0 || j > column)
                        {
                            break;
                        }
                        else
                        {
                            pixels++;
                            sumBlue += image[i][j].rgbtBlue;
                            sumGreen += image[i][j].rgbtGreen;
                            sumRed += image[i][j].rgbtRed;
                        }
                    }
                }
            }
            blurredImage[row][column].rgbtBlue = round(sumBlue / pixels);
            blurredImage[row][column].rgbtGreen = round(sumGreen / pixels);
            blurredImage[row][column].rgbtRed = round(sumRed / pixels);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = blurredImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blurredImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = blurredImage[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        double Blue;
        double Green;
        double Red;
    }
    sum;
    RGBTRIPLE edgifiedImage[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            sum sumX, sumY;
            
            sumX.Blue = 0;
            sumX.Green = 0;
            sumX.Red = 0;

            sumY.Blue = 0;
            sumY.Green = 0;
            sumY.Red = 0;
            
            for (int i = row - 1; i <= row + 1; i++)
            {
                if (i < 0 || i > height)
                {
                    break;
                }
                else
                {
                    for (int j = column - 1; j <= column + 1; j++)
                    {
                        if (j < 0 || j > width)
                        {
                            break;
                        }
                        else
                        {
                            if (i == row - 1)
                            {
                                if (j == column - 1)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * -1);
                                    sumX.Green += (image[i][j].rgbtGreen * -1);
                                    sumX.Red += (image[i][j].rgbtRed * -1);

                                    sumY.Blue += (image[i][j].rgbtBlue * -1);
                                    sumY.Green += (image[i][j].rgbtGreen * -1);
                                    sumY.Red += (image[i][j].rgbtRed * -1);
                                }
                                else if (j == column)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * 0);
                                    sumX.Green += (image[i][j].rgbtGreen * 0);
                                    sumX.Red += (image[i][j].rgbtRed * 0);

                                    sumY.Blue += (image[i][j].rgbtBlue * -2);
                                    sumY.Green += (image[i][j].rgbtGreen * -2);
                                    sumY.Red += (image[i][j].rgbtRed * -2);
                                }
                                else if (j == column + 1)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * 1);
                                    sumX.Green += (image[i][j].rgbtGreen * 1);
                                    sumX.Red += (image[i][j].rgbtRed * 1);

                                    sumY.Blue += (image[i][j].rgbtBlue * -1);
                                    sumY.Green += (image[i][j].rgbtGreen * -1);
                                    sumY.Red += (image[i][j].rgbtRed * -1);
                                }
                                else
                                {
                                    continue;
                                }
                            }
                            else if (i == row)
                            {
                                if (j == column - 1)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * -2);
                                    sumX.Green += (image[i][j].rgbtGreen * -2);
                                    sumX.Red += (image[i][j].rgbtRed * -2);

                                    sumY.Blue += (image[i][j].rgbtBlue * 0);
                                    sumY.Green += (image[i][j].rgbtGreen * 0);
                                    sumY.Red += (image[i][j].rgbtRed * 0);
                                }
                                else if (j == column)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * 0);
                                    sumX.Green += (image[i][j].rgbtGreen * 0);
                                    sumX.Red += (image[i][j].rgbtRed * 0);

                                    sumY.Blue += (image[i][j].rgbtBlue * 0);
                                    sumY.Green += (image[i][j].rgbtGreen * 0);
                                    sumY.Red += (image[i][j].rgbtRed * 0);
                                }
                                else if (j == column + 1)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * 2);
                                    sumX.Green += (image[i][j].rgbtGreen * 2);
                                    sumX.Red += (image[i][j].rgbtRed * 2);

                                    sumY.Blue += (image[i][j].rgbtBlue * 0);
                                    sumY.Green += (image[i][j].rgbtGreen * 0);
                                    sumY.Red += (image[i][j].rgbtRed * 0);
                                }
                                else
                                {
                                    continue;
                                }
                            }
                            else if (i == row + 1)
                            {
                                if (j == column - 1)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * -1);
                                    sumX.Green += (image[i][j].rgbtGreen * -1);
                                    sumX.Red += (image[i][j].rgbtRed * -1);

                                    sumY.Blue += (image[i][j].rgbtBlue * 1);
                                    sumY.Green += (image[i][j].rgbtGreen * 1);
                                    sumY.Red += (image[i][j].rgbtRed * 1);
                                }
                                else if (j == column)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * 0);
                                    sumX.Green += (image[i][j].rgbtGreen * 0);
                                    sumX.Red += (image[i][j].rgbtRed * 0);

                                    sumY.Blue += (image[i][j].rgbtBlue * 2);
                                    sumY.Green += (image[i][j].rgbtGreen * 2);
                                    sumY.Red += (image[i][j].rgbtRed * 2);
                                }
                                else if (j == column + 1)
                                {
                                    sumX.Blue += (image[i][j].rgbtBlue * 1);
                                    sumX.Green += (image[i][j].rgbtGreen * 1);
                                    sumX.Red += (image[i][j].rgbtRed * 1);

                                    sumY.Blue += (image[i][j].rgbtBlue * 1);
                                    sumY.Green += (image[i][j].rgbtGreen * 1);
                                    sumY.Red += (image[i][j].rgbtRed * 1);
                                }
                                else
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                }
            }
            sum root;
            
            root.Blue = round(sqrt((pow(sumX.Blue, 2) + pow(sumY.Blue, 2))));
            root.Green = round(sqrt((pow(sumX.Green, 2) + pow(sumY.Green, 2))));
            root.Red = round(sqrt((pow(sumX.Red, 2) + pow(sumY.Red, 2))));
            
            if (root.Blue > 255)
            {
                root.Blue = 255;
            }
            if (root.Green > 255)
            {
                root.Green = 255;
            }
            if (root.Red > 255)
            {
                root.Red = 255;
            }
            
            edgifiedImage[row][column].rgbtBlue = root.Blue;
            edgifiedImage[row][column].rgbtGreen = root.Green;
            edgifiedImage[row][column].rgbtRed = root.Red;
        }
    }
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = edgifiedImage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = edgifiedImage[i][j].rgbtGreen;
            image[i][j].rgbtRed = edgifiedImage[i][j].rgbtRed;
        }
    }
    return;
}