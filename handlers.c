// This file contains C functions to handle particular kinds of exceptions.
// Only a function to handle IRQ exceptions is currently implemented.

// Header files
#include "uart.h"
#include "gpio.h"
#include "irq.h"
#include "sysreg.h"

// Reference to the global shared value that keeps track of the state the system is in (1 or 2)
extern unsigned int state;

////////////////////////////////////////////////////////////////////////////////
//
//  Function:       IRQ_handler
//
//  Arguments:      none
//
//  Returns:        void
//
//  Description:    This function first prints out some basic information about
//                  the state of the interrupt controller, GPIO pending
//                  interrupts, and selected system registers. It then
//                  determines the particular kind of pending interrupt. The
//                  interrupt is cleared, and interrupt is handled by changing
//                  the state of the machine.
//
////////////////////////////////////////////////////////////////////////////////

void IRQ_handler()
{

    // Handle GPIO interrupts in general
    if (*IRQ_PENDING_2 == (0x1 << 20)) {

      // Handle the interrupt associated with GPIO pin 23 (SWITCH A)
      if (*GPEDS0 == (0x1 << 23)) {
	// Clear the interrupt by writing a 1 to the GPIO Event Detect
	// Status Register at bit 23
	*GPEDS0 = (0x1 << 23);

	// Handle the interrupt by setting the state to 2
	state = 2;
      }

      // Handle the interrupt associated with GPIO pin 24 (SWITCH B)
      if (*GPEDS0 == (0x1 << 24)) {
	// Clear the interrupt by writing a 1 to the GPIO Event Detect
	// Status Register at bit 24
	*GPEDS0 = (0x1 << 24);

	// Handle the interrupt by setting the state to 1
	state = 1;
      }
    }
    // Return to the IRQ exception handler stub
    return;
}
