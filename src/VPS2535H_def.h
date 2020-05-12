/**
 *******************************************************************************
 * @file    VPS2535H_def.h
 * @author  ADG
 * @version V1.0.0
 * @date    08-May-2020
 * @brief   VPS235H1 module driver.
 *          This file provides firmware functions to manage the following 
 *          functionalities of the VPS235H1 power switch:
 *           + Initialization and de-initialization functions
 *           + Diagnostic Sense Pin Configuration
 *           + Get Sense Diagnostic Values
 *******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2020 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
*/ 


/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __VPS2535H_H
#define __VPS2535H_H


/* Includes ------------------------------------------------------------------*/

#include "IPS_def.h"


/* Definitions ---------------------------------------------------------------*/

/* Number of channels */
#define NUM_CHANNELS 2

/* Channel 0 */
#define CHANNEL_1 1
/* Channel 1 */
#define CHANNEL_2 2

/* V-Sense Temperature Typical value at 25 degree */
#define V_SENSE_TC_TYPICAL 2.070

/* Vcc transfer function */
#define VCC_TRANSFER_FUNCT(sense)  ((sense)*4)
/* Current K factor */
#define K 3500


#endif /* __VPS2535H_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/ 
