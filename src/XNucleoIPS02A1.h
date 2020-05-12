/**
 *******************************************************************************
 * @file    XNucleoIPS02A1.h
 * @author  ADG
 * @version V1.0.0
 * @date    08-May-2020
 * @brief   Header file for the X-NUCLEO-IPS02A1 expansion board
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

#ifndef __X_NUCLEO_IPS02A1_H
#define __X_NUCLEO_IPS02A1_H


/* Includes ------------------------------------------------------------------*/

#include "VPS2535H.h"


/* Classes -------------------------------------------------------------------*/

/** Class X_NUCLEO_IPS02A1 is intended to represent the intelligent power switch 
 *  Nucleo Expansion Board with the same name.
 *
 *  The expansion board is featuring basically of:\n
 *  -# a VPS2535H power switch\n
 *
 * It is intentionally implemented as a singleton because only one
 * XNucleoIPS02A1 at a time might be deployed in a HW component stack.\n
 * In order to get the singleton instance you have to call class method `Instance()`, 
 * e.g.:
 * @code
 * // Intelligent Power Switch expansion board singleton instance
 * static XNucleoIPS02A1 *<TODO>_expansion_board = XNucleoIPS02A1::instance();
 * @endcode
 */

class XNucleoIPS02A1
{
 public:
	 /**
	 * @brief     Get singleton instance
	 * @return    a pointer to the initialized singleton instance of class X_NUCLEO_IPS02A1
	 * @param[in] none
	 */
	static XNucleoIPS02A1& instance (int in1, int in2, int frstdby,
		int sense1, int sense2, float vref, float rsense, float rd1, float rd2);

	/**
	 * @brief    get current measurement from singleton's power switch
	 * @retval   *hips contain status of the operation
	 * param[in] Channel number: CHANNEL_1 or CHANNEL_2
	 */
    float get_current(int ch);

	/**
	 * Power switch.
	 */
	VPS2535H &vps2535h;


protected:
    /**
     * Constructor.
     */
	XNucleoIPS02A1(int in1, int in2, int frstdby,
             int sense1, int sense2, float vref,float rsense,float rd1,float rd2);

	/**
	 * @brief  Initialize the singleton's power switch to default settings
	 * @retval true if initialization successful, 
	 * @retval false otherwise
	 */
	bool init(void) {
		return (init_VPS2535H());
	}       

	/**
	 * @brief  Initialize the singleton's power switch
	 * @retval true if initialization successful, 
	 * @retval false otherwise
	 */
	bool init_VPS2535H(void);


 private:
	/**
	 * Singleton instance of class XNucleoIPS02A1.
	 */
	static XNucleoIPS02A1 *_instance;
};

#endif /* __X_NUCLEO_IPS02A1_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
