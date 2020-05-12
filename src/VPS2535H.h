/**
 *******************************************************************************
 * @file    VPS2535H.h
 * @author  ADG
 * @version V1.0.0
 * @date    08-May-2020
 * @brief   vps2535h module driver.
 *          This file provides firmware functions to manage the following 
 *          functionalities of the vps2535h power switch:
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

#ifndef __VPS2535H_CLASS_H
#define __VPS2535H_CLASS_H
 

/* Includes ------------------------------------------------------------------*/

#include "Arduino.h"
#include "PowerSwitch.h"
#include "VPS2535H_def.h"
 
 
/* Classes -------------------------------------------------------------------*/

/** Class representing a VPS2535H power switch component
 */  
 
class VPS2535H : public PowerSwitch {
    
public:    
    int In_1,In_2,Fr_Stby;
 
    /** Constructor
     * @param[in] input Pin for the power switch
     * @param[out] sense1 and sense2, outputs from Ch1 and Ch2
     * @param[in] vref, reference voltage
     * @param[in] rsense, sense resistor ouside of chip
     * @param[in] rd1, upper partitor resistor (=R6 in schematic) to protect ADC 
     * @param[in] rd1, lower partitor resistor (=R7 in schematic) to protect ADC
     */
    VPS2535H(int in1, int in2, int frStdby,
             int sense1, int sense2, float vref,float rsense,float rd1,float rd2):
             PowerSwitch(),
             In_1 (in1),
             In_2 (in2),
             Fr_Stby(frStdby),
             V_REF(vref), 
             R_SENSE(rsense),
             R_D1(rd1),
             R_D2(rd2),
             CurrentSense1(sense1),
             CurrentSense2(sense2)
    {
             pinMode(In_1, OUTPUT);
             digitalWrite(In_1, LOW);
             pinMode(In_2, OUTPUT);
             digitalWrite(In_2, LOW);
             pinMode(Fr_Stby, OUTPUT);
             digitalWrite(Fr_Stby, LOW);
    }
 
    /** Destructor
    */
    virtual ~VPS2535H() {}
  
    /*** Interface Methods ***/
    virtual int init(void *init_struct);
    virtual int close(void);

    /* Getting the ID of the component */
    virtual int read_id(uint8_t *id) {
        (void)id;
        return (int) 235;
    }

    /* Provide Ch current w/o checking status of convertion */
    virtual float get_current(int Ch);

    /* Provide Ch current Value with status of convertion */
    IPS_StatusTypeDef VPS2535H_get_secure_current_sense(IPS_HandleTypeDef *hips);

 
protected:
    IPS_StatusTypeDef VPS2535H_close(void);
    IPS_StatusTypeDef VPS2535H_init(void);
    IPS_StatusTypeDef VPS2535H_get_sense_channel_diagnostic(IPS_HandleTypeDef *);
 
private:
    const float V_REF;      // Reference voltage for V-sense measurement
    const float R_SENSE;    // R-sense value depending on resistor connected to V-sense  output
    const float R_D1;       // R_D1 upper divisor partitor resistor (=R6 in schematic)
    const float R_D2;       // R_D2 lower divisor partitor resistor (=R7 in schematic)
    int CurrentSense1;      // V-Sense Output from Ch1
    int CurrentSense2;      // V-Sense Output  from Ch2
};
#endif /* __VPS2535H_CLASS_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
 