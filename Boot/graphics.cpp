#include"graphics.hpp"

int rgb(int r, int g, int b)
{
    return r << 11 | g << 5 | b;
}
void Draw(int x, int y, int r, int g, int b)
{
    VBEInfoBlock* VBE = (VBEInfoBlock* )VBEInfoAddress;
    unsigned short* buffer = (unsigned short*) ScreenBufferAdress;
    int index = y * VBE->x_resolution + x;
    *(buffer + index) = rgb(r,g,b);
}
void ClearScreen(int r, int g, int b)
{
    VBEInfoBlock* VBE = (VBEInfoBlock* )VBEInfoAddress;
    for(int y = 0; y < VBE->y_resolution; y++)
    {
        for(int x = 0; x < VBE->x_resolution; x++)
        {
            Draw(x, y, r, g, b);
        }   
    }
}
void DrawRect(int x, int y, int width, int height, int r, int g, int b)
{
    for (int j = y; j < (y + height); j++ ) 
    {
        for (int i = x; i < (x + width); i++) 
        { 
            Draw(i, j, r, g, b);
        }
    }
}
void DrawCharacter(int (*f)(int, int), int font_width, int font_height, char c, int x, int y, int r, int g, int b)
{
    for(int j = 0; j <  font_height; j++)
    {
        unsigned int row = (*f)((int)(c), j);
        int shift = font_width - 1;
        int bit_val = 0;
        for (int i = 0; i < font_width; i++)
        {
            bit_val = (row >> shift) & 0b00000000000000000000000000000001;
            if (bit_val == 1)
                Draw(x+i, y+j, r, g, b);
            shift -=1;
        }
    }
}
void DrawString(int (*f)(int, int), int font_width, int font_height, char* s, int x, int y, int r, int g, int b)
{
    int i = 0, j = 0;
    for (int k = 0; *(s + k) !=0; k++)
    {
        if (*(s + k) != '\n')
            DrawCharacter(f, font_width, font_height, *(s + k), x + i, y + j, r, g, b);
        i += font_width - (font_width / 4);
        if (*(s + k) == '\n')
        {
            i = 0;
            j += font_height;
        }
    }
}
void DrawMouse(int x, int y, int r, int g, int b)
{
    int mouse[] = {
        0b1111111111,
        0b1111111110,
        0b1111111100,
        0b1111111000,
        0b1111110000,
        0b1111100000,
        0b1111000000,
        0b1110000000,
        0b1100000000,
        0b1000000000,
    };
    int mouse_width = 10, mouse_height = 10;
    for(int j = 0; j <  mouse_height; j++)
    {
        unsigned int row = mouse[j];
        int shift = mouse_width - 1;
        int bit_val = 0;
        for (int i = 0; i < mouse_width; i++)
        {
            bit_val = (row >> shift) & 0b00000000000000000000000000000001;
            if (bit_val == 1)
                Draw(x+i, y+j, r, g, b);
            shift -=1;
        }
    }
}
void DrawCircle(int x, int y, int radius, int r, int g, int b)
{
    int rr = radius * radius;
    for (int j = -radius; j < radius; j ++)
    {
        for (int i = -radius; i < radius; i ++)
        {
            if((i*i + j*j) <= rr)
                Draw(x+ i, y + j, r, g, b);
        }
    }
}
void Flush()
{
    VBEInfoBlock* VBE = (VBEInfoBlock*) VBEInfoAddress;
    unsigned short* buffer = (unsigned short*) ScreenBufferAdress;
    int index;
    for (int y = 0; y < VBE->y_resolution; y++)
    {
        for (int x = 0; x < VBE->x_resolution; x++)
        {
            index = y * VBE->x_resolution + x;
            *((unsigned short*)VBE->screen_ptr + index) = *(buffer + index);
        }
    }
}