																								/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
*/
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


#include "../adc0.h"
#include "../../system/system.h"
#include "../../../ADCPrint.h"

adc_irq_cb_t ADC0_window_cb = NULL;

/**
 * \brief Initialize ADC interface
 */
int8_t ADC0_Initialize(void)
{
     
    //PRESC System clock divided by 2; 
    ADC0.CTRLB = 0x0;

    //FREERUN disabled; LEFTADJ disabled; SAMPNUM No accumulation; 
    ADC0.CTRLF = 0x0;

    //REFSEL VDD; TIMEBASE 2; 
    ADC0.CTRLC = 0x10;

    //WINCM No Window Comparison; WINSRC RESULT; 
    ADC0.CTRLD = 0x0;

    //SAMPDUR 255; 
    ADC0.CTRLE = 0xFF;

    //ADCPGASAMPDUR 6 ADC cycles; GAIN 1X Gain; PGABIASSEL 1/4x BIAS current; PGAEN enabled; 
    ADC0.PGACTRL = 0x19;

    //DBGRUN disabled; 
    ADC0.DBGCTRL = 0x0;

    //DIFF disabled; MODE SINGLE_12BIT; START Start on event; 
    ADC0.COMMAND = 0x14;

    //RESOVR disabled; RESRDY disabled; SAMPOVR disabled; SAMPRDY enabled; TRIGOVR disabled; WCMP disabled; 
    ADC0.INTCTRL = 0x2;

    //MUXPOS ADC input pin 8; VIA Via PGA; 
    ADC0.MUXPOS = 0x48;

    //MUXNEG Ground; VIA Via PGA; 
    ADC0.MUXNEG = 0x70;

    // Window comparator high threshold 
    ADC0.WINHT = 0x0;

    // Window comparator low threshold 
    ADC0.WINLT = 0x0;

    //ENABLE enabled; LOWLAT disabled; RUNSTDBY disabled; 
    ADC0.CTRLA = 0x1;


    return 0;
}

void ADC0_Enable(void)
{
    ADC0.CTRLA |= ADC_ENABLE_bm;
}

void ADC0_Disable(void)
{
    ADC0.CTRLA &= ~ADC_ENABLE_bm;
}

void ADC0_SetWindowHigh(adc_result_t high)
{
    ADC0.WINHT = high;
}

void ADC0_SetWindowLow(adc_result_t low)
{
    ADC0.WINLT = low;
}

void ADC0_SetWindowMode(ADC0_window_mode_t mode)
{
    ADC0.CTRLD = mode;
}

void ADC0_SetWindowChannel(adc_0_channel_t channel)
{
    ADC0.MUXPOS &= ADC_VIA_gm;
    ADC0.MUXPOS |= channel;
}

void ADC0_StartConversion(adc_0_channel_t channel)
{
    ADC0.MUXPOS &= ADC_VIA_gm;
    ADC0.MUXPOS |= channel;
    ADC0.COMMAND &= ~ADC_DIFF_bm;
    ADC0.COMMAND |= ADC_START_IMMEDIATE_gc;
}

void ADC0_StartDiffConversion(adc_0_channel_t channel, adc_0_muxneg_channel_t channel1)
{
    ADC0.MUXPOS &= ADC_VIA_gm;
    ADC0.MUXPOS |= channel;

    ADC0.MUXNEG &= ADC_VIA_gm;
    ADC0.MUXNEG |= channel1;
    
    ADC0.COMMAND |= (ADC_START_IMMEDIATE_gc | ADC_DIFF_bm);
}

void ADC0_StopConversion(void)
{
    ADC0.COMMAND |= ADC_START_STOP_gc;
}

bool ADC0_IsConversionDone(void)
{
    return (ADC0.INTFLAGS & ADC_RESRDY_bm);
}

adc_result_t ADC0_GetConversionResult(void)
{
    return (ADC0.RESULT);
}

bool ADC0_GetWindowResult(void)
{
    bool temp = (ADC0.INTFLAGS & ADC_WCMP_bm);
    ADC0.INTFLAGS = ADC_WCMP_bm; // Clear intflag if set
    return temp;
}

adc_result_t ADC0_GetConversion(adc_0_channel_t channel)
{
    adc_result_t res;

    ADC0_StartConversion(channel);
    while (!ADC0_IsConversionDone());
    res = ADC0_GetConversionResult();
    ADC0.INTFLAGS = ADC_RESRDY_bm;
    return res;
}

diff_adc_result_t ADC0_GetDiffConversion(bool enablePGA, adc_0_channel_t channel, adc_0_muxneg_channel_t channel1)
{
    diff_adc_result_t res;

    ADC0_StartDiffConversion(channel, channel1|(enablePGA<<6));
    while (!ADC0_IsConversionDone());
    res = ADC0_GetConversionResult();
    ADC0.INTFLAGS |= ADC_RESRDY_bm;
    return res;
}

uint8_t ADC0_GetResolution(void)
{
    return (ADC0.COMMAND & ADC_MODE_SINGLE_8BIT_gc) ? 8 : 12;
}

void ADC0_RegisterWindowCallback(adc_irq_cb_t f)
{
    ADC0_window_cb = f;
}


ISR(ADC0_SAMPRDY_vect)
{
    /* Insert your ADC Sample ready interrupt handling code here */
    setResultFlag();
    LED0_Toggle();
    
    // Clear the interrupt flag
    ADC0.INTFLAGS = ADC_SAMPRDY_bm;
}

ISR(ADC0_RESRDY_vect)
{
    /* Insert your ADC result ready interrupt handling code here */
    
    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_RESRDY_bm;
}

ISR(ADC0_ERROR_vect)
{
    /* Insert your ADC Error interrupt handling code here */

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_TRIGOVR_bm;

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_SAMPOVR_bm;

    /* The interrupt flag has to be cleared manually */
    ADC0.INTFLAGS = ADC_RESOVR_bm;
}

/* PGA API's */
void ADC0_PGA_enable(void)
{
    ADC0.PGACTRL |= ADC_PGAEN_bm;
}

void ADC0_PGA_disable(void)
{
    ADC0.PGACTRL &= ~ADC_PGAEN_bm;
}

void ADC0_PGA_Gain_Setting(ADC_GAIN_t value)
{
    ADC0.PGACTRL = (ADC0.PGACTRL & ~ADC_GAIN_gm) | value;
}

void ADC0_PGA_Bias_Select(ADC_PGABIASSEL_t value)
{
    ADC0.PGACTRL = (ADC0.PGACTRL & ~ADC_PGABIASSEL_gm) | value;
}

void ADC0_PGA_Sample_Duration(ADC_ADCPGASAMPDUR_t value)
{
    ADC0.PGACTRL = (ADC0.PGACTRL & ~ADC_ADCPGASAMPDUR_gm) | value;
}
