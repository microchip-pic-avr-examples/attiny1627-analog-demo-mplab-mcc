/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
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
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/adc/adc0.h"
#include "mcc_generated_files/timer/delay.h"

#include "ADCPrint.h"

//Enable the ADC to function in Standby or Debug Modes
#define ENABLE_ADC_STDBY_DBG() do { ADC0.CTRLA &= ~ADC_ENABLE_bm; ADC0.DBGCTRL = ADC_DBGRUN_bm; ADC0.CTRLA |= ADC_ENABLE_bm | ADC_RUNSTDBY_bm; } while (0)

//Strings associated with gains
const char* gains[] = {"1", "2", "4", "8", "16"};

//Returns the string associated with the current gain settings
const char* getCurrentGain(void)
{
    uint8_t index = (ADC0.PGACTRL & ADC_GAIN_gm) >> ADC_GAIN_gp;
    return gains[index];
}

//Increases ADC gain by 1 step - loops back to 1x after reaching 16x
void increaseADCGain(void)
{
    //Get the gain bits
    ADC_GAIN_t gain = (ADC0.PGACTRL & ADC_GAIN_gm) >> ADC_GAIN_gp;
    
    //Increment Gain
    gain++;
    
    //If the gain is above max, loopback to 1x
    if (gain == 5)
    {
        gain = 0;
    }
    
    //Re-shift Gain Value
    gain = gain << ADC_GAIN_gp;
    
    ADC0_PGA_Gain_Setting(gain);
}

void onButtonPress(void)
{
    //Stop the RTC
    RTC_Stop();
    
    //Set the Gain Flag
    setGainFlag();
}

int main(void)
{
    SYSTEM_Initialize();
             
    //Connect the CCL Callback for Button Press
    LUT1_OUT_SetInterruptHandler(&onButtonPress);
    
    //Enable the ADC in Standby and Debug
    ENABLE_ADC_STDBY_DBG();
    
    //Write an empty byte to set the USART TXCIF flags
    USART0_Write(0x00);
    
    float result = 0.0;
    const float bitsPerVolt = 3.3 / 4096;
    
    while(1)
    {
        if (getGainFlag())
        {
            //Gain Changed
            clearGainFlag();
            
            //Increase gain of ADC
            increaseADCGain();
            
            //Print Results
            printf("New Gain: %s\n\r\n\r", getCurrentGain());
            
            //Restart the RTC
            RTC_Start();
        }
        else if (getResultFlag())
        {
            //Result Changed
            clearResultFlag();
            
            //Convert result to floating point
            result = ADC0_GetConversionResult() * bitsPerVolt;
            
            //Toggle LED
            LED0_Toggle();
            
            //Print Results
            printf("Current Gain: %s\n\r", getCurrentGain());
            printf("Measured: %1.3fV\n\r\n\r", result);
        }
        
        //Wait for UART to finish
        while (!USART0_IsTxDone());
        USART0.STATUS = USART_TXCIF_bm;
                
        //If the button was pressed while printing
        if (getGainFlag())
            continue;
        
        //Go to Sleep
        asm ("SLEEP");
        asm ("NOP");
    }    
}