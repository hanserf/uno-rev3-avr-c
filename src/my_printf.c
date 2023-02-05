#include "my_printf.h"
#include "usart_basic.h"
#include <stdarg.h>
#include <stdio.h>

static void my_putchar(unsigned char sdbyte);

static void my_putchar(unsigned char sdbyte) {
#if USE_USART
    /* Will block until character is sent */
    USART_0_write(sdbyte);
    while (USART_0_is_tx_busy()) {
    }
#endif
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
            i++;
        }
    }
}
