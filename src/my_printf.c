#include "usart_basic.h"
#include "my_printf.h"
#include <stdarg.h>
#include <stdio.h>

static void my_putchar(unsigned char sdbyte);


static void my_putchar(unsigned char sdbyte) {
    USART_0_write(sdbyte);
}

void my_printf(char *str, ...) {
    char buf[256];
    uint16_t i = 0;
    int rc = 0;
    va_list ptr;
    va_start(ptr, str);
    rc = vsnprintf(buf, 256, str, ptr);
    va_end(ptr);
    if (rc > 0) {
        while (buf[i]) {
            my_putchar(buf[i]);
         	while (USART_0_is_tx_busy()){}
		    i++;
        }
    }
}
