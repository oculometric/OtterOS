#include <stddef.h> //we can use it: it doesnt use any platform-related api functions
#include <stdint.h> //include it to get int16_t and some integer types
#include <stdbool.h>

static inline uint8_t inb (uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

static inline void outb( unsigned short port, unsigned char val ) {
   asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) );
}
