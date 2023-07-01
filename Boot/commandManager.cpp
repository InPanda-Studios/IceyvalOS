struct Command
{
      void (*function) (int, char[5][100]);
      char string[100];
};
void echo(int taskid, char args[5][100])
{
      char *result = strarrconcat(args);
      cputs(result, taskid);
}
void calc(int taskid, char args[5][100])
{
      char num1[100];
      for (int j = 0; j < 100; j++)
      {
            num1[j] = args[1][j];
      }
      char num2[100];
      for (int j = 0; j < 100; j++)
      {
            num2[j] = args[3][j];
      }
      int n1 = atoi(num1);
      int n2 = atoi(num2);
      char equater = args[2][0];
      int ans = equate(n1, equater, n2);
      char *cans = itoa(ans);
      cputs(cans, taskid);
}
void osinfo(int taskid, char args[5][100])
{
      char text[] = "IceValley Os.\nMade by Filip and Xing!";
      cputs(text, taskid);
}
void clr(int taskid, char args[5][100])
{
      char text[] = "\0";
      cputs(text, taskid);
}
void shutdown(int taskid, char args[5][100])
{
      outw(0x2000, 0x604);
}
void reboot(int taskid, char args[5][100])
{
      outb(0x64, 0xFE);
}
void gettime(int taskid, char args[5][100])
{
      char *time = GetTime();
      cputs(time, taskid);
}
void testsound(int taskid, char args[5][100])
{
      enable_pc_speaker();
      play_note(MC1, 500);
      rest(250);
      play_note(MC2, 250);
      rest(250);
      play_note(As4, 500);
      rest(250);
      play_note((note_freq_t)3000, 250);
      disable_pc_speaker();
}
void rcl(int taskid, char args[5][100])
{
      char *src = fread(mainFile);
      RClass(src, true, taskid);
}