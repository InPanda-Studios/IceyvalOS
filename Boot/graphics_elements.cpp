int DrawCircleButton(int x, int y, int radius, int r, int g, int b, int taskid)
{
      if(mouse_possessed_taskid == taskid && (((mx - x)*(mx - x) + (my -y)*(my-y)) <= radius*radius))
      {
            DrawCircle(x, y, radius, r, g, b);

            if(left_clicked == true)
            {
                  left_clicked = false;
                  return 1;
            }
      }
      else
      {
            DrawCircle(x, y, radius, r/4, g/4, b/4);
      }
      return 0;

}

int DrawButton(int x, int y, int width, int height, int r, int g, int b, char* text, int r1, int g1, int b1, int taskid)
{
      if(mouse_possessed_taskid == taskid && mx > x && mx < x + width && my > y && my < y + height)
      {
            /*
            \ Ignore this
            */
            DrawRect(x, y, width, height, r, g, b);
            if(left_clicked == true)
            {
                  left_clicked = false;
                  return 1;
            }      
      }
      else
            DrawRect(x, y, width, height, r/4, g/4, b/4);
      DrawString(getArialCharacter, font_arial_width, font_arial_height, text, x + width / 10, y + height / 10, r1, g1, b1);
      return 0;
}


int DrawWindow(int* x, int* y, int* width, int* height, int r, int g, int b, int* mouse_held, int taskid)
{
      if(left_clicked == false)
      {
            *mouse_held = false;
      }
      if(mouse_possessed_taskid == taskid && (*mouse_held == true 
            || (left_clicked == true && mx > *x && 
            mx < *x + *width - 30 && 
            my > *y &&
            my < *y + 20)))
      {
            left_clicked == false;
            *mouse_held = true;
            *x = mx - (*width / 2);
            *y = my - 10;

      }
      DrawRect(*x, *y, *width, 20, 16, 32, 16);
      DrawRect(*x, *y + 20, *width, *height, r, g, b);

      return DrawCircleButton(*x + *width - 10, *y + 10, 8, 16, 0, 0,taskid);
}