int rcla = 0;
int rclb = 0;
int rclc = 0;
int rcld = 0;
int rcle = 0;
int rclf = 0;
int rclg = 0;
int rclh = 0; 
int rcli = 0;
int rclj = 0;
int rclk = 0;
int rcll = 0;
int rclm = 0;
bool comment = true;
bool starte = false, ende = false, hassq = false, hascq = false;
int stack[13];
int lint[1024];
int lpos = 0;
int pow(int base, int exponent) {
    int result = 1;
    int i;
    if (exponent >= 0) {
        for (i = 0; i < exponent; i++) {
            result *= base;
        }
    }
    else {
        for (i = 0; i > exponent; i--) {
            result /= base;
        }
    }
    return result;
}

void clear(char arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = '\0';
    }
}
bool nope(bool input)
{
      return (input == false) ? (1) : (0);
}
bool contaiins(char* str, char c) {
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if (str[i] == c) {
            return true;
        }
    }
    return false;
}
int GetValue(char c)
{
      if(c == 'a')
            return rcla;
      else if(c == 'b')
            return rclb;
      else if(c == 'c')
            return rclc;
      else if(c == 'd')
            return rcld;
      else if(c == 'e')
            return rcle;
      else if(c == 'f')
            return rclf;
      else if(c == 'g')
            return rclg;
      else if(c == 'h')
            return rclh;
      else if(c == 'i')
            return rcli;
      else if(c == 'j')
            return rclj;
      else if(c == 'k')
            return rclk;
      else if(c == 'l')
            return rcll;
      else if(c == 'm')
            return rclm;
      else if(c == 't')
            return lint[lpos];
      else
            return 0;
}
void SetValue(char pr, char l)
{
      if(pr == 'a')
      {
            rcla = GetValue(l);
            return;
      }else if(pr == 'b')
      {
            rclb = GetValue(l);
                  return;
      }else if(pr == 'c')
      {
            rclc = GetValue(l);
                  return;
      }else if(pr == 'd')
      {
            rcld = GetValue(l);
                  return;
      }else if(pr == 'e')
      {
            rcle = GetValue(l);
                  return;
      }else if(pr == 'f')
      {
            rclf = GetValue(l);
                  return;
      }else if(pr == 'g')
      {
            rclg = GetValue(l);
                  return;
      }else if(pr == 'h')
      {
            rclh = GetValue(l);
                  return;
      }
      else if(pr == 'i')
      {
            rcli = GetValue(l);
                  return;
      }else if(pr == 'j')
      {
            rclj = GetValue(l);
                  return;
      }else if(pr == 'k')
      {
            rclk = GetValue(l);
                  return;
      }else if(pr == 'l')
      {
                  rcll = GetValue(l);
                  return;
      }else if(pr == 'm')
      {
                  rclm = GetValue(l);
                  return;
      }
      else if(pr == 't')
      {
            lint[lpos] = GetValue(l);
            return;
      }
      else
      {
            return;
      }
}
void Push(char la)
{
      if(la == 'a')
            stack[0] = rcla;
      else if(la == 'b')
            stack[1] = rclb;
      else if(la == 'c')
            stack[2] = rclc;
      else if(la == 'd')
            stack[3] = rcld;
      else if(la == 'e')
            stack[4] = rcle;
      else if(la == 'f')
            stack[5] = rclf;
      else if(la == 'g')
            stack[6] = rclg;
      else if(la == 'h')
            stack[7] = rclh;
      else if(la == 'i')
            stack[8] = rcli;
      else if(la == 'j')
            stack[9] = rclj;
      else if(la == 'k')
            stack[10] = rclk;
      else if(la == 'l')
            stack[11] = rcll;
      else if(la == 'm')
            stack[12] = rclm;
      else if(la == 'y')
      {
            stack[0] = rcla;
            stack[1] = rclb;
            stack[2] = rclc;
            stack[3] = rcld;
            stack[4] = rcle;
            stack[5] = rclf;
            stack[6] = rclg;
            stack[7] = rclh;
            stack[8] = rcli;
            stack[9] = rclj;
            stack[10] = rclk;
            stack[11] = rcll;
            stack[12] = rclm;
      }
}
void Pop(char la)
{
      if(la == 'a')
            rcla = stack[0];
      else if(la == 'b')
            rclb = stack[1];
      else if(la == 'c')
            rclc = stack[2];
      else if(la == 'd')
            rcld = stack[3];
      else if(la == 'e')
            rcle = stack[4];
      else if(la == 'f')
            rclf = stack[5];
      else if(la == 'g')
            rclg = stack[6];
      else if(la == 'h')
            rclh = stack[7];
      else if(la == 'i')
            rcli = stack[8];
      else if(la == 'j')
            rclj = stack[9];
      else if(la == 'k')
            rclk = stack[10];
      else if(la == 'l')
            rcll = stack[11];
      else if(la == 'm')
            rclm = stack[12];
      else if(la == 'y')
      {
            rcla = stack[0];
            rclb = stack[1];
            rclc = stack[2];
            rcld = stack[3];
            rcle = stack[4];
            rclf = stack[5];
            rclg = stack[6];
            rclh = stack[7];
            rcli = stack[8];
            rclj = stack[9];
            rclk = stack[10];
            rcll = stack[11];
            rclm = stack[12];
      }
}
void ExecuteInstruction(char src[1024], bool printing, int taskid)
{
      char op[] = { '*', '/', '=', '<', '>', '+', '-', '^' };
      char rop[] = {'u', 'o'};
      int am = 1;
      char cmdd[1024];
      bool bracket = false, cbracket = false;
      bool digit = false;
      int pos = 0;
      int cpos = 0;
      while(pos < strlen(src))
      {
            char ch = src[pos];
            char la = src[pos+1];
            char prev = '\0';
            if(pos != 0)
            {
                  prev = src[pos-1];
            }
            if(ch == '\0')
            {
                  break;
            }else if(ch == 'a')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'a';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rcla += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'b')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'b';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclb += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'c')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'c';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclc += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'd')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'd';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rcld += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'e')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'e';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rcle += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'f')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'f';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclf += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'g')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'g';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclg += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'h')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'h';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclh += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'i')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'i';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rcli += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'j')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'j';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclj += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'k')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'k';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclk += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'l')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'l';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rcll += am;
                  }
                  pos++;
                  continue;
            }else if(ch == 'm')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(rop, prev))
                  {
                        pos++;
                        continue;
                  }
                  if (comment == false)
                  {
                        if (bracket)
                        {
                              cmdd[cpos] = 'm';
                              pos++;
                              cpos++;
                              continue;
                        }
                        rclm += am;
                  }
                  pos++;
                  continue;
            }else if(ch == '[')
            {
                  if (comment == false)
                  {
                        bracket = true;
                        hassq = true;
                  }
                  pos++;
                  continue;
            }else if(ch == ']')
            {
                  if (hassq)
                  {
                        if (comment == false)
                        {
                              if (bracket)
                              {
                                    while (rclm != 0)
                                    {
                                          ExecuteInstruction(cmdd, printing, taskid);
                                    }
                                    clear(cmdd, 1024);
                              }
                              bracket = false;
                        }
                  }
                  pos++;
                  continue;
            }
            else if(ch == '#')
            {
                  if(starte)
                        comment = nope(comment);
                  pos++;
                  continue;
            }
            else if(ch == 'p')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = 'p';
                              cpos++;
                              pos++;
                              continue;
                        }
                        am = 1;
                  }
                  pos++;
                  continue;
            }else if(ch == 'n')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = 'n';
                              cpos++;
                              pos++;
                              continue;
                        }
                        am = -1;
                  }
                  pos++;
                  continue;
            }else if(ch == '(')
            {
                  if(ende == false)
                  {
                        comment = false;
                        starte = true;
                  }
                  pos++;
                  continue;
            }else if(ch == '.')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '.';
                              cpos++;
                              pos++;
                              continue;
                        }
                        if(printing)
                        {
                              if(digit == false)
                                    putc((char)rcla, taskid);
                              else
                                    puts(itoa(rcla), taskid);
                        }
                  }
                  pos++;
                  continue;
            }else if(ch == '*')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '*';
                              cpos++;
                              pos++;
                              continue;
                        }
                        rcla = GetValue(prev) * GetValue(la);
                  }
                  pos++;
                  continue;
            }else if(ch == '/')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '/';
                              cpos++;
                              pos++;
                              continue;
                        }
                        rcla = (int)(GetValue(prev) / GetValue(la));
                  }
                  pos++;
                  continue;
            }
            else if(ch == ')')
            {
                  if(starte != false)
                  {
                        pos++;
                        starte = false;
                        ende = true;
                        comment = true;
                        break;
                  }
                  else
                        continue;
            }
            else if(ch == '=')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '=';
                              cpos++;
                              pos++;
                              continue;
                        }
                        SetValue(prev, la);
                  }
                  pos++;
                  continue;
            }else if(ch == 't')
            {
                  if (contaiins(op, la))
                  {
                        pos++;
                        continue;
                  }
                  if (contaiins(op, prev))
                  {
                        pos++;
                        continue;
                  }
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = 't';
                              cpos++;
                              pos++;
                              continue;
                        }
                        lint[lpos]+=am;
                  }
                  pos++;
                  continue;
            }else if(ch == '<')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '<';
                              cpos++;
                              pos++;
                              continue;
                        }
                        bool t = GetValue(prev) < GetValue(la);
                        rcla = (t == true) ? (1) : (0);
                  }
                  pos++;
                  continue;
            }else if(ch == '>')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '>';
                              cpos++;
                              pos++;
                              continue;
                        }
                        bool t = GetValue(prev) > GetValue(la);
                        rcla = (t == true) ? (1) : (0);
                  }
                  pos++;
                  continue;
            }else if(ch == '+')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '+';
                              cpos++;
                              pos++;
                              continue;
                        }
                        rcla = (int)(GetValue(prev) + GetValue(la));
                  }
                  pos++;
                  continue;
            }else if(ch == '-')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '-';
                              cpos++;
                              pos++;
                              continue;
                        }
                        rcla = (int)(GetValue(prev) - GetValue(la));
                  }
                  pos++;
                  continue;
            }
            else if(ch == ':')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = ':';
                              cpos++;
                              pos++;
                              continue;
                        }
                        digit = nope(digit);
                  }
                  pos++;
                  continue;
            }
            else if(ch == '{')
            {
                  if(comment == false)
                  {
                        cbracket = true;
                        hascq = true;
                  }
                  pos++;
                  continue;
            }else if(ch == '}')
            {
                  if(hascq)
                  {
                        if(comment == false)
                        {
                              if(cbracket)
                              {
                                    if(rcla == 1)
                                    {
                                          ExecuteInstruction(cmdd, printing, taskid);
                                    }
                                    clear(cmdd, 1024);
                              }
                              cbracket = false;
                        }
                  }
                  pos++;
                  continue;
            }else if(ch == '^')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = '^';
                              cpos++;
                              pos++;
                              continue;
                        }
                        rcla = pow(GetValue(prev), GetValue(la));
                  }
            }else if(ch == 'z')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = 'z';
                              cpos++;
                              pos++;
                              continue;
                        }
                        if(lpos != 0)
                        {
                              lpos -= 1;
                              int _ = lint[lpos];
                        }
                  }
                  pos++;
                  continue;
            }else if(ch == 'x')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = 'x';
                              cpos++;
                              pos++;
                              continue;
                        }
                        lpos += 1;
                        int _ = lint[lpos];
                  }
                  pos++;
                  continue;
            }else if(ch == 'u')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = 'u';
                              cpos++;
                              pos++;
                              continue;
                        }
                        Push(la);
                  }
                  pos++;
                  continue;
            }else if(ch == 'o')
            {
                  if(comment == false)
                  {
                        if(bracket)
                        {
                              cmdd[cpos] = 'o';
                              cpos++;
                              pos++;
                              continue;
                        }
                        Pop(la);
                  }
                  pos++;
                  continue;
            }else if(ch == 'y')
            {
                  pos++;
                  continue;
            }
            else
            {
                  if(comment)
                        pos++;
                  else
                        break;
                  continue;
            }
      }
}
void RClass(char src[1024], bool printing, int taskid)
{
      rcla = 0;
      rclb = 0;
      rclc = 0;
      rcld = 0;
      rcle = 0;
      rclf = 0;
      rclg = 0;
      rclh = 0; 
      rcli = 0;
      rclj = 0;
      rclk = 0;
      rcll = 0;
      rclm = 0;
      comment = true;
      starte = false, ende = false, hassq = false, hascq = false;
      for(int i = 0; i < 1024; i++)
      {
            lint[i] = 0;
      }
      for(int i = 0; i < 13; i++)
      {
            stack[i] = 0;
      }
      lpos = 0;
      ExecuteInstruction(src, printing, taskid);
}