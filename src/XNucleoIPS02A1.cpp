/**
 ******************************************************************************
 * @file    XNucleoIPS02A1.cpp
 * @author  ADG
 * @version V1.0.0
 * @date    08-May-2020
 * @brief   Implementation file for the XNucleoIPS02A1 singleton class
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

#include "Arduino.h"
#include "XNucleoIPS02A1.h"


/* Static variables ----------------------------------------------------------*/

XNucleoIPS02A1* XNucleoIPS02A1::_instance = NULL;


/* Methods -------------------------------------------------------------------*/

/**
 * @brief  Constructor
 * @return    a pointer to the initialized singleton instance of class X_NUCLEO_IPS02A1
 * @param[in] in1, input1 Pin for the power switch
 * @param[in] in2, input1 Pin for the power switch
 * @param[in] frstdby ,stand-by Pin
 * @param[in] sense1 and sense2, outputs from Ch1 and Ch2
 * @param[in] vref, reference voltage
 * @param[in] rsense, sense resistor ouside of chip
 * @param[in] rd1, upper partitor resistor (=R6 in schematic) to protect ADC 
 * @param[in] rd1, lower partitor resistor (=R7 in schematic) to protect ADC
 */
 
XNucleoIPS02A1::XNucleoIPS02A1(int in1, int in2, int frstdby,
             int sense1, int sense2, float vref, float rsense, float rd1, float rd2) :
             vps2535h( *(new VPS2535H(in1, in2, frstdby, sense1, sense2, vref,rsense,rd1,rd2)))
{
}

/**
 * @brief     Get singleton instance
 * @return    a pointer to the initialized singleton instance of class XNucleoIPS02A1
 * @param[in] none
 */
XNucleoIPS02A1 &XNucleoIPS02A1::instance(int in1, int in2, int frstdby,
	int sense1, int sense2, float vref, float rsense, float rd1, float rd2) {
	if (_instance == NULL) {
		_instance = new XNucleoIPS02A1(in1,in2,frstdby,sense1,sense2,vref,rsense,rd1,rd2);

		if (_instance != NULL) {
			_instance->init();
		}
	}

	return (*_instance);
}

/**
 * @brief  Initialize the singleton's power switch
 * @retval true if initialization successful, 
 * @retval false otherwise
 */
bool XNucleoIPS02A1::init_VPS2535H(void) {
	vps2535h.init(NULL);
	return true;
}

 
/**
 * @brief    get current measurement from singleton's power switch
 * @retval   *hips contain status of the operation
 * param[in] Channel number: CHANNEL_1 or CHANNEL_2
 */
float  XNucleoIPS02A1::get_current(int ch){
	return vps2535h.get_current(ch);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

