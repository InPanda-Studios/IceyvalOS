
int mx,my;
int left_clicked, right_clicked, middle_clicked;
int current_byte = 0;
uint8_t bytes[4] = {0};
int Scancode = -1;
int PrevScancode = -1;
int mouse_possessed_taskid = 0;
#define pic1_command 0x20
#define pic1_data 0x21
#define pic2_command 0xa0
#define pic2_data 0xa1
#define icw1_def 0x10
#define icw1_icw4 0x01
#define icw4_x86 0x01
#define y_overflow      0b10000000
#define x_overflow      0b01000000
#define y_negative      0b00100000
#define x_negative      0b00010000
#define always_set      0b00001000
#define middle_click    0b00000100
#define right_click     0b00000010
#define left_click      0b00000001
#define unused_a        0b10000000
#define unused_b        0b01000000
void InitialiseIDT();
extern "C" void LoadIDT();
extern "C" void HandleISR1();
extern "C" void HandleISR12();
void RemapPIC();
struct IDTElement
{
    unsigned short lower;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short higher;
};
struct IDTElement _idt[256];
extern unsigned int isr1, isr12;
unsigned int base, base12;
unsigned char inportb(unsigned short port)
{
    unsigned char value;
    __asm__ __volatile__("inb %1, %0" : "=a" (value) : "dN" (port));
    return value;
}

void outportb(unsigned short port, unsigned char data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}
void outw(int a, int b)
{
    __asm__ ("outw %%ax, %%dx" : : "a"(a), "d"(b) );
}
void InitialiseIDT()
{
    _idt[1].lower = (base & 0xffff);
    _idt[1].higher = (base >> 16) & 0xffff;
    _idt[1].selector = 0x08;
    _idt[1].zero = 0;
    _idt[1].flags = 0x8e; 
    _idt[12].lower = (base12 & 0xffff);
    _idt[12].higher = (base12 >> 16) & 0xffff;
    _idt[12].selector = 0x08;
    _idt[12].zero = 0;
    _idt[12].flags = 0x8e; 
    RemapPIC();
    outportb(0x21, 0b11111001);
    outportb(0xa1, 0x00);
    LoadIDT();
}
void RemapPIC()
{
    unsigned char a, b;
    a = inportb(pic1_data);
    b = inportb(pic2_data);
    outportb(pic1_command, icw1_def | icw1_icw4);
    outportb(pic2_command, icw1_def | icw1_icw4);
    outportb(pic1_data, 0);
    outportb(pic2_data, 8);
    outportb(pic1_data, 4);
    outportb(pic2_data, 2);
    outportb(pic1_data, icw4_x86);
    outportb(pic2_data, icw4_x86);
    outportb(pic1_data, a);
    outportb(pic2_data, b);
}
extern "C" void HandleISR1()
{
    PrevScancode = Scancode;
    Scancode = inportb(0x60);
    outportb(0xa0, 0x20);
    outportb(0x20, 0x20);
}
void HandleMouseInterrupt();
extern "C" void HandleISR12()
{
    HandleMouseInterrupt();
    outportb(0xa0, 0x20);
    outportb(0x20, 0x20);
}
void MouseWait(unsigned char type)
{
    int time_out = 100000;
    if(type == 0)
    {
        while(time_out--)
        {
            if((inportb(0x64) & 1) == 1)
                return;
        }
    }
    else 
    {
        while(time_out--)
        {
            if((inportb(0x64) & 2) == 0)
                return;
        }
    }
}
void MouseWrite(unsigned char data)
{
    MouseWait(1);
    outportb(0x64, 0xd4);
    MouseWait(1);
    outportb(0x60, data);

}
unsigned char MouseRead()
{
    MouseWait(0);
    return inportb(0x60);
}
void InitialiseMouse()
{
    unsigned char status;
    MouseWait(1);
    outportb(0x64, 0xd4);
    MouseWait(1);
    outportb(0x64, 0xa8);
    MouseWait(1);
    outportb(0x64, 0x20);
    MouseWait(0);
    status = (inportb(0x60) | 2);
    MouseWait(1);
    outportb(0x64, 0x60);
    MouseWait(1);
    outportb(0x60, status);
    MouseWrite(0xf6);
    MouseRead();
    MouseWrite(0xf4);
    MouseRead();
}
void HandleMousePacket();
void HandleMouseInterrupt()
{
    uint8_t byte = MouseRead();
    if(current_byte == 0 && !(byte & always_set))
        return;
    bytes[current_byte] = byte;
    current_byte++;
    if(current_byte >= 3)
        current_byte = 0;
    if(current_byte == 0)
        HandleMousePacket();
}
void HandleMousePacket()
{
    VBEInfoBlock* VBE = (VBEInfoBlock* )VBEInfoAddress;
    uint8_t status = bytes[0];
    int32_t change_x = (int32_t) bytes [1];
    int32_t change_y = (int32_t) bytes [2];
    if(status & x_overflow || status & y_overflow)
        return;
    
    if(status & x_negative)
        change_x |= 0xffffff00;
    if(status & y_negative)
        change_y |= 0xffffff00;
    
    left_clicked = status & left_click;
    right_clicked = status & right_click;
    middle_clicked = status & middle_click;
    int speed = 2;
    if(change_x > 0)
        mx+=speed;
    else if(change_x < 0)
        mx-=speed;
    if(change_y > 0)
        my-=speed;
    else if(change_y < 0)
        my+=speed;
    if (mx < 0)
        mx = 0;
    else if (mx > VBE->x_resolution - 10)
        mx = VBE->x_resolution - 10;
    if (my < 0)
        my = 0;
    else if (my > VBE->y_resolution-10)
        my = VBE->y_resolution-10;
    
}
bool shift_pressed = false;
bool caps_pressed = false;
bool escape_pressed = false;
bool backspace_pressed = false;
bool alt_pressed = false;
bool ctrl_pressed = false;
bool enter_pressed = false;
bool num_lock = false;
int ProcessScancode(int scancode)
{
    if (scancode == 0x01)
        escape_pressed = true;
    else if (scancode == 0x02)
    {
        if(shift_pressed == true)
            return '!';
        else
            return '1';
    }
    else if (scancode == 0x03)
    {
        if(shift_pressed == true)
            return '"';
        else
            return '2';
    }
    else if (scancode == 0x04)
    {
        if(shift_pressed == true)
            return '£';
        else
            return '3';
    }
    else if (scancode == 0x05)
    {
        if(shift_pressed == true)
            return '$';
        else
            return '4';
    }
    else if (scancode == 0x06)
    {
        if(shift_pressed == true)
            return '%';
        else
            return '5';
    }
    else if (scancode == 0x07)
    {
        if(shift_pressed == true)
            return '^';
        else
            return '6';
    }
    else if (scancode == 0x08)
    {
        if(shift_pressed == true)
            return '&';
        else
            return '7';
    }
    else if (scancode == 0x09)
    {
        if(shift_pressed == true)
            return '*';
        else
            return '8';
    }
    else if (scancode == 0x0a)
    {
        if(shift_pressed == true)
            return '(';
        else
            return '9';
    }
    else if (scancode == 0x0b)
    {
        if(shift_pressed == true)
            return ')';
        else
            return '0';
    }
    else if (scancode == 0x0c)
    {
        if(shift_pressed == true)
            return '_';
        else
            return '-';
    }
    else if (scancode == 0x0d)
    {
        if(shift_pressed == true)
            return '+';
        else
            return '=';
    }
    else if (scancode == 0x0e)
    {
        backspace_pressed = true;
        Scancode = -1;
    }
    else if (scancode == 0x0f)
    {
        return '\t';
    }
    else if (scancode == 0x10)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'Q';
        else
            return 'q';
    }
    else if (scancode == 0x11)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'W';
        else
            return 'w';
    }
    else if (scancode == 0x12)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'E';
        else
            return 'e';
    }
    else if (scancode == 0x13)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'R';
        else
            return 'r';
    }
    else if (scancode == 0x14)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'T';
        else
            return 't';
    }
    else if (scancode == 0x15)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'Y';
        else
            return 'y';
    }
    else if (scancode == 0x16)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'U';
        else
            return 'u';
    }
    else if (scancode == 0x17)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'I';
        else
            return 'i';
    }
    else if (scancode == 0x18)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'O';
        else
            return 'o';
    }
    else if (scancode == 0x19)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'P';
        else
            return 'p';
    }
    else if (scancode == 0x1a)
    {
        if(shift_pressed == true)
            return '{';
        else
            return '[';
    }
    else if (scancode == 0x1b)
    {
        if(shift_pressed == true)
            return '}';
        else
            return ']';
    }
    else if (scancode == 0x1c)
    {
        enter_pressed = true;
        return '\n';
    }
    else if (scancode == 0x1d)
    {
        ctrl_pressed = true;
    }
    else if (scancode == 0x1e)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'A';
        else
            return 'a';
    }
    else if (scancode == 0x1f)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'S';
        else
            return 's';
    }
    else if (scancode == 0x20)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'D';
        else
            return 'd';
    }
    else if (scancode == 0x21)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'F';
        else
            return 'f';
    }
    else if (scancode == 0x22)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'G';
        else
            return 'g';
    }
    else if (scancode == 0x23)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'H';
        else
            return 'h';
    }
    else if (scancode == 0x24)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'J';
        else
            return 'j';
    }
    else if (scancode == 0x25)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'K';
        else
            return 'k';
    }
    else if (scancode == 0x26)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'L';
        else
            return 'l';
    }
    else if (scancode == 0x27)
    {
        if(shift_pressed == true)
            return ':';
        else
            return ';';
    }
    else if (scancode == 0x28)
    {
        if(shift_pressed == true)
            return '@';
        else
            return '\'';
    }
    else if (scancode == 0x29)
    {
        if(shift_pressed == true)
            return '¬';
        else
            return '`';
    }
    else if (scancode == 0x2a)
    {
        shift_pressed = true;
        Scancode = -1;
    }
    else if (scancode == 0x2b)
    {
        if(shift_pressed == true)
            return '|';
        else
            return '\\';
    }
    else if (scancode == 0x2c)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'Z';
        else
            return 'z';
    }
    else if (scancode == 0x2d)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'X';
        else
            return 'x';
    }
    else if (scancode == 0x2e)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'C';
        else
            return 'c';
    }
    else if (scancode == 0x2f)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'V';
        else
            return 'v';
    }
    else if (scancode == 0x30)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'B';
        else
            return 'b';
    }
    else if (scancode == 0x31)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'N';
        else
            return 'n';
    }
    else if (scancode == 0x32)
    {
        if(shift_pressed == true || caps_pressed == true)
            return 'M';
        else
            return 'm';
    }
    else if (scancode == 0x33)
    {
        if(shift_pressed == true)
            return '<';
        else
            return ',';
    }
    else if (scancode == 0x34)
    {
        if(shift_pressed == true)
            return '>';
        else
            return '.';
    }
    else if (scancode == 0x35)
    {
        if(PrevScancode == 0xe0)
            return '/';
        else
        {
            if (shift_pressed)
                return '?';
            else
                return '/';
        }
    }
    else if (scancode == 0x36)
    {
        shift_pressed = true;
    }
    else if(scancode == 0x37)
    {
        return '*';
    }
    else if (scancode == 0x38)
    {
        alt_pressed = true;
    }
    else if (scancode == 0x39)
    {
        return ' ';
    }
    else if (scancode == 0x3a)
    {
        caps_pressed = not(caps_pressed);
        Scancode = -1;
    }
    else if(scancode == 0x45)
    {
        num_lock = not(num_lock);
        Scancode = -1;
    }
    else if(scancode == 0x47)
    {
        if(num_lock)
            return '7';
    }
    else if(scancode == 0x48)
    {
        if(num_lock)
            return '8';
    }
    else if(scancode == 0x49)
    {
        if(num_lock)
            return '9';
    }
    else if(scancode == 0x4a)
    {
        return '-';
    }
    else if(scancode == 0x4b)
    {
        if(num_lock)
            return '4';
    }
    else if(scancode == 0x4c)
    {
        if(num_lock)
            return '5';
    }
    else if(scancode == 0x4d)
    {
        if(num_lock)
            return '6';
    }
    else if(scancode == 0x4e)
    {
        return '+';
    }
    else if(scancode == 0x4f)
    {
        if(num_lock)
            return '1';
    }
    else if(scancode == 0x50)
    {
        if(num_lock)
            return '1';
    }
    else if(scancode == 0x51)
    {
        if(num_lock)
            return '2';
    }
    else if(scancode == 0x52)
    {
        if(num_lock)
            return '3';
    }
    else if(scancode == 0x53)
    {
        return '.';
    }
    else if(scancode == 0x52)
    {
        if(num_lock)
            return '3';
    }
    else if (scancode == 0xAA)
    {
        shift_pressed = false;
        Scancode = -1;
    }
    else if (scancode == 0xB6)
    {
        shift_pressed = false;
        Scancode = -1;
    }
    return '\0';
}