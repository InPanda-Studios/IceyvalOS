#define PC_SPEAKER_PORT 0x61

typedef enum note_freq_t
{
    C2  = 18356,
    MC1 = 1821,
    MC2 = 1952,
    Cs2 = 17292,
    Db2 = Cs2,
    D2  = 16344,
    Ds2 = 15297,
    Eb2 = Ds2,
    E2  = 14551,
    F2  = 13714,
    Fs2 = 12829,
    Gb2 = Fs2,
    G2  = 12175,
    Gs2 = 11472,
    Ab2 = Gs2,
    A2  = 10847,
    As2 = 10198,
    Bb2 = As2,
    B2  = 9700,
    C3  = 9121,
    Cs3 = 8609,
    Db3 = Cs3,
    D3  = 8126,
    Ds3 = 7670,
    Eb3 = Ds3,
    E3  = 7239,
    F3  = 6833,
    Fs3 = 6449,
    Gb3 = Fs3,
    G3  = 6087,
    Gs3 = 5746,
    Ab3 = Gs3,
    A3  = 5423,
    As3 = 5119,
    Bb3 = As3,
    B3  = 4831,
    C4  = 4560,  
    Cs4 = 4304,
    Db4 = Cs4,
    D4  = 4063,
    Ds4 = 3834,
    Eb4 = Ds4,
    E4  = 3619,
    F4  = 3416,
    Fs4 = 3224,
    Gb4 = Fs4,
    G4  = 3043,
    Gs4 = 2873,
    Ab4 = Gs4,
    A4  = 2711,  
    As4 = 2559,
    Bb4 = As4,
    B4  = 2415,
    C5  = 2280,
    Cs5 = 2152,
    Db5 = Cs5,
    D5  = 2031,
    Ds5 = 1918,
    Eb5 = Ds5,
    E5  = 1810,
    F5  = 1708,
    Fs5 = 1612,
    Gb5 = Fs5,
    G5  = 1522,
    Gs5 = 1437,
    Ab5 = Gs5,
    A5  = 1356,
    As5 = 1280,
    Bb5 = As5,
    B5  = 1208,
    C6  = 1140
} note_freq_t;
void set_pit_channel_mode_frequency(const uint8_t channel, const uint8_t operating_mode, const uint16_t frequency)
{
    if (channel > 2) return;
    __asm__ __volatile__ ("cli");
    outb(0x43, (channel << 6) | (0x3 << 4) | (operating_mode << 1));
    outb(0x40 + channel, (uint8_t)frequency);
    outb(0x40 + channel, (uint8_t)(frequency >> 8));
    __asm__ __volatile__ ("sti");
}

void enable_pc_speaker()
{
      uint8_t temp = inb(PC_SPEAKER_PORT);
      outb(PC_SPEAKER_PORT, temp | 3);
}
void disable_pc_speaker()
{
      uint8_t temp = inb(PC_SPEAKER_PORT);
      outb(PC_SPEAKER_PORT, temp & 0xfc);
}
void play_note(const note_freq_t note, const uint32_t durationMs)
{
      set_pit_channel_mode_frequency(2, 3, note);
      sleep_milliseconds(durationMs);
}
void rest(const uint32_t ms_duration)
{
    set_pit_channel_mode_frequency(2, 3, 40);
    sleep_milliseconds(ms_duration);
}