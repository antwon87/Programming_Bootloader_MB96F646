# Programming_Bootloader_MB96F646
This bootloader is to be uploaded into the RAM of the MB96F646 microcontroller using the Serial Communication Mode. Once running, the bootloader communicates with a programmer hardware device via UART. The bootloader receives commands to perform operations on the flash memory such as erase, program, read, or blank check. After receiving a command, the bootloader performs the appropriate operation and then reports success or failure.

I started with a general template project found on the Cypress website and adapted it to run in RAM rather than flash to fit my application.
