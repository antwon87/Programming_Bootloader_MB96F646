/*****************************************************************************/
/*  F2MC-16FX Family Template Project V01L01                                 */
/*****************************************************************************/
/*******************************************************************************
* Copyright (C) 2013 Spansion LLC. All Rights Reserved. 
*
* This software is owned and published by: 
* Spansion LLC, 915 DeGuigne Dr. Sunnyvale, CA  94088-3453 ("Spansion").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND 
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with Spansion 
* components. This software is licensed by Spansion to be adapted only 
* for use in systems utilizing Spansion components. Spansion shall not be 
* responsible for misuse or illegal use of this software for devices not 
* supported herein.  Spansion is providing this software "AS IS" and will 
* not be responsible for issues arising from incorrect user implementation 
* of the software.  
*
* SPANSION MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS), 
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING, 
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED 
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED 
* WARRANTY OF NONINFRINGEMENT.  
* SPANSION SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT, 
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT 
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION, 
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR 
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT, 
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA, 
* SAVINGS OR PROFITS, 
* EVEN IF SPANSION HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES. 
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED 
* FROM, THE SOFTWARE.  
*
* This software may be replicated in part or whole for the licensed use, 
* with the restriction that this Disclaimer and Copyright notice must be 
* included with each copy of this software, whether used in part or whole, 
* at all times.  
*/

/*----------------------------------------------------------------------------
  VECTORS.C
  - Interrupt vector definition
-----------------------------------------------------------------------------*/
#include "_ffmc16.h"

/*---------------------------------------------------------------------------
   Prototypes
   Add your own prototypes here. Each vector definition needs is proto-
   type. Either do it here or include a header file containing them.
-----------------------------------------------------------------------------*/

__interrupt void Vectors_Isr_DefaultHandler (void);
__interrupt void UART0_RX_ISR (void);

// Interrupt vector definition
//
// Use the following statements to define the interrupt vector table
// i.e. add your interrupt handlers here (ensure to define the ISR prototype,
// e.g. by adding the appropriate header file above).
// All resource related vectors are predefined. Remaining software interrupts
// can be added here as well.

#pragma	intvect	Vectors_Isr_DefaultHandler 11	///< Non-Maskable Interrupt
#pragma	intvect	Vectors_Isr_DefaultHandler 12	///< Delayed Interrupt
#pragma	intvect	Vectors_Isr_DefaultHandler 13	///< RC Timer
#pragma	intvect	Vectors_Isr_DefaultHandler 14	///< Main Clock Timer
#pragma	intvect	Vectors_Isr_DefaultHandler 15	///< Sub Clock Timer
#pragma	intvect	Vectors_Isr_DefaultHandler 16	///< LVD-interrupt
#pragma	intvect	Vectors_Isr_DefaultHandler 17	///< External Interrupt 0
#pragma	intvect	Vectors_Isr_DefaultHandler 18	///< External Interrupt 1
#pragma	intvect	Vectors_Isr_DefaultHandler 19	///< External Interrupt 2
#pragma	intvect	Vectors_Isr_DefaultHandler 20	///< External Interrupt 3
#pragma	intvect	Vectors_Isr_DefaultHandler 21	///< External Interrupt 4
#pragma	intvect	Vectors_Isr_DefaultHandler 22	///< External Interrupt 5
#pragma	intvect	Vectors_Isr_DefaultHandler 23	///< External Interrupt 6
#pragma	intvect	Vectors_Isr_DefaultHandler 24	///< External Interrupt 7
#pragma	intvect	Vectors_Isr_DefaultHandler 25	///< External Interrupt 8
#pragma	intvect	Vectors_Isr_DefaultHandler 26	///< External Interrupt 9
#pragma	intvect	Vectors_Isr_DefaultHandler 27	///< External Interrupt 10
#pragma	intvect	Vectors_Isr_DefaultHandler 28	///< External Interrupt 11
#pragma	intvect	Vectors_Isr_DefaultHandler 29	///< External Interrupt 12
#pragma	intvect	Vectors_Isr_DefaultHandler 30	///< External Interrupt 13
#pragma	intvect	Vectors_Isr_DefaultHandler 31	///< External Interrupt 14
#pragma	intvect	Vectors_Isr_DefaultHandler 32	///< External Interrupt 15
#pragma	intvect	Vectors_Isr_DefaultHandler 33	///< CAN Controller 0
#pragma	intvect	Vectors_Isr_DefaultHandler 34	///< CAN Controller 1
#pragma	intvect	Vectors_Isr_DefaultHandler 35	///< CAN Controller 2
#pragma	intvect	Vectors_Isr_DefaultHandler 36	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 37	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 38	///< Programmable Pulse Generator 0
#pragma	intvect	Vectors_Isr_DefaultHandler 39	///< Programmable Pulse Generator 1
#pragma	intvect	Vectors_Isr_DefaultHandler 40	///< Programmable Pulse Generator 2
#pragma	intvect	Vectors_Isr_DefaultHandler 41	///< Programmable Pulse Generator 3
#pragma	intvect	Vectors_Isr_DefaultHandler 42	///< Programmable Pulse Generator 4
#pragma	intvect	Vectors_Isr_DefaultHandler 43	///< Programmable Pulse Generator 5
#pragma	intvect	Vectors_Isr_DefaultHandler 44	///< Programmable Pulse Generator 6
#pragma	intvect	Vectors_Isr_DefaultHandler 45	///< Programmable Pulse Generator 7
#pragma	intvect	Vectors_Isr_DefaultHandler 46	///< Programmable Pulse Generator 8
#pragma	intvect	Vectors_Isr_DefaultHandler 47	///< Programmable Pulse Generator 9
#pragma	intvect	Vectors_Isr_DefaultHandler 48	///< Programmable Pulse Generator 10
#pragma	intvect	Vectors_Isr_DefaultHandler 49	///< Programmable Pulse Generator 11
#pragma	intvect	Vectors_Isr_DefaultHandler 50	///< Programmable Pulse Generator 12
#pragma	intvect	Vectors_Isr_DefaultHandler 51	///< Programmable Pulse Generator 13
#pragma	intvect	Vectors_Isr_DefaultHandler 52	///< Programmable Pulse Generator 14
#pragma	intvect	Vectors_Isr_DefaultHandler 53	///< Programmable Pulse Generator 15
#pragma	intvect	Vectors_Isr_DefaultHandler 54	///< Programmable Pulse Generator 16
#pragma	intvect	Vectors_Isr_DefaultHandler 55	///< Programmable Pulse Generator 17
#pragma	intvect	Vectors_Isr_DefaultHandler 56	///< Programmable Pulse Generator 18
#pragma	intvect	Vectors_Isr_DefaultHandler 57	///< Programmable Pulse Generator 19
#pragma	intvect	Vectors_Isr_DefaultHandler 58	///< Reload Timer 0
#pragma	intvect	Vectors_Isr_DefaultHandler 59	///< Reload Timer 1
#pragma	intvect	Vectors_Isr_DefaultHandler 60	///< Reload Timer 2
#pragma	intvect	Vectors_Isr_DefaultHandler 61	///< Reload Timer 3
#pragma	intvect	Vectors_Isr_DefaultHandler 62	///< Reload Timer 4
#pragma	intvect	Vectors_Isr_DefaultHandler 63	///< Reload Timer 5
#pragma	intvect	Vectors_Isr_DefaultHandler 64	///< Reload Timer 6 - dedicated for PPG
#pragma	intvect	Vectors_Isr_DefaultHandler 65	///< Input Capture Unit 0
#pragma	intvect	Vectors_Isr_DefaultHandler 66	///< Input Capture Unit 1
#pragma	intvect	Vectors_Isr_DefaultHandler 67	///< Input Capture Unit 2
#pragma	intvect	Vectors_Isr_DefaultHandler 68	///< Input Capture Unit 3
#pragma	intvect	Vectors_Isr_DefaultHandler 69	///< Input Capture Unit 4
#pragma	intvect	Vectors_Isr_DefaultHandler 70	///< Input Capture Unit 5
#pragma	intvect	Vectors_Isr_DefaultHandler 71	///< Input Capture Unit 6
#pragma	intvect	Vectors_Isr_DefaultHandler 72	///< Input Capture Unit 7
#pragma	intvect	Vectors_Isr_DefaultHandler 73	///< Input Capture Unit 8
#pragma	intvect	Vectors_Isr_DefaultHandler 74	///< Input Capture Unit 9
#pragma	intvect	Vectors_Isr_DefaultHandler 75	///< Input Capture Unit 10
#pragma	intvect	Vectors_Isr_DefaultHandler 76	///< Input Capture Unit 11
#pragma	intvect	Vectors_Isr_DefaultHandler 77	///< Output Compare Unit 0
#pragma	intvect	Vectors_Isr_DefaultHandler 78	///< Output Compare Unit 1
#pragma	intvect	Vectors_Isr_DefaultHandler 79	///< Output Compare Unit 2
#pragma	intvect	Vectors_Isr_DefaultHandler 80	///< Output Compare Unit 3
#pragma	intvect	Vectors_Isr_DefaultHandler 81	///< Output Compare Unit 4
#pragma	intvect	Vectors_Isr_DefaultHandler 82	///< Output Compare Unit 5
#pragma	intvect	Vectors_Isr_DefaultHandler 83	///< Output Compare Unit 6
#pragma	intvect	Vectors_Isr_DefaultHandler 84	///< Output Compare Unit 7
#pragma	intvect	Vectors_Isr_DefaultHandler 85	///< Output Compare Unit 8
#pragma	intvect	Vectors_Isr_DefaultHandler 86	///< Output Compare Unit 9
#pragma	intvect	Vectors_Isr_DefaultHandler 87	///< Output Compare Unit 10
#pragma	intvect	Vectors_Isr_DefaultHandler 88	///< Output Compare Unit 11
#pragma	intvect	Vectors_Isr_DefaultHandler 89	///< Free Running Timer 0
#pragma	intvect	Vectors_Isr_DefaultHandler 90	///< Free Running Timer 1
#pragma	intvect	Vectors_Isr_DefaultHandler 91	///< Free Running Timer 2
#pragma	intvect	Vectors_Isr_DefaultHandler 92	///< Free Running Timer 3
#pragma	intvect	Vectors_Isr_DefaultHandler 93	///< Real Timer Clock
#pragma	intvect	Vectors_Isr_DefaultHandler 94	///< Clock Calibration Unit
#pragma	intvect	Vectors_Isr_DefaultHandler 95	///< Sound Generator 0
#pragma	intvect	Vectors_Isr_DefaultHandler 96	///< I2C interface 0
#pragma	intvect	Vectors_Isr_DefaultHandler 97	///< I2C interface 1
#pragma	intvect	Vectors_Isr_DefaultHandler 98	///< A/D Converter
#pragma	intvect	Vectors_Isr_DefaultHandler 99	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 100	///< Reserved
#pragma	intvect	UART0_RX_ISR			   101	///< LIN USART 0 RX
//#pragma	intvect	Vectors_Isr_DefaultHandler 101	///< LIN USART 0 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 102	///< LIN USART 0 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 103	///< LIN USART 1 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 104	///< LIN USART 1 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 105	///< LIN USART 2 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 106	///< LIN USART 2 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 107	///< LIN USART 3 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 108	///< LIN USART 3 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 109	///< LIN USART 4 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 110	///< LIN USART 4 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 111	///< LIN USART 5 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 112	///< LIN USART 5 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 113	///< LIN USART 6 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 114	///< LIN USART 6 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 115	///< LIN USART 7 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 116	///< LIN USART 7 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 117	///< LIN USART 8 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 118	///< LIN USART 8 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 119	///< LIN USART 9 RX
#pragma	intvect	Vectors_Isr_DefaultHandler 120	///< LIN USART 9 TX
#pragma	intvect	Vectors_Isr_DefaultHandler 121	///< Sound Generator 1
#pragma	intvect	Vectors_Isr_DefaultHandler 122	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 123	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 124	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 125	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 126	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 127	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 128	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 129	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 130	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 131	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 132	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 133	///< Dual operation Flash A
#pragma	intvect	Vectors_Isr_DefaultHandler 134	///< Dual operation Flash B
#pragma	intvect	Vectors_Isr_DefaultHandler 135	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 136	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 137	///< Quad Possition/Revolution counter 0
#pragma	intvect	Vectors_Isr_DefaultHandler 138	///< Quad Possition/Revolution counter 1
#pragma	intvect	Vectors_Isr_DefaultHandler 139	///< A/D Converter 0 - Range Comparator
#pragma	intvect	Vectors_Isr_DefaultHandler 140	///< A/D Converter 0 - Pulse detection
#pragma	intvect	Vectors_Isr_DefaultHandler 141	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 142	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 143	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 144	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 145	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 146	///< Reserved
#pragma	intvect	Vectors_Isr_DefaultHandler 147	///< Reserved

/**
 ******************************************************************************
 ** This function is a placeholder for all vector definitions. Either use
 ** your own placeholder or add necessary code here.
 *****************************************************************************/
__interrupt void Vectors_Isr_DefaultHandler (void)
{
    // disable interrupts
    __DI();

    // halt system or wait for watchdog reset
    while(1)
    {
        __wait_nop();
    }
}

__interrupt void UART0_RX_ISR (void) {
	int foo = 0;
	char bar = 'o';
	__DI();
	
	UART0_SCR0_CRE = 1;
	foo = UART0_RDR0;
	
    // Send a byte
    while (UART0_SSR0_TDRE != 1); // Wait for UART0 to be ready for transmission data
    if (foo == 0x31) {
    	UART0_TDR0 = bar;	// Set data to be sent
    } else {
    	UART0_TDR0 = 0x4E;
    }
	
    PDR13_P2 = ~PDR13_P2;//0;
	
	__EI();
}
