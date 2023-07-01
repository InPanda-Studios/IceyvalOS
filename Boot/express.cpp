#define RTC_PORT 0x70

/* define the value port address for the RTC */
#define RTC_VALUE_PORT 0x71

/* define the RTC registers */
#define RTC_SECONDS 0x00
#define RTC_MINUTES 0x02
#define RTC_HOURS 0x04
#define RTC_STATUS_B_12_HOUR_FORMAT (1 << 1)
#define RTC_STATUS_B 0x0B
#define RTC_HOURS_PM 0x80
uint8_t read_rtc_register(uint8_t reg) {
    /* select the RTC register */
    outb(RTC_PORT, reg);
    
    /* read the value from the RTC */
    return inb(RTC_VALUE_PORT);
}
void get_device_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds) {
    /* read the hours, minutes, and seconds registers from the RTC */
    uint8_t raw_hours = read_rtc_register(RTC_HOURS);
    uint8_t raw_minutes = read_rtc_register(RTC_MINUTES);
    uint8_t raw_seconds = read_rtc_register(RTC_SECONDS);

    /* check if the 12-hour format is enabled */
    bool is_12_hour_format = (read_rtc_register(RTC_STATUS_B) & RTC_STATUS_B_12_HOUR_FORMAT);

    /* convert the BCD-encoded values to decimal */
    *minutes = ((raw_minutes & 0x0F) + ((raw_minutes >> 4) * 10));
    *seconds = ((raw_seconds & 0x0F) + ((raw_seconds >> 4) * 10));

    if (is_12_hour_format) {
        /* convert 12-hour format to 24-hour format */
        bool is_pm = (raw_hours & RTC_HOURS_PM);
        uint8_t hours_12 = (raw_hours & 0x0F) + ((raw_hours >> 4) * 10);
        if (hours_12 == 12) {
            hours_12 = 0;
        }
        *hours = hours_12 + (is_pm ? 12 : 0);
    } else {
        /* convert 24-hour format */
        *hours = ((raw_hours & 0x0F) + ((raw_hours >> 4) * 10));
    }
}uint64_t getcyclec() {
    uint32_t high, low;
    asm volatile("rdtsc" : "=a"(low), "=d"(high));
    return ((uint64_t)high << 32) | low;
}