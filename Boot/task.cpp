
int TasksLength = 0;
#define task_params_length 10

int iparams[100] = {10};

void ProcessTasks()
{
      int priority;
      int i;

      priority = 5;
      while (priority >= 0)
      {
            i = mouse_possessed_taskid;
            if(left_clicked == true && mx > iparams[i * task_params_length + 0] &&mx < iparams[i * task_params_length + 0] + iparams[i * task_params_length + 2] &&my > iparams[i * task_params_length + 1] && my < iparams[i * task_params_length + 1] + iparams[i * task_params_length + 3])
            {
                  break;
            }
            for (i = 0;i < TasksLength; i++)
            {
                  if(left_clicked == true && mx > iparams[i * task_params_length + 0] &&mx < iparams[i * task_params_length + 0] + iparams[i * task_params_length + 2] &&my > iparams[i * task_params_length + 1] && my < iparams[i * task_params_length + 1] + iparams[i * task_params_length + 3])
                  {
                        tasks[mouse_possessed_taskid].priority = 0;
                        mouse_possessed_taskid = i;
                        tasks[i].priority = 2;
                        left_clicked = false;
                  }   
            }
            priority --;
      }
      
      priority = 0;
      while(priority <= 5)
      {
            for (int i = 0; i < TasksLength; i++)
            {
                  if(tasks[i].priority == priority)
                  {
                        tasks[i].function(tasks[i].taskid);
                  }
            }
            priority++;
      }
}
int NullTask(int taskid)
{
      return 0;
}
void CloseTask(int taskid)
{
      tasks[taskid].function = &NullTask;
      iparams[taskid * task_params_length + 0] = 0;
      iparams[taskid * task_params_length + 1] = 0;
      iparams[taskid * task_params_length + 2] = 0;
      iparams[taskid * task_params_length + 3] = 0;
}
int ClearScreenTask(int taskid)
{
      ClearScreen((0.0f / 255.0f * 16.0f), (204.0f / 255.0f * 32.0f), (102.0f / 255.0f * 16.0f));
      return 0;
}
int DrawMouseTask(int taskid)
{
      DrawMouse(mx, my, 0, 0, 0);
      return 0;
}
int ShellTask(int taskid)
{
      int* r = &iparams[taskid * task_params_length + 4];
      int* g = &iparams[taskid * task_params_length + 5];
      int* b = &iparams[taskid * task_params_length + 6];
      int* tr = &iparams[taskid * task_params_length + 7];
      int* tg = &iparams[taskid * task_params_length + 8];
      int* tb = &iparams[taskid * task_params_length + 10];
      int close_clicked = DrawWindow(
            &iparams[taskid * task_params_length + 0],
            &iparams[taskid * task_params_length + 1],
            &iparams[taskid * task_params_length + 2],
            &iparams[taskid * task_params_length + 3],
            *r,
            *g,
            *b,
            &iparams[taskid * task_params_length + 9],
            taskid
      );
      int x = iparams[taskid * task_params_length + 0];
      int y = iparams[taskid * task_params_length + 1];
      int width = iparams[taskid * task_params_length + 2];
      int height = iparams[taskid * task_params_length + 3];
      
      if(close_clicked == true)
      {
            CloseTask(taskid);
      }
      char texte[] = "Dark\0";
      char text2[] = "Light\0";
      if(DrawButton(x + 20, y + 20, 50, 20, 0 ,32, 0, texte,16, 32, 16, taskid) == true)
      {
            *r = (50.0f / 255.0f * 16.0f);
            *g = (50.0f / 255.0f * 32.0f);
            *b = (50.0f / 255.0f * 16.0f);
            *tr = 16;
            *tg = 32;
            *tb = 16;
      }
      if(DrawButton(x + 200, y + 20, 50, 20, 0 ,32, 0, text2,16, 32, 16, taskid) == true)
      {
            *r = (150.0f / 255.0f * 16.0f);
            *g = (150.0f / 255.0f * 32.0f);
            *b = (150.0f / 255.0f * 16.0f);
            *tr = 0;
            *tg = 0;
            *tb = 0;
      }
      char* charbuffer = tasks[taskid].ca1;
      char* text = tasks[taskid].text;
      int* charbufflen = &tasks[taskid].i1;
      if(mouse_possessed_taskid == taskid)
      {
            char character = ProcessScancode(Scancode);
            if(backspace_pressed == true)
            {
                  if((*charbufflen) != 0)
                  {
                        charbuffer[*charbufflen-1] = '\0';
                        (*charbufflen)--;
                  }
                  backspace_pressed = false;
                  Scancode = -1;
            }
            else if (character != '\0')
            {
                  if(character == '\n')
                  {
                        struct Command commands[17];
                        commands[0].string[0] = 'e'; commands[0].string[1] = 'c'; commands[0].string[2] = 'h';commands[0].string[3] = 'o'; commands[0].string[4] = '\0';
                        commands[0].function = &echo;
                        commands[2].string[0] = 'c'; commands[2].string[1] = 'a'; commands[2].string[2] = 'l';commands[2].string[3] = 'c';commands[2].string[4] = '\0';
                        commands[2].function = &calc;
                        commands[4].string[0] = 'o'; commands[4].string[1] = 's'; commands[4].string[2] = 'i';commands[4].string[3] = 'n';commands[4].string[4] = 'f';commands[4].string[5] = 'o';commands[4].string[6] = '\0';
                        commands[4].function = &osinfo;
                        commands[6].string[0] = 'c'; commands[6].string[1] = 'l'; commands[6].string[2] = 'r';commands[6].string[3] = '\0';
                        commands[6].function = &clr;
                        commands[8].string[0] = 's'; commands[8].string[1] = 'h'; commands[8].string[2] = 'u';commands[8].string[3] = 't';commands[8].string[4] = 'd';commands[8].string[5] = 'o';commands[8].string[6] = 'w';commands[8].string[7] = 'n';commands[8].string[8] = '\0';
                        commands[8].function = &shutdown;
                        commands[10].string[0] = 'r'; commands[10].string[1] = 'e'; commands[10].string[2] = 'b';commands[10].string[3] = 'o';commands[10].string[4] = 'o';commands[10].string[5] = 't';commands[10].string[6] = '\0';
                        commands[10].function = &reboot;
                        commands[12].string[0] = 'g'; commands[12].string[1] = 'e'; commands[12].string[2] = 't';commands[12].string[3] = 't';commands[12].string[4] = 'i';commands[12].string[5] = 'm';commands[12].string[6] = 'e';commands[12].string[7] = '\0';
                        commands[12].function = &gettime;
                        commands[14].string[0] = 's'; commands[14].string[1] = 'o'; commands[14].string[2] = 'u';commands[14].string[3] = 'n';commands[14].string[4] = 'd';commands[14].string[5] = '\0';
                        commands[14].function = &testsound;
                        commands[16].string[0] = 'r'; commands[16].string[1] = 'c'; commands[16].string[2] = 'l';commands[16].string[3] = 'a';commands[16].string[4] = 's';commands[16].string[5] = 's';commands[16].string[6] = '\0';
                        commands[16].function = &rcl;
                        for (int i = 0; i < 17;i +=2)
                        {
                              char *ans;
                              char ota[100];
                              char *out = ota;
                              char args[5][100];
                              if(contains(charbuffer, ' ') != NULL)
                              {
                                    split_string(charbuffer, ' ', args);
                                    for (int j = 0; j < 100; j++)
                                    {
                                          out[j] = args[0][j];
                                    }
                                    ans = commands[i].string;
                              }
                              else
                              {
                                    for (int j = 0; j < 100; j++)
                                    {
                                          out[j] = charbuffer[j];
                                    }
                                    ans = commands[i].string;
                              }
                              int yes = compare(ans, out);
                              if(yes == true)
                              {
                                    commands[i].function(taskid, args);
                              }
                        }
                        (*charbufflen) = 0;
                        charbuffer[*charbufflen] = '\0';
                        Scancode = -1;
                  }
                  else
                  {
                        charbuffer[*charbufflen] = character;
                        charbuffer[*charbufflen + 1] = '\0';
                        (*charbufflen)++;
                        Scancode = -1;
                  }
            }
            
      }
      char prtext[256];
      int j = 0;
      int k = 0;
      for (int i = 0; i < 256; i++)
      {
            if (k > 0 && k % 32 == 0)
            {
                  prtext[i] = '\n';
                  k = 0;
            }
            else
            {
                  prtext[i] = charbuffer[j * sizeof(char)];
                  j++;
            }
            k++;
            if(prtext[i] == '\n')
                  k=0;
      }
      DrawString(getArialCharacter, font_arial_width, font_arial_height, text, x+10, y+150, *tr, *tg, *tb);
      DrawString(getArialCharacter, font_arial_width, font_arial_height, prtext, x+10, y+100, *tr, *tg, *tb);
      return 0;
}
int BallTask(int taskid)
{
      int close_clicked = DrawWindow(
            &iparams[taskid * task_params_length + 0],
            &iparams[taskid * task_params_length + 1],
            &iparams[taskid * task_params_length + 2],
            &iparams[taskid * task_params_length + 3],
            (50.0f / 255.0f * 16.0f),
            (50.0f / 255.0f * 32.0f),
            (50.0f / 255.0f * 16.0f),
            &iparams[taskid * task_params_length + 9],
            taskid
      );
      if(close_clicked == true)
      {
            CloseTask(taskid);
      }
      int x = iparams[taskid * task_params_length + 0];
      int y = iparams[taskid * task_params_length + 1];
      int width = iparams[taskid * task_params_length + 2];
      int height = iparams[taskid * task_params_length + 3];

      iparams[taskid * task_params_length + 5] += iparams[taskid * task_params_length + 7];
      iparams[taskid * task_params_length + 6] += iparams[taskid * task_params_length + 8];
      if(iparams[taskid * task_params_length + 5] + 10 > iparams[taskid * task_params_length + 2] || iparams[taskid * task_params_length + 5] - 10 < 0)
      {
            iparams[taskid * task_params_length + 7] = -iparams[taskid * task_params_length + 7];
      }
      if(iparams[taskid * task_params_length + 6] + 10 > iparams[taskid * task_params_length + 3] || iparams[taskid * task_params_length + 6] - 10 < 20)
      {
            iparams[taskid * task_params_length + 8] = -iparams[taskid * task_params_length + 8];
      }
      DrawCircle(x + iparams[taskid * task_params_length + 5],y + iparams[taskid * task_params_length + 6], 10, 16, 32, 16);
      return 0;
}
int CalcTask(int taskid)
{
      int close_clicked = DrawWindow(
            &iparams[taskid * task_params_length + 0],
            &iparams[taskid * task_params_length + 1],
            &iparams[taskid * task_params_length + 2],
            &iparams[taskid * task_params_length + 3],
            (50.0f / 255.0f * 16.0f),
            (50.0f / 255.0f * 32.0f),
            (50.0f / 255.0f * 16.0f),
            &iparams[taskid * task_params_length + 9],
            taskid
      );
      if(close_clicked == true)
      {
            CloseTask(taskid);
      }
      int x = iparams[taskid * task_params_length + 0];
      int y = iparams[taskid * task_params_length + 1];
      int width = iparams[taskid * task_params_length + 2];
      int height = iparams[taskid * task_params_length + 3];
      char *equater = tasks[taskid].equater;
      char deltext[] = "Del\0";
      char entertext[] = "Enter\0";
      char addtext[] = "+\0";
      char mintext[] = "-\0";
      char divtext[] = "/\0";
      char multext[] = "*\0";
      char ctext[] = "C\0";
      char n0text[] = "0\0";
      char n1text[] = "1\0";
      char n2text[] = "2\0";
      char n3text[] = "3\0";
      char n4text[] = "4\0";
      char n5text[] = "5\0";
      char n6text[] = "6\0";
      char n7text[] = "7\0";
      char n8text[] = "8\0";
      char n9text[] = "9\0";
      char* text = tasks[taskid].text;
      int* charbufflen = &tasks[taskid].i1;
      if(DrawButton(x,y+75, 25, 20, 0, 10, 16, ctext, 16, 32, 16, taskid) == true)
      {
            text[0] = '\0';
            (*charbufflen)=0;
            equater[0] = '\0';
      }
      if(DrawButton(x+30,y+75, 25, 20, 0, 10, 16, deltext, 16, 32, 16, taskid) == true)
      {
            if((*charbufflen) != 0)
            {
                  text[*charbufflen-1] = '\0';
                  (*charbufflen)--;
            }
      }
      if(DrawButton(x,y+100, 25, 20, 0, 10, 16, n1text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '1';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x+30,y+100, 25, 20, 0, 10, 16, n2text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '2';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x+60,y+100, 25, 20, 0, 10, 16, n3text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '3';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x,y+125, 25, 20, 0, 10, 16, n4text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '4';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x+30,y+125, 25, 20, 0, 10, 16, n5text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '5';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x+60,y+125, 25, 20, 0, 10, 16, n6text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '6';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x,y+150, 25, 20, 0, 10, 16, n7text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '7';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x+30,y+150, 25, 20, 0, 10, 16, n8text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '8';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x+60,y+150, 25, 20, 0, 10, 16, n9text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '9';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x,y+175, 25, 20, 0, 10, 16, n0text, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '0';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
      }
      if(DrawButton(x+60,y+75, 25, 20, 0, 10, 16, addtext, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '+';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
            equater[0] = '+';
            equater[1] = '\0';
      }
      if(DrawButton(x+90,y+75, 25, 20, 0, 10, 16, mintext, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '-';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
            equater[0] = '-';
            equater[1] = '\0';
      }
      if(DrawButton(x+120,y+75, 25, 20, 0, 10, 16, multext, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '*';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
            equater[0] = '*';
            equater[1] = '\0';
      }
      if(DrawButton(x+90,y+100, 25, 20, 0, 10, 16, divtext, 16, 32, 16, taskid) == true)
      {
            text[*charbufflen] = '/';
            text[*charbufflen+1] = '\0';
            (*charbufflen)++;
            equater[0] = '/';
            equater[1] = '\0';
      }
      if(DrawButton(x+90,y+125, 50, 40, 0, 10, 16, entertext, 16, 32, 16, taskid) == true)
      {
            char answer[5][100];
            split_string(text, equater[0], answer);
            char num1[100];
            for (int j = 0; j < 100; j++)
            {
                  num1[j] = answer[0][j];
            }
            char num2[100];
            for (int j = 0; j < 100; j++)
            {
                  num2[j] = answer[1][j];
            }
            int n1 = atoi(num1);
            int n2 = atoi(num2);
            int ianswer = equate(n1, equater[0], n2);
            char *canswer = itoa(ianswer);
            for (int j = 0; j < 100; j++)
            {
                  text[j] = canswer[j];
            }
            (*charbufflen) = len(text);
            equater[0] = '\0';
            
      }
      char prtext[100];
      int j = 0;
      for (int i = 0; i < 100; i++)
      {
            if (i > 0 && i % 32 == 0)
            {
                  prtext[i] = '\n';
            }
            else
            {
                  prtext[i] = text[j * sizeof(char)];
                  j++;
            }
      }
      for(int i = 0; i < 100; i ++)
      {
            text[i] = prtext[i];
      }
      DrawString(getArialCharacter, font_arial_width, font_arial_height, text, x, y+50, 16, 32, 16);
      return 0;
}
int TextTask(int taskid)
{
      int close_clicked = DrawWindow(
            &iparams[taskid * task_params_length + 0],
            &iparams[taskid * task_params_length + 1],
            &iparams[taskid * task_params_length + 2],
            &iparams[taskid * task_params_length + 3],
            (50.0f / 255.0f * 16.0f),
            (50.0f / 255.0f * 32.0f),
            (50.0f / 255.0f * 16.0f),
            &iparams[taskid * task_params_length + 9],
            taskid
      );
      if(close_clicked == true)
      {
            CloseTask(taskid);
      }
      int x = iparams[taskid * task_params_length + 0];
      int y = iparams[taskid * task_params_length + 1];
      int width = iparams[taskid * task_params_length + 2];
      int height = iparams[taskid * task_params_length + 3];
      char* charbuffer = tasks[taskid].ca1;
      int* charbufflen = &tasks[taskid].i1;
      if(mouse_possessed_taskid == taskid)
      {
            char character = ProcessScancode(Scancode);
            if(backspace_pressed == true)
            {
                  if((*charbufflen) != 0)
                  {
                        charbuffer[*charbufflen-1] = '\0';
                        (*charbufflen)--;
                  }
                  backspace_pressed = false;
                  Scancode = -1;
            }
            else if (character != '\0')
            {
                  charbuffer[*charbufflen] = character;
                  charbuffer[*charbufflen + 1] = '\0';
                  (*charbufflen)++;
                  Scancode = -1;
            }
      }
      char prtext[256];
      int j = 0;
      int k = 0;
      for (int i = 0; i < 256; i++)
      {
            if (k > 0 && k % 32 == 0)
            {
                  prtext[i] = '\n';
                  k = 0;
            }
            else
            {
                  prtext[i] = charbuffer[j * sizeof(char)];
                  j++;
            }
            k++;
            if(prtext[i] == '\n')
                  k=0;
      }
      char savetext[] = "Save\0";
      char opentext[] = "Open\0";
      if(DrawButton(x+15,y+30, 50, 20, 0, 10, 16, savetext, 16, 32, 16, taskid) == true)
      {
            fwrite(&mainFile, charbuffer);
      }
      if(DrawButton(x+75,y+30, 50, 20, 0, 10, 16, opentext, 16, 32, 16, taskid) == true)
      {
            char *txt = fread(mainFile);
            (*charbufflen)=0;
            for(int i = 0; i < 256 && txt[i] != '\0'; i++)
            {
                  charbuffer[i] = txt[i];
                  (*charbufflen)++;
            }
      }
      DrawString(getArialCharacter, font_arial_width, font_arial_height, prtext, x+10, y+90, 16, 32, 16);
      return 0;
}
int TaskBarTask(int taskid)
{
      VBEInfoBlock* VBE = (VBEInfoBlock*) VBEInfoAddress;
      int y = VBE->y_resolution - 40;
      DrawRect(0,y,VBE->x_resolution, 40, 8, 16, 8);
      int i = iparams[taskid * task_params_length + 4];
      char shuttext[] = "Shut\0";
      char restart[] = "Reboot\0";
      DrawString(getArialCharacter, font_arial_width, font_arial_height, GetTime(), VBE->x_resolution - 70, y+10, 16, 32, 16);
      if(DrawButton(0,y, 50, 20, 0, 10, 16, shuttext, 16, 32, 16, taskid) == true)
      {
            outw(0x2000, 0x604);
      }
      if(DrawButton(0,y+20, 50, 20, 0, 10, 16, restart, 16, 32, 16, taskid) == true)
      {
            outb(0x64, 0xFE);
      }
      char text[] = "Shell\0";
      if(DrawButton(50,y, 50, 40, 0, 10, 16, text, 16, 32, 16, taskid) == true)
      {
            tasks[TasksLength].priority = 0;
            tasks[TasksLength].taskid = TasksLength;
            tasks[TasksLength].function = &ShellTask;
            iparams[TasksLength * task_params_length + 0] = i * 40;
            iparams[TasksLength * task_params_length + 1] = i * 40;
            iparams[TasksLength * task_params_length + 2] = 300;
            iparams[TasksLength * task_params_length + 3] = 300;
            iparams[TasksLength * task_params_length + 4] = (50.0f / 255.0f * 16.0f);
            iparams[TasksLength * task_params_length + 5] = (50.0f / 255.0f * 32.0f);
            iparams[TasksLength * task_params_length + 6] = (50.0f / 255.0f * 16.0f);
            iparams[TasksLength * task_params_length + 7] = 16;
            iparams[TasksLength * task_params_length + 8] = 32;
            iparams[TasksLength * task_params_length + 10] = 16;
            TasksLength++;
            iparams[TasksLength * task_params_length + 4]++;
      }
      char text2[] = "Ball\0";
      if(DrawButton(100,y, 50, 40, 16, 10, 0, text2, 16, 32, 16, taskid) == true)
      {
            tasks[TasksLength].priority = 0;
            tasks[TasksLength].taskid = TasksLength;
            tasks[TasksLength].function = &BallTask;
            iparams[TasksLength * task_params_length + 0] = i * 40;
            iparams[TasksLength * task_params_length + 1] = i * 40;
            iparams[TasksLength * task_params_length + 2] = 300;
            iparams[TasksLength * task_params_length + 3] = 300;
            iparams[TasksLength * task_params_length + 4] = 0;
            iparams[TasksLength * task_params_length + 5] = 20;
            iparams[TasksLength * task_params_length + 6] = 30;
            iparams[TasksLength * task_params_length + 7] = 5;
            iparams[TasksLength * task_params_length + 8] = 5;
            TasksLength++;
      }
      char text3[] = "Calc\0";
      if(DrawButton(150,y, 50, 40, 16, 10, 0, text3, 16, 32, 16, taskid) == true)
      {
            tasks[TasksLength].priority = 0;
            tasks[TasksLength].taskid = TasksLength;
            tasks[TasksLength].function = &CalcTask;
            iparams[TasksLength * task_params_length + 0] = i * 40;
            iparams[TasksLength * task_params_length + 1] = i * 40;
            iparams[TasksLength * task_params_length + 2] = 150;
            iparams[TasksLength * task_params_length + 3] = 200;
            TasksLength++;
      }
      char text4[] = "Text\0";
      if(DrawButton(200,y, 50, 40, 0, 16, 10, text4, 16, 32, 16, taskid) == true)
      {
            tasks[TasksLength].priority = 0;
            tasks[TasksLength].taskid = TasksLength;
            tasks[TasksLength].function = &TextTask;
            iparams[TasksLength * task_params_length + 0] = i * 40;
            iparams[TasksLength * task_params_length + 1] = i * 40;
            iparams[TasksLength * task_params_length + 2] = 300;
            iparams[TasksLength * task_params_length + 3] = 300;
            TasksLength++;
      }
      uint8_t a1[1];
      mread(a1, 0x7c00, 1);
      uint32_t * a2 = (uint32_t*)0x7c00;
      *a2 = 0x0;
      return 0;
}