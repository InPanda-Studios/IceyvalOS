#include "memory.hpp"
void mread(uint8_t* buffer, long address, size_t size) {
    uint8_t* buffer_ptr = buffer;
    long address_ptr = address;

    while (size > 0) {
        // set up the segment registers for accessing memory
        asm volatile("pushw %%es\n\t"
                     "pushw %%ds\n\t"
                     "popw %%es\n\t"
                     "movl %0, %%eax\n\t"
                     "movw %%ax, %%ds\n\t"
                     "movw %%ax, %%es\n\t"
                     "popw %%es\n\t"
                     :
                     : "r" (address_ptr >> 16)
                     : "eax", "memory");

        // determine the number of bytes to read in this iteration
        size_t read_size = size;
        if (read_size > 65536) {
            read_size = 65536;
        }

        // read the bytes from memory
        asm volatile("rep movsb\n\t"
                     :
                     : "S" (address_ptr), "D" (buffer_ptr), "c" (read_size)
                     : "memory");

        // update the buffer and address pointers
        buffer_ptr += read_size;
        address_ptr += read_size;
        size -= read_size;
    }
}

