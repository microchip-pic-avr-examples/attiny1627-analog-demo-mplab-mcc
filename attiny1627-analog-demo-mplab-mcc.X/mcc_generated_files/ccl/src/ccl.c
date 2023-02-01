/**
 * CCL Generated Driver File
 * 
 * @file ccl.c
 * 
 * @ingroup  ccl
 * 
 * @brief This file contains the API implementations for the CCL driver. 
 *
 * @version Driver Version 1.1.1
*/

/*
© [2023] Microchip Technology Inc. and its subsidiaries.

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

#include "../ccl.h"
static void (*LUT1_OUT_InterruptHandler)(void);

int8_t CCL_Initialize(void)
{
    //INTMODE0 INTDISABLE; INTMODE1 RISING; INTMODE2 INTDISABLE; INTMODE3 INTDISABLE; 
    CCL.INTCTRL0 = 0x4;

    //INT 0x0; 
    CCL.INTFLAGS = 0x0;

    //INSEL0 MASK; INSEL1 MASK; 
    CCL.LUT0CTRLB = 0x0;

    //INSEL2 MASK; 
    CCL.LUT0CTRLC = 0x0;

    //INSEL0 MASK; INSEL1 IO; 
    CCL.LUT1CTRLB = 0x50;

    //INSEL2 MASK; 
    CCL.LUT1CTRLC = 0x0;

    //INSEL0 MASK; INSEL1 MASK; 
    CCL.LUT2CTRLB = 0x0;

    //INSEL2 MASK; 
    CCL.LUT2CTRLC = 0x0;

    //INSEL0 MASK; INSEL1 MASK; 
    CCL.LUT3CTRLB = 0x0;

    //INSEL2 MASK; 
    CCL.LUT3CTRLC = 0x0;

    //SEQSEL DISABLE; 
    CCL.SEQCTRL0 = 0x0;

    //SEQSEL DISABLE; 
    CCL.SEQCTRL1 = 0x0;

    //TRUTH 0; 
    CCL.TRUTH0 = 0x0;

    //TRUTH 4; 
    CCL.TRUTH1 = 0x4;

    //TRUTH 0; 
    CCL.TRUTH2 = 0x0;

    //TRUTH 0; 
    CCL.TRUTH3 = 0x0;

    //CLKSRC OSCULP1K; EDGEDET DIS; ENABLE disabled; FILTSEL DISABLE; OUTEN disabled; 
    CCL.LUT0CTRLA = 0xC;

    //CLKSRC OSCULP1K; EDGEDET EN; ENABLE enabled; FILTSEL FILTER; OUTEN disabled; 
    CCL.LUT1CTRLA = 0xAD;

    //CLKSRC CLKPER; EDGEDET DIS; ENABLE disabled; FILTSEL DISABLE; OUTEN disabled; 
    CCL.LUT2CTRLA = 0x0;

    //CLKSRC CLKPER; EDGEDET DIS; ENABLE disabled; FILTSEL DISABLE; OUTEN disabled; 
    CCL.LUT3CTRLA = 0x0;

    //ENABLE enabled; RUNSTDBY enabled; 
    CCL.CTRLA = 0x41;
    
    // register default ISC callback functions at runtime; use these methods to register a custom function
    LUT1_OUT_SetInterruptHandler(LUT1_OUT_DefaultInterruptHandler);

    return 0;
}

/**
  Allows selecting an interrupt handler for LUT1_OUT at application runtime
*/
void LUT1_OUT_SetInterruptHandler(void (* interruptHandler)(void)) 
{
    LUT1_OUT_InterruptHandler = interruptHandler;
}

void LUT1_OUT_DefaultInterruptHandler(void)
{
    // add your LUT1_OUT interrupt custom code
    // or set custom function using LUT1_OUT_SetInterruptHandler()
}

ISR(CCL_CCL_vect)
{
    /*
    * Insert your CCL interrupt handling code
    *
    * Interrupt flag can be cleared by writing 1 to its bit location
    * in the INTFLAGS register
    */

    // Call the interrupt handler for the callback registered at runtime
    if(CCL.INTFLAGS & CCL_INT1_bm)
    {
        LUT1_OUT_InterruptHandler();
    }
    
    /* Clear interrupt flags */
    CCL.INTFLAGS = CCL_INT1_bm ;
}
