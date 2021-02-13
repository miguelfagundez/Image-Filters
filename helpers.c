#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE grayValue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // If value is gray, I do not calculate it again
            if (!(image[i][j].rgbtRed == image[i][j].rgbtBlue && image[i][j].rgbtRed == image[i][j].rgbtGreen
                && image[i][j].rgbtBlue == image[i][j].rgbtGreen))
            {
                // New gray value - Average
                grayValue = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
                image[i][j].rgbtRed = grayValue;
                image[i][j].rgbtGreen = grayValue;
                image[i][j].rgbtBlue = grayValue;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaGreen;
    int sepiaBlue;
    int sepiaRed;

    // Loops
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            // Validate that values are less than 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Sepia values for new image
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *initial = &image[0][0];
    RGBTRIPLE *last = &image[0][width - 1];
    RGBTRIPLE temp;

    // Running each row at a time
    for (int i = 0; i < height; i++)
    {
        // Taking the first element
        initial = &image[i][0];
        // Taking last element
        last = &image[i][width - 1];

        while (initial <= last)
        {
            // if initial es less than last then exchange values
            temp = *initial;
            *initial = *last;
            *last = temp;

            // Increase & Decrease positions
            initial++;
            last--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int blurGreen;
    int blurBlue;
    int blurRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // First Line (Top edge)
            if (i == 0)
            {
                // Left Top Corner
                if (j == 0)
                {
                    blurGreen = round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen) / 4.0);
                    blurBlue = round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue) / 4.0);
                    blurRed = round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed) / 4.0);
                }
                else
                {
                    // Right Top Corner
                    if (j == width - 1)
                    {
                        blurGreen = round((image[0][j].rgbtGreen + image[0][j - 1].rgbtGreen + image[1][j].rgbtGreen + image[1][j - 1].rgbtGreen) / 4.0);
                        blurBlue = round((image[0][j].rgbtBlue + image[0][j - 1].rgbtBlue + image[1][j].rgbtBlue + image[1][j - 1].rgbtBlue) / 4.0);
                        blurRed = round((image[0][j].rgbtRed + image[0][j - 1].rgbtRed + image[1][j].rgbtRed + image[1][j - 1].rgbtRed) / 4.0);
                    }
                    else
                    {
                        // General Case (Top edge)
                        blurGreen = round((image[0][j].rgbtGreen + image[0][j - 1].rgbtGreen + image[0][j + 1].rgbtGreen + image[1][j].rgbtGreen +
                                        image[1][j - 1].rgbtGreen + image[1][j + 1].rgbtGreen) / 6.0);
                        blurBlue = round((image[0][j].rgbtBlue + image[0][j - 1].rgbtBlue + image[0][j + 1].rgbtBlue + image[1][j].rgbtBlue +
                                        image[1][j - 1].rgbtBlue + image[1][j + 1].rgbtBlue) / 6.0);
                        blurRed = round((image[0][j].rgbtRed + image[0][j - 1].rgbtRed + image[0][j + 1].rgbtRed + image[1][j].rgbtRed +
                                        image[1][j - 1].rgbtRed + image[1][j + 1].rgbtRed) / 6.0);

                    }
                }
            }
            else
            {
                // Left Bottom Corner
                if (i == height - 1)
                {
                    if (j == 0)
                    {
                        blurGreen = round((image[i][0].rgbtGreen + image[i][1].rgbtGreen + image[i - 1][0].rgbtGreen + image[i - 1][1].rgbtGreen) / 4.0);
                        blurBlue = round((image[i][0].rgbtBlue + image[i][1].rgbtBlue + image[i - 1][0].rgbtBlue + image[i - 1][1].rgbtBlue) / 4.0);
                        blurRed = round((image[i][0].rgbtRed + image[i][1].rgbtRed + image[i - 1][0].rgbtRed + image[i - 1][1].rgbtRed) / 4.0);
                    }
                    else
                    {
                        // Right Bottom Corner
                        if (j == width - 1)
                        {
                            blurGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen) /
                                            4.0);
                            blurBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 4.0);
                            blurRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed) / 4.0);
                        }
                        else
                        {
                            // General Case (Bottom edge)
                            blurGreen = round((image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen +
                                            image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen) / 6.0);
                            blurBlue = round((image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue +
                                            image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue) / 6.0);
                            blurRed = round((image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j - 1].rgbtRed +
                                            image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed) / 6.0);
                        }
                    }
                }
                else
                {
                    // Left Edge case
                    if (j == 0)
                    {
                        blurGreen = round((image[i][0].rgbtGreen + image[i - 1][0].rgbtGreen + image[i + 1][0].rgbtGreen + image[i - 1][1].rgbtGreen +
                                        image[i][1].rgbtGreen + image[i + 1][1].rgbtGreen) / 6.0);
                        blurBlue = round((image[i][0].rgbtBlue + image[i - 1][0].rgbtBlue + image[i + 1][0].rgbtBlue + image[i - 1][1].rgbtBlue +
                                        image[i][1].rgbtBlue + image[i + 1][1].rgbtBlue) / 6.0);
                        blurRed = round((image[i][0].rgbtRed + image[i - 1][0].rgbtRed + image[i + 1][0].rgbtRed + image[i - 1][1].rgbtRed +
                                        image[i][1].rgbtRed + image[i + 1][1].rgbtRed) / 6.0);
                    }
                    else
                    {
                        // Right Edge case
                        if (j == width - 1)
                        {
                            blurGreen = round((image[i][width - 1].rgbtGreen + image[i - 1][width - 1].rgbtGreen + image[i + 1][width - 1].rgbtGreen + image[i - 1][width - 2].rgbtGreen +
                                            image[i][width - 2].rgbtGreen + image[i + 1][width - 2].rgbtGreen) / 6.0);
                            blurBlue = round((image[i][width - 1].rgbtBlue + image[i - 1][width - 1].rgbtBlue + image[i + 1][width - 1].rgbtBlue + image[i - 1][width - 2].rgbtBlue +
                                            image[i][width - 2].rgbtBlue + image[i + 1][width - 2].rgbtBlue) / 6.0);
                            blurRed = round((image[i][width - 1].rgbtRed + image[i - 1][width - 1].rgbtRed + image[i + 1][width - 1].rgbtRed + image[i - 1][width - 2].rgbtRed +
                                            image[i][width - 2].rgbtRed + image[i + 1][width - 2].rgbtRed) / 6.0);
                        }
                        else
                        {
                            // General Case
                            blurGreen = round((image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen +
                                            image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
                            blurBlue = round((image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue +
                                            image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
                            blurRed = round((image[i][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed +
                                            image[i - 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);

                        }
                    }
                }
            }

            // Blur values for new image
            image[i][j].rgbtRed = blurRed;
            image[i][j].rgbtGreen = blurGreen;
            image[i][j].rgbtBlue = blurBlue;
        }
    }
    return;
}
