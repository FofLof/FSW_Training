#include <globals.h>

#include <LED/led.h>
#include <Buttons/buttons.h>
#include <print_scan.h>

void branch_main() {
	// space for initializations
	buttons_init();
	printer_init();
	led_init();
	uint64_t initTime = getSysTime();
	uint64_t changeInTime = 0;
	bool currentState = false;
	led_d1(currentState);

	// infinite loop
	while (1) {
		changeInTime = getSysTime() - initTime;

		if (get_buttonStatus_0()) {
			printMsg("Button 0 ON\r\n");
		}

		if (get_buttonStatus_1()) {
			printMsg("Button 1 ON\r\n");
		}

		if (changeInTime > 1000) {
			changeInTime = 0;
			currentState = !currentState;
			led_d1(currentState);

		}


	}

	// NOTE
	// Always keep the system in the infinite while loop. Never break out of it
	// There is no place for the computer to go once you break out of this loop
}
