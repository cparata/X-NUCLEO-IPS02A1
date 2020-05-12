/**
 ******************************************************************************
 * @file    VPS2535H.cpp
 * @author  ADG
 * @version V1.0.0
 * @date    08-May-2020
 * @brief   implementatio for VPS2535H driver class
 ******************************************************************************
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


/* Includes ------------------------------------------------------------------*/
#include "VPS2535H.h"


/* Methods -------------------------------------------------------------------*/

/**
 * @brief  Set VPS2535H Initialization
 * @param  VPS2535H handel structure
 * @retval IPS_SUCCESS
 */
int VPS2535H::init(void *init_struct) {
    (void)init_struct;
    VPS2535H_init();
    return IPS_SUCCESS; 
}

/**
 * @brief  Close VPS2535H
 * @param  none
 * @retval IPS_SUCCESS
 */
int VPS2535H::close(void) {
    VPS2535H_close();
    return IPS_SUCCESS; 
}

/* Module Interface */
/**
  * @brief  Initializes the VPS2535H device
  * @param  none
  * @retval VPS2535H status
  */
IPS_StatusTypeDef VPS2535H::VPS2535H_init() {
    digitalWrite(Fr_Stby, HIGH);
    return IPS_SUCCESS;
}

/**
  * @brief  Close (Deinitialize) the VPS2535H device and used peripheral.
  * @param  None
  * @retval VPS2535H status
  */
IPS_StatusTypeDef VPS2535H::VPS2535H_close(){
    digitalWrite(Fr_Stby, HIGH);
    return IPS_SUCCESS;
}

/**
  * @brief  GetSense function gets the value of the Sense power switch output pin 
  * (for either Ch1 or Ch2) upon IO conversion. It just reads from sense pin
  * @param  hips: pointer to a VPS2535H_HandleTypeDef structure that contains
  *                the configuration information for the specified VPS2535H module.
  *                Value got from V-sense output is stored in hips->SenseValue
  *                field. Status of the operation is stored in hips->Status and 
  *                hips->Status fields
  * @retval IPS_StatusTypeDef status
  */
IPS_StatusTypeDef VPS2535H::VPS2535H_get_sense_channel_diagnostic(IPS_HandleTypeDef *hips){
    hips->SenseRawValue = 0; //if channel is wrong Sense value is 0
    hips->GNDSenseRawValue = 0; // VPS2535H doesn't require GND measurement compensation
    hips-> Status =IPS_WRONG_CHANNEL;
    hips->IO_Status = IPS_IO_FAIL;
    if (hips ->ipsChannel == CHANNEL_1) {
        hips->SenseRawValue = analogRead(CurrentSense1) * V_REF * ((R_D1+R_D2)/(R_D2));
    }
    if (hips ->ipsChannel == CHANNEL_2) {
        hips->SenseRawValue = analogRead(CurrentSense2) * V_REF * ((R_D1+R_D2)/(R_D2));
    }
 
    hips->IO_Status = IPS_IO_SUCCESS;
    hips->Status =IPS_SUCCESS;
    return hips-> Status;
}

/**
  * @brief  GetSecureCurrentSense  function gets the I-sense switch output pin
  *         upon ADC conversion. 
  * @param  hips: pointer to a IPS_HandleTypeDef structure that contains
  *         the configuration information for the specified VPS2535H module.
  *         Value got from V-sense output is stored in hips->SenseValue
  *         field.
  *         Status of the operation is stored in hips->Status fields   
  * @retval IPS status
  */
IPS_StatusTypeDef VPS2535H::VPS2535H_get_secure_current_sense(IPS_HandleTypeDef *hips){
  
    if ((hips ->ipsChannel != CHANNEL_1) && (hips ->ipsChannel != CHANNEL_2)) {
        hips->Status = IPS_WRONG_CHANNEL;
        return IPS_WRONG_CHANNEL; 
    }
  
    /* Get sense feedback */
    if ((VPS2535H_get_sense_channel_diagnostic(hips) == IPS_SUCCESS) && (hips->Status == IPS_SUCCESS)) {
        hips->IValue= K*hips->SenseRawValue/R_SENSE;
        return IPS_SUCCESS;
    } else {
        return IPS_FAIL; // see hips->Status
    }
}

/**
  * @brief  GetCurrent  function gets the I-sense switch output pin
  * @param  Ch: Channel number. Possible value are CHANNEL_1 or CHANNEL_2
  * @retval Current Value
  */
float VPS2535H::get_current(int Ch) {
 
    if (Ch == CHANNEL_1) {
        return (K*(analogRead(CurrentSense1))* ((R_D1+R_D2)/(R_D2)) * V_REF/R_SENSE);
    }
    if (Ch == CHANNEL_2) {
        return (K*(analogRead(CurrentSense2))* ((R_D1+R_D2)/(R_D2)) * V_REF/R_SENSE);
    }
    return 0;
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
