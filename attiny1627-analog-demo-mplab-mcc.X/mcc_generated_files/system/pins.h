/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  1.0.0
*/

/*
� [2021] Microchip Technology Inc. and its subsidiaries.

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

#ifndef PINS_H_INCLUDED
#define PINS_H_INCLUDED

#include <avr/io.h>
#include "./port.h"

//get/set IO_PB2 aliases
#define IO_PB2_SetHigh() do { PORTB_OUTSET = 0x4; } while(0)
#define IO_PB2_SetLow() do { PORTB_OUTCLR = 0x4; } while(0)
#define IO_PB2_Toggle() do { PORTB_OUTTGL = 0x4; } while(0)
#define IO_PB2_GetValue() (VPORTB.IN & (0x1 << 2))
#define IO_PB2_SetDigitalInput() do { PORTB_DIRCLR = 0x4; } while(0)
#define IO_PB2_SetDigitalOutput() do { PORTB_DIRSET = 0x4; } while(0)
#define IO_PB2_SetPullUp() do { PORTB_PIN2CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PB2_ResetPullUp() do { PORTB_PIN2CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PB2_SetInverted() do { PORTB_PIN2CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PB2_ResetInverted() do { PORTB_PIN2CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PB2_DisableInterruptOnChange() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PB2_EnableInterruptForBothEdges() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PB2_EnableInterruptForRisingEdge() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PB2_EnableInterruptForFallingEdge() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PB2_DisableDigitalInputBuffer() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PB2_EnableInterruptForLowLevelSensing() do { PORTB.PIN2CTRL = (PORTB.PIN2CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set IO_PB5 aliases
#define IO_PB5_SetHigh() do { PORTB_OUTSET = 0x20; } while(0)
#define IO_PB5_SetLow() do { PORTB_OUTCLR = 0x20; } while(0)
#define IO_PB5_Toggle() do { PORTB_OUTTGL = 0x20; } while(0)
#define IO_PB5_GetValue() (VPORTB.IN & (0x1 << 5))
#define IO_PB5_SetDigitalInput() do { PORTB_DIRCLR = 0x20; } while(0)
#define IO_PB5_SetDigitalOutput() do { PORTB_DIRSET = 0x20; } while(0)
#define IO_PB5_SetPullUp() do { PORTB_PIN5CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define IO_PB5_ResetPullUp() do { PORTB_PIN5CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define IO_PB5_SetInverted() do { PORTB_PIN5CTRL  |= PORT_INVEN_bm; } while(0)
#define IO_PB5_ResetInverted() do { PORTB_PIN5CTRL  &= ~PORT_INVEN_bm; } while(0)
#define IO_PB5_DisableInterruptOnChange() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define IO_PB5_EnableInterruptForBothEdges() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define IO_PB5_EnableInterruptForRisingEdge() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define IO_PB5_EnableInterruptForFallingEdge() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define IO_PB5_DisableDigitalInputBuffer() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define IO_PB5_EnableInterruptForLowLevelSensing() do { PORTB.PIN5CTRL = (PORTB.PIN5CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set SW0 aliases
#define SW0_SetHigh() do { PORTC_OUTSET = 0x10; } while(0)
#define SW0_SetLow() do { PORTC_OUTCLR = 0x10; } while(0)
#define SW0_Toggle() do { PORTC_OUTTGL = 0x10; } while(0)
#define SW0_GetValue() (VPORTC.IN & (0x1 << 4))
#define SW0_SetDigitalInput() do { PORTC_DIRCLR = 0x10; } while(0)
#define SW0_SetDigitalOutput() do { PORTC_DIRSET = 0x10; } while(0)
#define SW0_SetPullUp() do { PORTC_PIN4CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define SW0_ResetPullUp() do { PORTC_PIN4CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define SW0_SetInverted() do { PORTC_PIN4CTRL  |= PORT_INVEN_bm; } while(0)
#define SW0_ResetInverted() do { PORTC_PIN4CTRL  &= ~PORT_INVEN_bm; } while(0)
#define SW0_DisableInterruptOnChange() do { PORTC.PIN4CTRL = (PORTC.PIN4CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define SW0_EnableInterruptForBothEdges() do { PORTC.PIN4CTRL = (PORTC.PIN4CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define SW0_EnableInterruptForRisingEdge() do { PORTC.PIN4CTRL = (PORTC.PIN4CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define SW0_EnableInterruptForFallingEdge() do { PORTC.PIN4CTRL = (PORTC.PIN4CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define SW0_DisableDigitalInputBuffer() do { PORTC.PIN4CTRL = (PORTC.PIN4CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define SW0_EnableInterruptForLowLevelSensing() do { PORTC.PIN4CTRL = (PORTC.PIN4CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

//get/set LED0 aliases
#define LED0_SetHigh() do { PORTB_OUTSET = 0x80; } while(0)
#define LED0_SetLow() do { PORTB_OUTCLR = 0x80; } while(0)
#define LED0_Toggle() do { PORTB_OUTTGL = 0x80; } while(0)
#define LED0_GetValue() (VPORTB.IN & (0x1 << 7))
#define LED0_SetDigitalInput() do { PORTB_DIRCLR = 0x80; } while(0)
#define LED0_SetDigitalOutput() do { PORTB_DIRSET = 0x80; } while(0)
#define LED0_SetPullUp() do { PORTB_PIN7CTRL  |= PORT_PULLUPEN_bm; } while(0)
#define LED0_ResetPullUp() do { PORTB_PIN7CTRL  &= ~PORT_PULLUPEN_bm; } while(0)
#define LED0_SetInverted() do { PORTB_PIN7CTRL  |= PORT_INVEN_bm; } while(0)
#define LED0_ResetInverted() do { PORTB_PIN7CTRL  &= ~PORT_INVEN_bm; } while(0)
#define LED0_DisableInterruptOnChange() do { PORTB.PIN7CTRL = (PORTB.PIN7CTRL & ~PORT_ISC_gm) | 0x0 ; } while(0)
#define LED0_EnableInterruptForBothEdges() do { PORTB.PIN7CTRL = (PORTB.PIN7CTRL & ~PORT_ISC_gm) | 0x1 ; } while(0)
#define LED0_EnableInterruptForRisingEdge() do { PORTB.PIN7CTRL = (PORTB.PIN7CTRL & ~PORT_ISC_gm) | 0x2 ; } while(0)
#define LED0_EnableInterruptForFallingEdge() do { PORTB.PIN7CTRL = (PORTB.PIN7CTRL & ~PORT_ISC_gm) | 0x3 ; } while(0)
#define LED0_DisableDigitalInputBuffer() do { PORTB.PIN7CTRL = (PORTB.PIN7CTRL & ~PORT_ISC_gm) | 0x4 ; } while(0)
#define LED0_EnableInterruptForLowLevelSensing() do { PORTB.PIN7CTRL = (PORTB.PIN7CTRL & ~PORT_ISC_gm) | 0x5 ; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize();

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PB2 pin. 
 *        This is a predefined interrupt handler to be used together with the PB2_SetInterruptHandler() method.
 *        This handler is called every time the PB2 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PB2_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PB2 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PB2 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PB2_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PB5 pin. 
 *        This is a predefined interrupt handler to be used together with the PB5_SetInterruptHandler() method.
 *        This handler is called every time the PB5 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PB5_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PB5 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PB5 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PB5_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PC4 pin. 
 *        This is a predefined interrupt handler to be used together with the PC4_SetInterruptHandler() method.
 *        This handler is called every time the PC4 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PC4_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PC4 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PC4 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PC4_SetInterruptHandler(void (* interruptHandler)(void)) ; 

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for PB7 pin. 
 *        This is a predefined interrupt handler to be used together with the PB7_SetInterruptHandler() method.
 *        This handler is called every time the PB7 ISR is executed. 
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param none
 * @return none
 */
void PB7_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for PB7 pin input-sense-config functionality.
 *        Allows selecting an interrupt handler for PB7 at application runtime
 * @pre PIN_MANAGER_Initialize() has been called at least once
 * @param InterruptHandler function pointer.
 * @return none
 */
void PB7_SetInterruptHandler(void (* interruptHandler)(void)) ; 
#endif /* PINS_H_INCLUDED */
