#ifndef MB96600_MAIN_H
#define MB96699_MAIN_H

#define BOOTLOADER_ADDR		0x7200		// Address for bootloader parameters

// Commands coming from MW
#define BLANK_CHECK			0x36
#define CHIP_ERASE			0x25
#define READ				0xC4
#define SECTOR_ERASE		0x2F
#define WRITE				0xA0

// Responses to send to MW
#define BUFFER_OVERFLOW		0x18
#define COMMAND_RECEIVED	0x6A
#define FAILURE				0x17
#define OK					0x69
#define READY				0xF5
#define TIMEOUT				0x0F
#define UNKNOWN_COMMAND		0x72

// Place the data buffer at the last 1024 bytes in RAM. Address and buffer size may need to change
//   if a new part has smaller RAM.
// RAM addresses found in the MB96600 Hardware Manual and device-specific datasheets.
#define DATA_BUFFER_SIZE	1024		// Size of the data buffer in RAM
__BYTE * const dataBuf = (__BYTE * const) 0x7C00;

// Struct containing parameters set by MW.
typedef struct {
	__BYTE exOscMHz;  	// External oscillator frequency in MHz
	__BYTE ckssr;  		// Value to place in CKSSR register
	__WORD pllcr;		// Value to place in PLLCR register
	__WORD ckfcr;		// Value to place in CKFCR register
	__WORD bgr;			// Value to place in BGR register
	__LWORD unused1;	// Unused space, available for future use
	__LWORD unused2;	// Unused space, available for future use	
} bootloaderParams;
bootloaderParams const * bootParams;  // Global pointer to parameter struct. Defined in main().

// Addresses used to start the Flash Memory Automatic Algorithm when erasing.
__far volatile __BYTE * const addrAAA = (__far volatile __BYTE * const) 0xDF0AAA;
__far volatile __BYTE * const addr554 = (__far volatile __BYTE * const) 0xDF0554;

// Function declarations.
__BYTE BlankCheck(volatile __far __WORD * addr, long size);
__BYTE EraseChip(void);
__BYTE EraseSector(__far volatile __BYTE * const sectorAddr);
void InitUART0(void);
__BYTE PollEraseComplete(__far volatile __BYTE * const addr);
__BYTE RX_Byte(void);
void TX_Byte(__BYTE txByte);
__BYTE WriteFlash(__far volatile __BYTE * addr, __LWORD bytes);

#endif // MB96600_MAIN_H
