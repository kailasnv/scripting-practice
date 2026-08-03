#include <stdio.h>
#include "font8x8_basic.h"

int getFontIndex(char c)
{
    if (c == ' ')
        return 0;

    if (c >= '0' && c <= '9')
        return (c - '0') + 1;

    if (c >= 'A' && c <= 'Z')
        return (c - 'A') + 11;

    if (c >= 'a' && c <= 'z')
        return (c - 'a') + 37;

    return 0;
}
void showCharacter(int index)
{
    int row, col;

    for (row = 0; row < 8; row++)
    {
        for (col = 7; col >= 0; col--)
        {
            int bit = (fonts[index][row] >> col) & 1;

            if (bit == 1)
                printf("#");
            else
                printf(".");
        }
        printf("\n");
    }
}

int main()
{
    char text[] = "Kailas";

    int i;
    for (i = 0; text[i] != '\0'; i++)
    {
        int index = getFontIndex(text[i]);
        showCharacter(index);
    }

    return 0;
}