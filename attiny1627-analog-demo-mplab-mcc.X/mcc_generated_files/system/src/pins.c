/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 1.0.0
*/

/*
© [2021] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

static void (*PB2_InterruptHandler)(void);
static void (*PB5_InterruptHandler)(void);
static void (*PC4_InterruptHandler)(void);
static void (*PB7_InterruptHandler)(void);
void PORT_Initialize(void);

void PIN_MANAGER_Initialize()
{
  PORT_Initialize();
  /* DIR Registers Initialization */
    PORTA.DIR = 0x0;
    PORTB.DIR = 0x84;
    PORTC.DIR = 0x0;

  /* OUT Registers Initialization */
    PORTA.OUT = 0x0;
    PORTB.OUT = 0x0;
    PORTC.OUT = 0x0;

  /* PINxCTRL registers Initialization */
    PORTA.PIN0CTRL = 0x0;
    PORTA.PIN1CTRL = 0x0;
    PORTA.PIN2CTRL = 0x0;
    PORTA.PIN3CTRL = 0x0;
    PORTA.PIN4CTRL = 0x0;
    PORTA.PIN5CTRL = 0x0;
    PORTA.PIN6CTRL = 0x0;
    PORTA.PIN7CTRL = 0x0;
    PORTB.PIN0CTRL = 0x0;
    PORTB.PIN1CTRL = 0x0;
    PORTB.PIN2CTRL = 0x0;
    PORTB.PIN3CTRL = 0x0;
    PORTB.PIN4CTRL = 0x0;
    PORTB.PIN5CTRL = 0x0;
    PORTB.PIN6CTRL = 0x0;
    PORTB.PIN7CTRL = 0x0;
    PORTC.PIN0CTRL = 0x0;
    PORTC.PIN1CTRL = 0x0;
    PORTC.PIN2CTRL = 0x0;
    PORTC.PIN3CTRL = 0x0;
    PORTC.PIN4CTRL = 0x88;
    PORTC.PIN5CTRL = 0x0;
    PORTC.PIN6CTRL = 0x0;
    PORTC.PIN7CTRL = 0x0;

  /* Multi-pin Config registers Initialization */

  /* PORTMUX Initialization */
    PORTMUX.CCLROUTEA = 0x0;
    PORTMUX.EVSYSROUTEA = 0x0;
    PORTMUX.SPIROUTEA = 0x0;
    PORTMUX.TCAROUTEA = 0x0;
    PORTMUX.TCBROUTEA = 0x0;
    PORTMUX.USARTROUTEA = 0x0;

  // register default ISC callback functions at runtime; use these methods to register a custom function
    PB2_SetInterruptHandler(PB2_DefaultInterruptHandler);
    PB5_SetInterruptHandler(PB5_DefaultInterruptHandler);
    PC4_SetInterruptHandler(PC4_DefaultInterruptHandler);
    PB7_SetInterruptHandler(PB7_DefaultInterruptHandler);
}

void PORT_Initialize(void)
{
  /* On AVR devices all peripherals are enable from power on reset, this
  * disables all peripherals to save power. Driver shall enable
  * peripheral if used */

  /* Set all pins to low power mode */
    for (uint8_t i = 0; i < 8; i++) {
      *((uint8_t *)&PORTA + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
      *((uint8_t *)&PORTB + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
    for (uint8_t i = 0; i < 8; i++) {
      *((uint8_t *)&PORTC + 0x10 + i) |= 1 << PORT_PULLUPEN_bp;
    }
    
}
/**
  Allows selecting an interrupt handler for PB2 at application runtime
*/
void PB2_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PB2_InterruptHandler = interruptHandler;
}

void PB2_DefaultInterruptHandler(void)
{
    // add your PB2 interrupt custom code
    // or set custom function using PB2_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PB5 at application runtime
*/
void PB5_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PB5_InterruptHandler = interruptHandler;
}

void PB5_DefaultInterruptHandler(void)
{
    // add your PB5 interrupt custom code
    // or set custom function using PB5_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PC4 at application runtime
*/
void PC4_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PC4_InterruptHandler = interruptHandler;
}

void PC4_DefaultInterruptHandler(void)
{
    // add your PC4 interrupt custom code
    // or set custom function using PC4_SetInterruptHandler()
}
/**
  Allows selecting an interrupt handler for PB7 at application runtime
*/
void PB7_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    PB7_InterruptHandler = interruptHandler;
}

void PB7_DefaultInterruptHandler(void)
{
    // add your PB7 interrupt custom code
    // or set custom function using PB7_SetInterruptHandler()
}
ISR(PORTA_PORT_vect)
{ 
    /* Clear interrupt flags */
    VPORTA.INTFLAGS = 0xff;
}

ISR(PORTB_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTB.INTFLAGS & PORT_INT2_bm)
    {
       PB2_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT5_bm)
    {
       PB5_InterruptHandler(); 
    }
    if(VPORTB.INTFLAGS & PORT_INT7_bm)
    {
       PB7_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTB.INTFLAGS = 0xff;
}

ISR(PORTC_PORT_vect)
{ 
    // Call the interrupt handler for the callback registered at runtime
    if(VPORTC.INTFLAGS & PORT_INT4_bm)
    {
       PC4_InterruptHandler(); 
    }
    /* Clear interrupt flags */
    VPORTC.INTFLAGS = 0xff;
}

/**
 End of File
*/