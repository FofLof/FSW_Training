#include <globals.h>

#include <LED/led.h>
#include <Buttons/buttons.h>
#include <print_scan.h>
#include "gpio_.h"
#include <Timers/timers.h>

void branch_main() {
	// space for initializations
	printer_init();
	bool currentState = false;
	uint64_t initTime = getSysTime();
	uint64_t changeInTime = 0;
	int pin = 8;
	GPIO_TypeDef* port = GPIOB;
	gpio_configureMode(port, pin, GPIO_DIGITAL_OUT, -1, -1, -1);
//	gpio_set(GPIOE, pin, GPIO_LOW);


	// infinite loop
	while (1) {

		changeInTime = getSysTime() - initTime;

		if (changeInTime > 10) {
			changeInTime = 0;
			initTime = getSysTime();
			currentState = !currentState;
			gpio_set(port, pin, currentState);
		}

	}

	// NOTE
	// Always keep the system in the infinite while loop. Never break out of it
	// There is no place for the computer to go once you break out of this loop
}
