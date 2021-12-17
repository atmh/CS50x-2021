#include "helpers.h"
#include <math.h>

// helper to cap val to 255
int lim(int val)
{
    if (val > 255)
    {
        val = 255;
    }
    return val;
}

// helper to calculate blur
int calBlur(int i, int j, int h, int w, RGBTRIPLE image[h][w], int color_position)
{
    int count = 0, sum = 0;
    for (int k = i - 1; k < (i + 2); k++)
    {
        for (int l = j - 1; l < (j + 2); l++)
        {
            // edge case
            if (k < 0 || l < 0 || k >= h || l >= w)
            {
                continue;
            }
            // 0
            if (color_position == 0)
            {
                sum = sum + image[k][l].rgbtRed;
            }
            // 1
            else if (color_position == 1)
            {
                sum = sum + image[k][l].rgbtGreen;
            }
            // otherwise
            else
            {
                sum = sum + image[k][l].rgbtBlue;
            }
            count++;
        }
    }
    // cast to float to ensure accurate rounding
    return round((float) sum / count);
}


// Convert image to grayscale
void grayscale(int h, int w, RGBTRIPLE image[h][w])
{
    float gray;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            gray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int h, int w, RGBTRIPLE image[h][w])
{
    int red, green, blue;
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            // temp variables
            red = lim(round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue));
            green = lim(round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue));
            blue = lim(round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue));

            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int h, int w, RGBTRIPLE image[h][w])
{
    // temp array
    int temp[3];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w / 2; j++)
        {
            // swap temp colors
            temp[0] = image[i][j].rgbtBlue;
            temp[1] = image[i][j].rgbtGreen;
            temp[2] = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][w - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][w - j - 1].rgbtGreen;
            image[i][j].rgbtRed = image[i][w - j - 1].rgbtRed;

            // update
            image[i][w - j - 1].rgbtBlue = temp[0];
            image[i][w - j - 1].rgbtGreen = temp[1];
            image[i][w - j - 1].rgbtRed = temp[2];
        }
    }
    return;
}

// Blur image
void blur(int h, int w, RGBTRIPLE image[h][w])
{
    // temp array
    RGBTRIPLE temp[h][w];
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            image[i][j].rgbtRed = calBlur(i, j, h, w, temp, 0);
            image[i][j].rgbtGreen = calBlur(i, j, h, w, temp, 1);
            image[i][j].rgbtBlue = calBlur(i, j, h, w, temp, 2);
        }
    }
    return;
}