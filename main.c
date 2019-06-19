/* CheckSum LLC
*  Programmer: Anthony Fisher
*  Date: 4/22/2019
*
*  Bootloader for Cypress MB96600 series processors. Written specifically for MB96F646RB,
*  but will ideally work for the whole MB96600 family. The bootloader communicates on UART0.
*  Modifications would need to be made to use other UART ports.
*/

#include "_ffmc16.h"
#include "main.h"

// Main entry function executed after start.asm.
void main(void)
{
	__LWORD i;
	__BYTE status;
    __BYTE rxByte;
	__LWORD addr;
	__LWORD bytes;

	bootParams = (bootloaderParams*) BOOTLOADER_ADDR;  // This is the address where the params struct is being written to.
    
	// Set up clock to run at 48MHz if an external oscillator is present.
	// Otherwise, the clock will stay with the internal 2MHz RC oscillator
	if (bootParams->exOscMHz != 0) {
		CKSSR = bootParams->ckssr;
		PLLCR = bootParams->pllcr;
		CKFCR = bootParams->ckfcr;
		CKSR = 0xFA;
		while (CKMR_PCM != 1);
	}
	
	// Set 2-cycle flash read/write. Using a 1-cycle read/write causes incorrect reads when
	//   reading many values sequentially.
	DFCA_TMG = 1;
    
	InitUART0();
    
	// Send a byte to indicate that the bootloader has initialized.
	TX_Byte(OK);

    // Endless loop
    while(1)
    {
		// Wait until a command is received, then process it.
    	if (UART0_SSR0_RDRF == 1) {
			switch (UART0_RDR0) {
				case BLANK_CHECK:
					// Receive address at which to blank check.
					addr = RX_Byte();
					addr |= ((__LWORD) RX_Byte()) << 8;
					addr |= ((__LWORD) RX_Byte()) << 16;
					
					// Receive number of bytes to blank check.
					bytes = RX_Byte();
					bytes |= ((__LWORD) RX_Byte()) << 8;
					bytes |= ((__LWORD) RX_Byte()) << 16;
					
					// Wait for the checksum byte before responding.
					RX_Byte();
					TX_Byte(COMMAND_RECEIVED);
					
					// Do a blank check and report success or failure.
					if (BlankCheck((volatile __far __WORD *) addr, bytes)) {
						TX_Byte(FAILURE);
					} else {
						TX_Byte(OK);
					}	
					break;
				case CHIP_ERASE:
					// Wait for the checksum byte before responding.
					RX_Byte();
					TX_Byte(COMMAND_RECEIVED);
					
					// Erase the full chip and report success or failure.
					status = EraseChip();
					if (status == 2) {
						TX_Byte(FAILURE);
					} else if (status == 1) {
						TX_Byte(TIMEOUT);
					} else {
						TX_Byte(OK);
					}
					break;
				case READ:
					// Receive address from which to read.
					addr = RX_Byte();
					addr |= ((__LWORD) RX_Byte()) << 8;
					addr |= ((__LWORD) RX_Byte()) << 16;
					
					// Receive number of bytes to read.
					bytes = RX_Byte();
					bytes |= ((__LWORD) RX_Byte()) << 8;
					bytes |= ((__LWORD) RX_Byte()) << 16;
					
					// Wait for the checksum byte.
					RX_Byte();
					
					// Don't send a "command received" byte. Just start sending data.
					// Doing this because it was more convenient to interface with the MW algorithm.
					while (bytes > 0) {
						TX_Byte(*((volatile __far __BYTE *) addr));
						bytes--;
						addr++;
					}
					break;
				case SECTOR_ERASE:
					// Receive the 24-bit address, least-significant byte first.
					addr = RX_Byte();
					addr |= ((__LWORD) RX_Byte()) << 8;
					addr |= ((__LWORD) RX_Byte()) << 16;
					
					// Wait for the checksum byte before responding.
					RX_Byte();
					TX_Byte(COMMAND_RECEIVED);
					
					// Erase the sector containing address "addr" and report success or failure.
					status = EraseSector((__far volatile __BYTE *) addr);
					if (status == 2) {
						TX_Byte(FAILURE);
					} else if (status == 1) {
						TX_Byte(TIMEOUT);
					} else {
						TX_Byte(OK);
					}
					break;
				case WRITE:					
					// Receive address to which to write.
					addr = RX_Byte();
					addr |= ((__LWORD) RX_Byte()) << 8;
					addr |= ((__LWORD) RX_Byte()) << 16;
					
					// Receive number of bytes to write.
					bytes = RX_Byte();
					bytes |= ((__LWORD) RX_Byte()) << 8;
					bytes |= ((__LWORD) RX_Byte()) << 16;
					
					// Wait for the checksum byte before responding. Send command received within write function.
					RX_Byte();
					
					// If we have been asked to write more data than we can buffer, send a response and do nothing.
					if (bytes > DATA_BUFFER_SIZE) {
						TX_Byte(BUFFER_OVERFLOW);
						continue;
					} else {  // Otherwise indicate reception, and ready to receive data.
						TX_Byte(COMMAND_RECEIVED);
					}
					
					// Receive the data and store it in data buffer.
					for (i = 0; i < bytes; ++i) {
						*(dataBuf +i) = RX_Byte();
					}
					
					// Write the data and report success or failure.
					if (WriteFlash((__far volatile __BYTE *) addr, bytes)) {
						TX_Byte(FAILURE);
					} else {
						TX_Byte(OK);
					}
					
					break;
				default:
					TX_Byte(UNKNOWN_COMMAND);
			}
    	}		
    }
}

// Blank check "size" number of bytes starting at address "addr".
// Return 0 if all bytes read 0xFF, 1 otherwise.
__BYTE BlankCheck(volatile __far __WORD * addr, long size) {
	__BYTE status;
	__WORD read;
	__LWORD i;
	status = 0;
	read = 0;
	
	while (size > 0) {
		if (*addr != 0xFFFF) {
			status = 1;
			break;
		}
		addr++;
		size -= 2;
	}
	
	return status;
}

// Perform a chip erase command using the Flash Memory Automatic Algorithm.
// Returns 0 on success, 1 on failure.
// See chapter 29 of the MB96600 Hardware Manual Rev *A.
__BYTE EraseChip(void) {
	__BYTE status;
	__LWORD i;
	
	// Enable writes to flash.
	DFWC0A = 0x1F;
	DFWC1A = 0xFF;
	DFCA_WE = 1;
	
	status = 0;
	
	// Perform the sequence of flash writes that starts the Erase Chip Automatic Algorithm.
	// See section 29.4 of the MB96600 Hardware Manual Rev *A.
	*addrAAA = 0xAA;
	*addr554 = 0x55;
	*addrAAA = 0x80;
	*addrAAA = 0xAA;
	*addr554 = 0x55;
	*addrAAA = 0x10;	
	
	// If a chip erase didn't start, bail out.
	if (DFSA_CERS == 0) return 2;
	
	// Wait until the erase operation is complete or has timed out.
	status = PollEraseComplete(addrAAA);
	
	DFCA_WE = 0;  // Disable writes to flash.
	
	return status;	
}

// Perform a sector erase command using the Flash Memory Automatic Algorithm.
// "sectorAddr" is any address within the sector to be erased.
// Returns 0 on success, non-zero on failure.
// See chapter 29 of the MB96600 Hardware Manual Rev *A.
__BYTE EraseSector(__far volatile __BYTE * const sectorAddr) {
	__BYTE status;
	__LWORD i;
	
	// Enable writes to flash.
	DFWC0A = 0x1F;
	DFWC1A = 0xFF;
	DFCA_WE = 1;
	
	status = 0;
	
	// Perform the sequence of flash writes that starts the Erase Sector Automatic Algorithm.
	// See section 29.4 of the MB96600 Hardware Manual Rev *A.
	*addrAAA = 0xAA;
	*addr554 = 0x55;
	*addrAAA = 0x80;
	*addrAAA = 0xAA;
	*addr554 = 0x55;
	*sectorAddr = 0x30;
	
	// If a sector erase didn't start, bail out.
	if (DFSA_SERS == 0)	return 2;
	
	// Wait until the erase operation is complete or has timed out.
	PollEraseComplete(sectorAddr);
	
	DFCA_WE = 0;  // Disable writes to flash.
	
	return status;	
}

// Initialize UART0.
void InitUART0(void) {
	// See MB96600 Hardware Manual Chapter 19 for UART info
    
    // Set up SIN0 pin
    DDR13_D4 = 0;  			// Set SIN0 pin to input
    PIER13_IE4 = 1;  		// Enable SIN0 input
    PUCR13_PU4 = 0;			// Disable SIN0 pull-up resistor
    PDR13_P4 = 0;			// Disable SIN0 pull-down resistor
    
    // Set up SOT0 pin
    DDR13_D5 = 1;			// May need to set it as output with the DDR register as well?
    UART0_SMR0_SOE = 1;  	// Set SOT0 as output
    PUCR13_PU5 = 1;			// Set pull-up on SOT0
    
    // UART config
    UART0_SCR0_PEN = 0;		// No parity bit
    //UART0_SCR0_P = 0;		// Even parity, unused
    UART0_SCR0_SBL = 0;		// 1 stop bit
    UART0_SCR0_CL = 1;		// 8 data bits
    
    UART0_SSR0_BDS = 0;		// LSB first
    UART0_SSR0_RIE = 1;		// Receive interrupt enabled
    UART0_SSR0_TIE = 0;		// No transmission interrupt
    UART0_SMR0_MD = 0;  	// Set UART to mode 0 (asynchronous normal)
    UART0_SMR0_OTO = 0;		// Use ext. clock (SCK) with Baud Rate Generator). I don't have a clock, but the data sheet says to set this to 0 anyway.
    UART0_SMR0_SCKE = 0;	// Serial clock output pin disabled
    UART0_SMR0_EXT = 0;		// Use internal Baud Rate Generator (Reload Counter)
    UART0_ESCR0_CCO = 0;	// Continuous Clock Output disabled
    UART0_ESCR0_SCES = 0;	// Sampling on rising clock edge
    UART0_ECCR0_INV = 0;	// Data is not inverted
    UART0_ECCR0_LBR = 0;	// No LIN synch break
    UART0_ECCR0_BIE = 0;	// Disable bus idle interrupt
    UART0_BGR0 = bootParams->bgr;
    // EFER0_BRGR = 1;  // For debug, allows reading the value written to UART0_BGR0 rather than the current counter value.
    
    // Enable UART for reception and transmission of data
    UART0_SMR0_UPCL = 1;  	// Reset UART
    UART0_SCR0_TXE = 1;		// Enable transmission
    UART0_SCR0_RXE = 1;		// Enable reception
}

// Poll the DFSA register and Hardware Sequence Flags to determine when the erase operation finishes of times out.
// "addr" is an address in the memory range being erased.
__BYTE PollEraseComplete(__far volatile __BYTE * const addr) {
	// __LWORD i;
	__BYTE status;
	__BYTE read1;
	__BYTE read2;
	status = 0;
	
	// Read addr to check the Hardware Sequence Flags.
	// Waiting for the toggle bit to stop toggling, or the timeout bit to be set and toggle still toggling.
	// See Figure 29-4 in section 29.6.5 of the MB96600 Hardware Manual Rev *A.
	while(1) {
		// 10ms delay, for debug.
		// for (i = 0; i < 28000; ++i) __wait_nop();
		
		read1 = *addrAAA & 0xFF;
		read2 = *addrAAA & 0xFF;
		
		// TX_Byte(read1);  // DEBUG
		// TX_Byte(read2);  // DEBUG
		// TX_Byte(DFSA);   // DEBUG
		
		// If toggle bit didn't toggle, and DFSA shows not currently erasing sector or chip, and not hung
		if (((read1 & 0x40) == (read2 & 0x40)) && ((DFSA & 0x16) == 0x00)) {  
			// Operation completed successfully.
			// The manual shows an extra check here against a "timeout marker", but I don't know what it is referring to.
			// TX_Byte(DFSA);  // DEBUG
			break;
		}
		
		if ((read2 & 0x20) == 0x20) {
			// Operation is still active, but timeout bit is set. Check toggle bit again.
			read1 = *addrAAA & 0xFF;
			read2 = *addrAAA & 0xFF;
			
			if (((read1 & 0x40) != (read2 & 0x40)) || (DFSA_HANG == 1)) {
				// If still toggling, or the DFSA says it is hung, timeout error.
				status = 1;
			}
			
			// Sometimes on sector erase when the flash is protected, the reads will return as
			//	 0xFF every time, even if the sector really is being erased. So, check the DFSA
			//   bits to see if an erase is still in progress.
			if ((DFSA & 0x14) == 0x00) {
				break;
			}
		}
	}
	
	return status;
}

// Receive one byte on UART0.
__BYTE RX_Byte(void) {
	while(UART0_SSR0_RDRF == 0);
	return UART0_RDR0;
}

// Transmit one byte on UART0.
void TX_Byte(__BYTE txByte) {
	while (UART0_SSR0_TDRE != 1U);
	UART0_TDR0 = txByte;
}

// Write "bytes" number of bytes to the flash memory starting at address "addr".
// Data is written as bytes using the Write Command Sequencer.
// Returns 0 on success, non-zero on failure.
// See section 29.6.3 of the MB96600 Hardware Manual Rev *A.
__BYTE WriteFlash(__far volatile __BYTE * addr, __LWORD bytes) {
	__BYTE status;
	__BYTE * data;
	status = 0;
	data = dataBuf;
	
	// Enable writing to flash and Write Command Sequencer
	DFWC0A = 0x1F;
	DFWC1A = 0xFF;
	DFCA_WE = 1;
	DFCA_CSWE = 1;
	
	while (bytes > 0) {
		// Wait for Write Command Sequencer to be in the idle state.
		while (DFSA_ST != 0);
		// Write the data.
		*addr = *data;
		addr++;
		data++;
		bytes -= 1;
	}
	
	// Disable writing to flash and Write Command Sequencer
	DFCA_WE = 0;
	DFCA_CSWE = 0;
	
	return status;
}

// Reference code. In case we ever want to use timers or interrupts.
	
	// Cascaded TIMER example. About 87ms max for each timer at 48MHz CLKP1
	// TMRLR1 = 0x8000;
	// TMISR_TMIS1 = 1;  // Set TMR1 to trigger when TMR0 underflows. Cascading timers for longer timeout.
	// TMCSR1 = 0x0882;  // Set up TMR1 for maximum CLKP1 division, event trigger
	// TMRLR0 = 0xFFFF;  // Load value to count down from
	// TMCSR0 = 0x0803;  // Start counter in one-shot mode, dividing CLKP1 as much as possible
	// // while(TMR1 != 0xFFFF);  // Check to see that the timer has underflowed by value in TMR.
	// while (TMCSR1_UF == 0);    // Check to see that the timer has underflowed by underflow flag.
	// TMCSR0_UF = 0;  // Reset UF flags.
	// TMCSR1_UF = 0;	
    
    // Allow all interrupt levels
    // __set_il(7);
    
    // Enable UART0 interrupt vector by setting the interrupt level less than 7.
    // ICR_IX = 101;
    // ICR_IL = 0;
	
    // Enable interrupts
    // __EI();