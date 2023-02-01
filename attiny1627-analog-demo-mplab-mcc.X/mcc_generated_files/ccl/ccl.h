/**
 * CCL Generated Header File
 * 
 * @file ccl.h
 * 
 * @defgroup  ccl CCL
 * 
 * @brief This file contains the API prototype for the CCL driver. 
 *
 * @version Driver Version  1.1.0
*/

#include <stdint.h>
#include <stdbool.h>

#ifndef CCL_H_INCLUDED
#define CCL_H_INCLUDED

#include "../system/utils/compiler.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @ingroup  ccl
 * @brief Initializes the CCL. This is called only once during the system initialization.
 * @pre None.
 * @param None.
 * @return None.
 */
int8_t CCL_Initialize(void);
/**
 * @ingroup ccl
 * @brief Default interrupt handler assigned to handle the LUT1_OUT interrupt events.
 * @pre CCL_Initialize() is already called.
 * @param None.
 * @return None.
 */
void LUT1_OUT_DefaultInterruptHandler(void);

/**
 * @ingroup ccl
 * @brief Assigns an interrupt handler for the LUT1_OUT interrupt event.
 * @pre CCL_Initialize() is already called.
 * @param (*interruptHandler)(void) - InterruptHandler function pointer.
 * @return None.
 */
void LUT1_OUT_SetInterruptHandler(void (* interruptHandler)(void)) ; 

#ifdef __cplusplus
}
#endif

#endif /* CCL_H_INCLUDED */
