#include <globals.h>

#include <LED/led.h>
#include <Buttons/buttons.h>
#include <print_scan.h>
#include "gpio_.h"

void branch_main() {
	// space for initializations
	GPIO_TypeDef* port;
	int pin = 1;
	gpio_configureMode(port, pin, GPIO_DIGITAL_OUT, GPIO_PULL_DOWN, GPIO_MED_SPEED, GPIO_PUSH_PULL);

	// infinite loop
	while (1) {
		gpio_set(port, pin, GPIO_HIGH);
		delay_ms(10);
		gpio_set(port, pin, GPIO_LOW);
		delay_ms(10);

	}

	// NOTE
	// Always keep the system in the infinite while loop. Never break out of it
	// There is no place for the computer to go once you break out of this loop
}
