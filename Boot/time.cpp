

char * GetTime()
{
      uint8_t hours, minutes, seconds;
      get_device_time(&hours, &minutes, &seconds);
      char *houre = itoa(hours);
      char hour[10];
      for(int i = 0; i < 10; i++)
      {
            hour[i] = houre[i];
      }
      if(len(hour) == 1)
      {
            hour[1] = hour[0];
            hour[0] = '0';
      }
      char *minutee = itoa(minutes);
      char minute[10];
      for(int i = 0; i < 10; i++)
      {
            minute[i] = minutee[i];
      }
      if(len(minute) == 1)
      {
            minute[1] = minute[0];
            minute[0] = '0';
      }
      char *seconde = itoa(seconds);
      char second[10];
      for(int i = 0; i < 10; i++)
      {
            second[i] = seconde[i];
      }
      if(len(second) == 1)
      {
            second[1] = second[0];
            second[0] = '0';
      }
      char colon[] = ":";
      char *time = concat(hour, colon);
      time = concat(time, minute);
      time = concat(time, colon);
      time = concat(time, second);
      return time;
}
void sleep_seconds(const uint16_t seconds) 
{
    unsigned int tick_count = (seconds*100*100) * 1193; // 1193 is the number of clock ticks per millisecond

    __asm__ volatile (
        "1: \n"
        "movl %0, %%ecx \n"
        "0: \n"
        "loop 0b \n"
        : // no output operands
        : "r" (tick_count)
        : "%ecx"
    );
}
void sleep_milliseconds(unsigned int milliseconds) {
    unsigned int tick_count = (milliseconds*100) * 1193; // 1193 is the number of clock ticks per millisecond

    __asm__ volatile (
        "1: \n"
        "movl %0, %%ecx \n"
        "0: \n"
        "loop 0b \n"
        : // no output operands
        : "r" (tick_count)
        : "%ecx"
    );
}






