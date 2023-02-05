#include "my_printf.h"
#include "port.h"
#include <atmel_start.h>
#include <util/delay.h>

int main(void) {
    /* Initializes MCU, drivers and middleware */
    atmel_start_init();
    // Arduino
    int i = 0;
    bool level = false;
    PORT_set_pin_dir(D13_PORT, D13_PIN, PORT_DIR_OUT);
	PORT_set_pin_pull_mode(D13_PORT, D13_PIN, PORT_PULL_UP);
    PORT_set_pin_level(D13_PORT, D13_PIN, level);
	while (1) {
		i++;
        level = ((i % 2) == 0);
        PORT_set_pin_level(D13_PORT, D13_PIN, level);
        my_printf("Run #%d\n", i);
        _delay_ms(1000);
    }
}
