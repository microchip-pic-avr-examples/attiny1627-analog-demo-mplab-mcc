/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   1.0.0
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


#include "../usart0.h"
#define RECEIVE_ERROR_MASK 0x46

#if defined(__GNUC__)

int USART0_printCHAR(char character, FILE *stream)
{
    while(!(USART0_IsTxReady()));
    USART0_Write(character);
    return 0;
}

FILE USART0_stream = FDEV_SETUP_STREAM(USART0_printCHAR, NULL, _FDEV_SETUP_WRITE);

#elif defined(__ICCAVR__)

int putchar(int outChar)
{
    USART0_Write(outChar);
    return outChar;
}
#endif

static void DefaultFramingErrorCallback(void);
static void DefaultOverrunErrorCallback(void);
static void DefaultParityErrorCallback(void);
void (*USART0_framing_err_cb)(void) = &DefaultFramingErrorCallback;
void (*USART0_overrun_err_cb)(void) = &DefaultOverrunErrorCallback;
void (*USART0_parity_err_cb)(void) = &DefaultParityErrorCallback;

const struct UART_INTERFACE USART0_Interface = {
  .Initialize = USART0_Initialize,
  .Write = USART0_Write,
  .Read = USART0_Read,
  .RxCompleteCallbackRegister = NULL,
  .TxCompleteCallbackRegister = NULL,
  .ErrorCallbackRegister = NULL,
  .FramingErrorCallbackRegister = USART0_FramingErrorCallbackRegister,
  .OverrunErrorCallbackRegister = USART0_OverrunErrorCallbackRegister,
  .ParityErrorCallbackRegister = USART0_ParityErrorCallbackRegister,
  .ChecksumErrorCallbackRegister = NULL,
  .IsRxReady = USART0_IsRxReady,
  .IsTxReady = USART0_IsTxReady,
  .IsTxDone = USART0_IsTxDone
};

void USART0_Initialize(void)
{
    //set baud rate register
    USART0.BAUD = (uint16_t)USART0_BAUD_RATE(9600);
	
    // ABEIE disabled; DREIE disabled; LBME disabled; RS485 DISABLE; RXCIE disabled; RXSIE disabled; TXCIE disabled; 
    USART0.CTRLA = 0x0;
	
    // MPCM disabled; ODME disabled; RXEN disabled; RXMODE NORMAL; SFDEN disabled; TXEN enabled; 
    USART0.CTRLB = 0x40;
	
    // CMODE Asynchronous Mode; UCPHA enabled; UDORD disabled; CHSIZE Character size: 8 bit; PMODE No Parity; SBMODE 1 stop bit; 
    USART0.CTRLC = 0x3;
	
    //DBGCTRL_DBGRUN
    USART0.DBGCTRL = 0x0;
	
    //EVCTRL_IREI
    USART0.EVCTRL = 0x0;
	
    //RXPLCTRL_RXPL
    USART0.RXPLCTRL = 0x0;
	
    //TXPLCTRL_TXPL
    USART0.TXPLCTRL = 0x0;
	

#if defined(__GNUC__)
    stdout = &USART0_stream;
#endif

}

void USART0_FramingErrorCallbackRegister(void* callbackHandler)
{
    USART0_framing_err_cb = callbackHandler;
}

void USART0_OverrunErrorCallbackRegister(void* callbackHandler)
{
    USART0_overrun_err_cb = callbackHandler;
}

void USART0_ParityErrorCallbackRegister(void* callbackHandler)
{
    USART0_parity_err_cb = callbackHandler;
}

static void DefaultFramingErrorCallback(void)
{
    /* Add your interrupt code here or use USART0.FramingCallbackRegister function to use Custom ISR */
}

static void DefaultOverrunErrorCallback(void)
{
   /* Add your interrupt code here or use USART0.OverrunCallbackRegister function to use Custom ISR */
}

static void DefaultParityErrorCallback(void)
{
    /* Add your interrupt code here or use USART0.ParityCallbackRegister function to use Custom ISR */
}

void USART0_Enable(void)
{
    USART0.CTRLB |= USART_RXEN_bm | USART_TXEN_bm;
}

void USART0_EnableRx(void)
{
    USART0.CTRLB |= USART_RXEN_bm;
}

void USART0_EnableTx(void)
{
    USART0.CTRLB |= USART_TXEN_bm;
}

void USART0_Disable(void)
{
    USART0.CTRLB &= ~(USART_RXEN_bm | USART_TXEN_bm);
}

uint8_t USART0_GetData(void)
{
    return USART0.RXDATAL;
}

bool USART0_IsTxReady(void)
{
    return (USART0.STATUS & USART_DREIF_bm);
}

bool USART0_IsRxReady(void)
{
    return (USART0.STATUS & USART_RXCIF_bm);
}

bool USART0_IsTxDone(void)
{
    return (USART0.STATUS & USART_TXCIF_bm);
}

void USART0_ErrorCheck(void)
{
    uint8_t errorMask = USART0.RXDATAH;
    if(errorMask & RECEIVE_ERROR_MASK)
    {
        if(errorMask & USART_PERR_bm)
        {
            USART0_parity_err_cb();
        } 
        if(errorMask & USART_FERR_bm)
        {
            USART0_framing_err_cb();
        }
        if(errorMask & USART_BUFOVF_bm)
        {
            USART0_overrun_err_cb();
        }
    }
    
}

uint8_t USART0_Read(void)
{       
    return USART0.RXDATAL;
}

void USART0_Write(const uint8_t data)
{
    USART0.TXDATAL = data;
}