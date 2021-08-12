/*
Copyright (c) [2012-2020] Microchip Technology Inc.  

    All rights reserved.

    You are permitted to use the accompanying software and its derivatives 
    with Microchip products. See the Microchip license agreement accompanying 
    this software, if any, for additional info regarding your rights and 
    obligations.
    
    MICROCHIP SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT 
    WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
    LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT 
    AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT WILL MICROCHIP OR ITS
    LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT 
    LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE 
    THEORY FOR ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES INCLUDING BUT NOT 
    LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, 
    OR OTHER SIMILAR COSTS. 
    
    To the fullest extend allowed by law, Microchip and its licensors 
    liability will not exceed the amount of fees, if any, that you paid 
    directly to Microchip to use this software. 
    
    THIRD PARTY SOFTWARE:  Notwithstanding anything to the contrary, any 
    third party software accompanying this software is subject to the terms 
    and conditions of the third party's license agreement.  To the extent 
    required by third party licenses covering such third party software, 
    the terms of such license will apply in lieu of the terms provided in 
    this notice or applicable license.  To the extent the terms of such 
    third party licenses prohibit any of the restrictions described here, 
    such restrictions will not apply to such third party software.
*/
#include "mcc_generated_files/system/system.h"
#include "mcc_generated_files/adc/adc0.h"
#include "mcc_generated_files/timer/delay.h"

#include "ADCPrint.h"

//Enable the ADC to function in Standby or Debug Modes
#define ENABLE_ADC_STDBY_DBG() do { ADC0.CTRLA = 0x00; ADC0.CTRLA = 0xA1; } while (0)

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

int main(void)
{
    SYSTEM_Initialize();
                
    //Enable the ADCC in Standby and Debug
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
        while (USART0_IsTxBusy());
        USART0.STATUS = USART_TXCIF_bm;
                
        //If the button was pressed while printing
        if (getGainFlag())
            continue;
        
        //Go to Sleep
        asm ("SLEEP");
        asm ("NOP");
    }    
}