#include "gpio_.h"

void gpio_low(GPIO_TypeDef *port, int pin) {
	/*
	 * Use bitwise operations on registers in the GPIO `port`
	 * to turn a pin's value low.
	 * Hint: BSRR
	 */

	//BRO is reset pin for pin 0, add with pin to shift needed number of times to reach desired pin on the
	// 32 bit BSRR register, Reset pins start at 16
	//Do bitwise or to retain the values of BSRR previous for example if it started as
	// 0000 0000 0010 0000 doing bitwise or with 0000 0010 0000 0000 results in 0000 0010 0010 0000
	port->BSRR &= ~(0x1UL << pin); //NOT will make all 1 except place we want to invert and AND will retain values only change desired bit
	port->BSRR |= 0x1UL << (pin + GPIO_BSRR_BR0_Pos);


}

void gpio_high(GPIO_TypeDef *port, int pin) {
	/*
	 * same as gpio_low, but turns the value high
	 */

	//Same explanation as gpio_low but BS0 (set register) starts at 0 so think of this as adding GPIO_BSRR_BSO_POS
	port->BSRR |= 0x1UL << pin;
	port->BSRR &= ~(0x1UL << pin + GPIO_BSRR_BR0_Pos); //Sets corresponding BRx pin to LOW
}

void gpio_set(GPIO_TypeDef *port, int pin, bool value) {
	/*
	 * A generalized function that uses gpio_high() or gpio_low()
	 * depending on whether `value` is HIGH or LOW
	 */
	if (value) {
		gpio_high(port, pin);
	} else {
		gpio_low(port, pin);
	}

}

void gpio_configureMode(GPIO_TypeDef * port, int pin, int mode, int open_drain, int speed, int pull) {
	/*
	 * This will require setting a few registers
	 * See if you can identify which registers, and why.
	 * The process is the same though, bitwise operations on the registers
	 */

	if (mode >= GPIO_DIGITAL_IN && mode <= GPIO_ANALOG_IN) {
		port->MODER |= mode << pin * 2;
	} else if (mode == -1) {

	} else {
		printMsg("Invalid GPIO mode\r\n");
	}


	if (open_drain == GPIO_PUSH_PULL || open_drain == GPIO_OPEN_DRAIN) {
		port->OTYPER |= open_drain << pin;
	} else if (open_drain == -1) {

	} else {
		printMsg("Invalid GPIO Open_drain option\r\n");
	}



	if (speed >= GPIO_LOW_SPEED && speed <= GPIO_VERY_HI_SPEED) {
		port->OSPEEDR |= speed << pin * 2;
	} else if (speed == -1) {

	} else {
		printMsg("Invalid GPIO speed\r\n");
	}


	if (pull >= GPIO_NO_PULL && pull <= GPIO_PULL_DOWN) {
		port->PUPDR |= pull << pin * 2;
	} else if (pull == -1) {

	} else {
		printMsg("Invalid GPIO pull\r\n");
	}




}

void gpio_alternateFunction(GPIO_TypeDef * port, uint8_t pin, uint8_t afn) {
	/*
	 * Use the gpio_configureMode to get GPIO to Alternate Function.
	 * Then set the Alternate Function registers to the right alternate function
	 */
	gpio_configureMode(port, pin, GPIO_AF, -1, -1, -1);

	if (pin >= 0 && pin <= 7) {
	 	port->AFR[0] |= afn << pin * 4;
	} else if (pin >= 8 && pin <= 15){
		port->AFR[1] |= afn << pin * 4;
	}

}
