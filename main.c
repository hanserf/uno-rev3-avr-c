#include <atmel_start.h>
#include <util/delay.h>
#include "port.h"
#include "my_printf.h"
#define LED_PIN (5)



int main(void)
{
	/* Initializes MCU, drivers and middleware */
	atmel_start_init();
	// Arduino 
	PORTB_set_pin_dir(LED_PIN, PORT_DIR_OUT);
	PORTB_set_pin_pull_mode(LED_PIN,PORT_PULL_UP);
	PORTB_set_pin_level(LED_PIN,false);
	/* Replace with your application code */
	int i = 0;
	while (1) {
		my_printf("Run #%d\n",i);
		_delay_ms(1000);
		PORTB_toggle_pin_level(LED_PIN);
		i++;
	}
}
