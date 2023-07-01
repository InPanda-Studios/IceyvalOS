unsigned strlen(const char* str)
{
    unsigned len = 0;
    while (*str)
    {
        ++len;
        ++str;
    }

    return len;
}
int strcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

int randint(int minVal, int maxVal) {
    uint64_t cyclec = getcyclec();

    // Extract hour, minute, and second components
    uint8_t hour, minute, second;
    get_device_time(&hour, &minute, &second);

    // Combine components into a seed
    uint64_t seed = static_cast<uint64_t>(hour) * 3600 + static_cast<uint64_t>(minute) * 60 + static_cast<uint64_t>(second);

    // Incorporate the cycle count into the seed
    seed ^= cyclec;

    // Initialize the LCG parameters
    uint64_t a = 1103515245ULL;
    uint64_t c = 12345ULL;
    uint64_t m = static_cast<uint64_t>(maxVal - minVal + 1);

    // Generate a random integer between minVal and maxVal (inclusive)
    seed = a * seed + c;
    int randInt = static_cast<int>((seed >> 16) % m) + minVal;
    return randInt;
}


char* strdup(const char* str) {
    size_t length = strlen(str); // Maximum length of the string (adjust as needed)
    static char duplicate[25]; // Create a fixed-size character array

    if (length > 25) {
        // Handle strings that exceed the maximum size
        // You can define custom behavior here
        // For example, return nullptr or truncate the string
        return nullptr_;
    }

    // Copy the original string to the duplicate
    for (size_t i = 0; i <= length; ++i) {
        duplicate[i] = str[i];
    }
    return duplicate;
}
bool isspace(char c)
{
    // Check for whitespace characters
    return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v');
}

bool isdigit(char c)
{
    return (c >= '0' && c <= '9');
}
double strtod(const char* str, char** endptr)
{
    double result = 0.0;
    int sign = 1;
    int decimals = 0;
    bool hasDigits = false;

    // Skip leading whitespace
    while (*str && isspace(*str))
        str++;

    // Check sign
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
    {
        str++;
    }

    // Parse integer part
    while (*str && isdigit(*str))
    {
        result = result * 10 + (*str - '0');
        str++;
        hasDigits = true;
    }

    // Parse decimal part
    if (*str == '.')
    {
        str++;
        double decimalFactor = 0.1;

        while (*str && isdigit(*str))
        {
            result += (*str - '0') * decimalFactor;
            decimalFactor *= 0.1;
            str++;
            hasDigits = true;
            decimals++;
        }
    }

    // Set endptr if provided
    if (endptr)
        *endptr = const_cast<char*>(hasDigits ? str : nullptr);

    // Apply sign and return the result
    return sign * result;
}
double stod(const char* str)
{
    if (str == nullptr_)
        return 0.0;

    // Convert the C-style string to a double using strtod function
    char* endptr;
    double value = strtod(str, &endptr);

    // Check for conversion errors
    if (*endptr != '\0')
    {
        // Handle the error case, such as returning a default value or throwing an exception
        // For simplicity, we'll return 0.0 in case of an error
        return 0.0;
    }

    return value;
}
int strncmp(const char* str1, const char* str2, size_t num) {
    for (size_t i = 0; i < num; ++i) {
        if (str1[i] != str2[i]) {
            return (str1[i] < str2[i]) ? -1 : 1;
        }
        if (str1[i] == '\0') {
            // Reached the end of str1 before num characters
            return 0;
        }
    }
    return 0;
}

int compare(const char *a, const char *b)
{
      bool yes = false;
      for(int i = 0; i < 100; i++)
      {
            if(((int)b[i] == 0 || b[i] == '\n' || b[i] == '\r') && ((int)a[i] == 0 || a[i] == '\n' || a[i] == '\r'))
            {
                  break;
            }
            if(a[i] == b[i])
            {
                  yes = true;
            }
            else
            {
                  yes = false;           
                  break;
            }
      }
      return yes;
}
char *strcpy(char *dest, const char *src) {
    char *dst = dest;
    while (*src) {
        *dst++ = *src++;
    }
    *dst = '\0';
    return dest;
}


int len(const char* str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}
void putc(char c, int taskid)
{
    int pose = 0;
    char *text = tasks[taskid].text;
    for(int i = 0; i < 100; i++)
    {
        if(text[i] != '\0')
            pose++;
        else
            break;
    }
    text[pose] = c;
    text[pose+1] = '\0';
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
                prtext[i] = text[j * sizeof(char)];
                j++;
        }
        k++;
        if(prtext[i] == '\n')
                k=0;
    }
    for(int i = 0; i < 100; i ++)
    {
        text[i] = prtext[i];
    }
}
char* concat(const char* str1, const char* str2) {
    int i, j;
    char *result;
    // Copy str1 into the result buffer
    for (i = 0; str1[i] != '\0'; i++) {
        result[i] = str1[i];
    }
    
    // Copy str2 into the result buffer after str1
    for (j = 0; str2[j] != '\0'; j++) {
        result[i + j] = str2[j];
    }
    
    result[i + j] = '\0'; // Add null terminator to the end of the result string
    return result;
}
char* strcat(char* dest, const char* src) {
    char* result = dest;
    
    // Find the end of the destination string
    while (*dest) {
        ++dest;
    }
    
    // Append characters from the source string to the destination string
    while (*src) {
        *dest = *src;
        ++dest;
        ++src;
    }
    
    // Add the null-terminating character to the end of the concatenated string
    *dest = '\0';
    
    return result;
}

char * strarrconcat(char str[5][100]) {
    char r[500];
    char *result = r;
    int k = 0;
    for (int i = 1; i < 5; i++) {
        int j = 0;
        while (str[i][j] != '\0' && k < 495) { // 495 is the maximum length of the result string
            result[k++] = str[i][j++];
        }
        if (k < 495) { // add space if there is more space in the result string
            result[k++] = ' ';
        } else {
            break;
        }
    }
    result[k-1] = '\0'; // remove the trailing space
    return result;
}



void puts(const char *str, int taskid)
{
    while(*str)
    {
        putc(*str, taskid);
        str++;
    }
}
void clrscr(int taskid)
{
    char *text= tasks[taskid].text;
    for(int i =0; i < 100; i++)
    {
        text[i] = '\0';
    }
}
void cputc(char c, int taskid)
{
    clrscr(taskid);
    putc(c, taskid);
}
void cputs(const char *str, int taskid)
{
    clrscr(taskid);
    puts(str, taskid);
}
void split_string(char* str, char delimiter, char args[5][100]) {
    int start = 0;
    int end = 0;
    int substring_count = 0;

    while (1) {
        while (str[end] != delimiter && str[end] != '\0') {
            end++;
        }
        int substring_length = end - start + 1;
        for (int i = 0; i < substring_length; i++) {
            args[substring_count][i] = str[start + i];
        }
        args[substring_count][substring_length - 1] = '\0';
        substring_count++;
        if (str[end] == '\0') {
            break;
        }
        start = end + 1;
        end = start;
    }
}
char* contains(char* str, char c) {
    while (*str != '\0') {
        if (*str == c) {
            return str;
        }
        str++;
    }
    if (c == '\0') {
        return str;
    }
    return NULL;
}
int atoi(const char* str) {
    int num = 0;
    int sign = 1;

    // Check for sign
    if (*str == '-') {
        sign = -1;
        str++;
    }
    while (*str >= '0' && *str <= '9') {
        num = num * 10 + (*str - '0');
        str++;
    }

    return num * sign;
}
int equate(int num1, char equater, int num2)
{
    switch(equater)
    {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '/':
            if(num2 == 0)
            {
                return 0;
            }
            return (int)(num1 / num2);
        case '*':
            return num1 * num2;
        default:
            return 0;
    }
}
char* itoa(int num) {
    static char str[11];
    int i = 0;
    int sign = 1;

    // Handle negative numbers
    if (num < 0) {
        sign = -1;
        num = -num;
    }

    // Convert the number to a string in reverse order
    do {
        str[i++] = num % 10 + '0';
        num /= 10;
    } while (num > 0);

    // Add the sign character if necessary
    if (sign == -1) {
        str[i++] = '-';
    }

    // Terminate the string
    str[i] = '\0';

    // Reverse the string
    int j, k;
    char temp;
    for (j = 0, k = i - 1; j < k; j++, k--) {
        temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }

    return str;
}
const char * strchr(const char *str, char chr)
{
    if(str == NULL)
        return NULL;
    while(*str)
    {
        if(*str == chr)
            return str;
        str++;
    }
    return NULL;
}
void* memcpy(void* dst, const void* src, uint16_t num)
{
    uint8_t* u8Dst = (uint8_t *)dst;
    const uint8_t* u8Src = (const uint8_t *)src;

    for (uint16_t i = 0; i < num; i++)
        u8Dst[i] = u8Src[i];

    return dst;
}
void * memset(void * ptr, int value, uint16_t num)
{
    uint8_t* u8Ptr = (uint8_t *)ptr;

    for (uint16_t i = 0; i < num; i++)
        u8Ptr[i] = (uint8_t)value;

    return ptr;
}
bool islower(char chr)
{
    return chr >= 'a' && chr <= 'z';
}

char toupper(char chr)
{
    return islower(chr) ? (chr - 'a' + 'A') : chr;
}
int memcmp(const void* ptr1, const void* ptr2, uint16_t num)
{
    const uint8_t* u8Ptr1 = (const uint8_t *)ptr1;
    const uint8_t* u8Ptr2 = (const uint8_t *)ptr2;

    for (uint16_t i = 0; i < num; i++)
        if (u8Ptr1[i] != u8Ptr2[i])
            return 1;

    return 0;
}
char *fread(VFSEntry entry)
{
    if(entry.isDir == false)
    {
        if(entry.openable == true)
        {
            char res[256];
            char *result = res;
            for(int i = 0; i < 256; i++)
                result[i] = entry.src[i];
            return result;
        }
    }
    return (char*)"\0";
}
void fwrite(VFSEntry *entry, char buffer[256])
{
    if(entry->isDir == false)
    {
        if(entry->openable == true)
        {
            for(int i = 0; i < 100; i++)
            {
                entry->src[i] = buffer[i];
            }
        }
    }
}
long atol(const char* str) {
    long result = 0;
    int sign = 1;

    // handle negative sign
    if (*str == '-') {
        sign = -1;
        str++;
    }

    // parse digits
    while (*str != '\0' && *str >= '0' && *str <= '9') {
        result = result * 10 + (*str - '0');
        str++;
    }

    // apply sign
    result *= sign;

    return result;
}
char* strncpy(char* dest, const char* src, size_t count) {
    char* result = dest;
    
    // Copy characters from the source string to the destination string, up to the specified count
    while (*src && count > 0) {
        *dest = *src;
        ++dest;
        ++src;
        --count;
    }
    
    // If the destination string length is less than the specified count, pad with null characters
    while (count > 0) {
        *dest = '\0';
        ++dest;
        --count;
    }
    
    return result;
}

void erase(const char* str, size_t pos, size_t length, char* result)
{
    size_t strLength = strlen(str);
    size_t eraseLength = (pos + length <= strLength) ? length : (strLength - pos);

    if (eraseLength == 0)
    {
        strcpy(result, str);
        return; // Nothing to erase
    }

    size_t resultLength = strLength - eraseLength;

    strncpy(result, str, pos); // Copy the part before the erased portion
    strncpy(result + pos, str + pos + eraseLength, resultLength - pos); // Copy the part after the erased portion

    result[resultLength] = '\0'; // Null-terminate the resulting string
}

char* strncat(char* dest, const char* src, size_t count) {
    char* result = dest;
    
    // Find the end of the destination string
    while (*dest) {
        ++dest;
    }
    
    // Append characters from the source string to the destination string, up to the specified count
    while (*src && count > 0) {
        *dest = *src;
        ++dest;
        ++src;
        --count;
    }
    
    // Add the null-terminating character to the end of the concatenated string
    *dest = '\0';
    
    return result;
}
void extractString(const char* source, int startPos, char delim, char* extractedStr, size_t maxLength) {
    const char* defineStr = source + startPos; // Skip the specified number of characters

    size_t extractedLength = 0;
    while (defineStr[extractedLength] && defineStr[extractedLength] != delim && extractedLength < maxLength - 1) {
        extractedStr[extractedLength] = defineStr[extractedLength];
        ++extractedLength;
    }

    extractedStr[extractedLength] = '\0';
}
bool isCharInCString(const char* str, char c)
{
    if (str == nullptr_)
    {
        return false;
    }

    for (size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c)
        {
            return true;
        }
    }

    return false;
}
bool isNumber(const char* str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
} 

bool isDecimal(const char* str)
{
    bool withFraction = false;

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '.' && !withFraction)
        {
            withFraction = true;
        }
        else if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return withFraction;
}
bool isValidId(const char* t)
{
    if (isCharInCString(t, '-') || isCharInCString(t, '+') || isCharInCString(t, '*') ||
        isCharInCString(t, '/') || isCharInCString(t, '%') || isCharInCString(t, '!') ||
        isCharInCString(t, '='))
    {
        return false;
    }

    // at least one symbol must be a letter
    for (int i = 0; t[i] != '\0'; i++)
    {
        if ((t[i] >= 'A' && t[i] <= 'Z') || (t[i] >= 'a' && t[i] <= 'z'))
        {
            return true;
        }
    }

    return false;
}

