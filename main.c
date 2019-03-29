// Include files
#include "uart.h"
#include "sysreg.h"
#include "gpio.h"
#include "irq.h"

// Declare a global int that represents the current state (1 or 2)
unsigned int state;	//Create a variable that will store the system state

//Funciton Prototypes are below

//LED 1 on pin 17
void init_GPIO17_to_output();
void set_GPIO17();
void clear_GPIO17();

//LED 2 on pin 27
void init_GPIO27_to_output();
void set_GPIO27();
void clear_GPIO27();

//LED 3 on pin 22
void init_GPIO22_to_output();
void set_GPIO22();
void clear_GPIO22();

//Switch A (pulled high)
void init_GPIO23_to_fallingEdgeInterrupt();

//Switch B (pulled low)
void init_GPIO24_to_risingEdgeInterrupt();


//The main function for the program
//It cycles through the LED outputs based on the current state of the machine
//The GPIO inputs change the state of the machine to change the cycle of LED's
void main() {

// Initializes UART protocols
	uart_init();

//Initialize output on pin 17
	init_GPIO17_to_output();

//Initialize output on pin 27
	init_GPIO27_to_output();

//Initialize output on pin 22
	init_GPIO22_to_output();

//Initialize a falling edge interrupt on pin 23
	init_GPIO23_to_fallingEdgeInterrupt();

//Initialize a rising edge interrupt on pin 23
	init_GPIO24_to_risingEdgeInterrupt();

//Enables IRQ interrupts, defined in sysreg
	enableIRQ();

	state = 1;	//Initialize the state to 1

	register unsigned int r;	//declare a register int that the busy loops will use

	while (1){	//Loop forever

		if (state == 1){
			set_GPIO17();	//Set A
            r = 2000000;
            while (r--) {
                asm volatile("nop");
            }

			clear_GPIO17();	//Clear A
			set_GPIO27();	//Set B
            r = 2000000;
            while (r--) {
                asm volatile("nop");
            }

			clear_GPIO27();	//Clear B
			set_GPIO22();	//Set C
            r = 2000000;
            while (r--) {
                asm volatile("nop");
            }

			clear_GPIO22();	//Clear C
		}

		else if (state == 2){
			set_GPIO22();	//Set C
            r = 1000000;
            while (r--) {
                asm volatile("nop");
            }

			clear_GPIO22();	//Clear C
			set_GPIO27();	//Set B
            r = 1000000;
            while (r--) {
                asm volatile("nop");
            }

			clear_GPIO27();	//Clear B
			set_GPIO17();	//Set A
            r = 1000000;
            while (r--) {
                asm volatile("nop");
            }

			clear_GPIO17();	//Clear A
		}

	}//End of while (should never leave this loop)
}//End of main


void init_GPIO17_to_output()
{
    register unsigned int r;

    // Get the current contents of the GPIO Function Select Register 1
    r = *GPFSEL1;

    // Clear bits 21 - 23. This is the field FSEL23, which maps to GPIO pin 17.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
    r &= ~(0x7 << (3*7));

    // Set the field FSEL23 to 001, which sets pin 17 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
    r |= (0x1 << (3*7));

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 1
    *GPFSEL1 = r;

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    r = 150;
    while (r--) {
      asm volatile("nop");
    }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 17 to
    // clock in the control signal for GPIO pin 17. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 17);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    r = 150;
    while (r--) {
      asm volatile("nop");
    }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;
}

void set_GPIO17()
{
	  register unsigned int r;

	  // Put a 1 into the SET17 field of the GPIO Pin Output Set Register 0
	  r = (0x1 << 17);
	  *GPSET0 = r;
}

void clear_GPIO17()
{
	  register unsigned int r;

	  // Put a 1 into the CLR17 field of the GPIO Pin Output Clear Register 0
	  r = (0x1 << 17);
	  *GPCLR0 = r;
}

void init_GPIO27_to_output()
{
    register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 2
    r = *GPFSEL2;

    // Clear bits 21 - 23. This is the field FSEL23, which maps to GPIO pin 27.
    // We clear the bits by ANDing with a 000 bit pattern in the field.
    r &= ~(0x7 << (3*7));

    // Set the field FSEL23 to 001, which sets pin 27 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
    r |= (0x1 << (3*7));

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
    *GPFSEL2 = r;

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    r = 150;
    while (r--) {
      asm volatile("nop");
    }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 27 to
    // clock in the control signal for GPIO pin 27. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 27);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    r = 150;
    while (r--) {
      asm volatile("nop");
    }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;
}

void set_GPIO27()
{
	  register unsigned int r;

	  // Put a 1 into the SET27 field of the GPIO Pin Output Set Register 0
	  r = (0x1 << 27);
	  *GPSET0 = r;
}

void clear_GPIO27()
{
	  register unsigned int r;

	  // Put a 1 into the CLR27 field of the GPIO Pin Output Clear Register 0
	  r = (0x1 << 27);
	  *GPCLR0 = r;
}

void init_GPIO22_to_output()
{
    register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 2
    r = *GPFSEL2;

    // We clear the bits 6-8 by ANDing with a 000 bit pattern in the field.
    r &= ~(0x7 << (3*2));

    // Set the field FSEL23 to 001, which sets pin 22 to an output pin.
    // We do so by ORing the bit pattern 001 into the field.
    r |= (0x1 << (3*2));

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 2
    *GPFSEL2 = r;

    // Disable pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    r = 150;
    while (r--) {
      asm volatile("nop");
    }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 22 to
    // clock in the control signal for GPIO pin 22. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 22);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    r = 150;
    while (r--) {
      asm volatile("nop");
    }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;
}

void set_GPIO22()
{
	  register unsigned int r;

	  // Put a 1 into the SET17 field of the GPIO Pin Output Set Register 0
	  r = (0x1 << 22);
	  *GPSET0 = r;
}

void clear_GPIO22()
{
	  register unsigned int r;

	  // Put a 1 into the CLR24 field of the GPIO Pin Output Clear Register 0
	  r = (0x1 << 22);
	  *GPCLR0 = r;
}

void init_GPIO23_to_fallingEdgeInterrupt()
{
    register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 1
    r = *GPFSEL2;

    // Clear bits 9 - 11. This is the field FSEL17, which maps to GPIO pin 23.
    // We clear the bits by ANDing with a 000 bit pattern in the field. This
    // sets the pin to be an input pin
    r &= ~(0x7 << (3*3));

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 1
    *GPFSEL1 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 17. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. We
    // will pull down the pin using an external resistor connected to ground.

    // Disable internal pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    r = 150;
    while (r--) {
        asm volatile("nop");
    }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 17 to
    // clock in the control signal for GPIO pin 17. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 23);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    r = 150;
    while (r--) {
        asm volatile("nop");
    }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;

    // Set pin 23 to so that it generates an interrupt on a falling edge.
    // We do so by setting bit 23 in the GPIO Rising Edge Detect Enable
    // Register 0 to a 1 value (p. 97 in the Broadcom manual).
    *GPFEN0 = (0x1 << 23);

    // Enable the GPIO IRQS for ALL the GPIO pins by setting IRQ 52
    // GPIO_int[3] in the Interrupt Enable Register 2 to a 1 value.
    // See p. 117 in the Broadcom Peripherals Manual.
    *IRQ_ENABLE_IRQS_2 = (0x1 << 20);
}

void init_GPIO24_to_risingEdgeInterrupt()
{
    register unsigned int r;


    // Get the current contents of the GPIO Function Select Register 1
    r = *GPFSEL2;

    // Clear bits 12 - 14. This is the field FSEL24, which maps to GPIO pin 24.
    // We clear the bits by ANDing with a 000 bit pattern in the field. This
    // sets the pin to be an input pin
    r &= ~(0x7 << (3*4));

    // Write the modified bit pattern back to the
    // GPIO Function Select Register 1
    *GPFSEL1 = r;

    // Disable the pull-up/pull-down control line for GPIO pin 17. We follow the
    // procedure outlined on page 101 of the BCM2837 ARM Peripherals manual. We
    // will pull down the pin using an external resistor connected to ground.

    // Disable internal pull-up/pull-down by setting bits 0:1
    // to 00 in the GPIO Pull-Up/Down Register
    *GPPUD = 0x0;

    // Wait 150 cycles to provide the required set-up time
    // for the control signal
    r = 150;
    while (r--) {
        asm volatile("nop");
    }

    // Write to the GPIO Pull-Up/Down Clock Register 0, using a 1 on bit 24 to
    // clock in the control signal for GPIO pin 24. Note that all other pins
    // will retain their previous state.
    *GPPUDCLK0 = (0x1 << 24);

    // Wait 150 cycles to provide the required hold time
    // for the control signal
    r = 150;
    while (r--) {
        asm volatile("nop");
    }

    // Clear all bits in the GPIO Pull-Up/Down Clock Register 0
    // in order to remove the clock
    *GPPUDCLK0 = 0;

    // Set pin 24 to so that it generates an interrupt on a rising edge.
    // We do so by setting bit 24 in the GPIO Rising Edge Detect Enable
    // Register 0 to a 1 value (p. 97 in the Broadcom manual).
    *GPREN0 = (0x1 << 24);

    // Enable the GPIO IRQS for ALL the GPIO pins by setting IRQ 52
    // GPIO_int[3] in the Interrupt Enable Register 2 to a 1 value.
    // See p. 117 in the Broadcom Peripherals Manual.
    *IRQ_ENABLE_IRQS_2 = (0x1 << 20);
}
