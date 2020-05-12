/**
 *******************************************************************************
 * @file    IPS.c
 * @author  ADG
 * @version V1.0.0
 * @date    08-May-2020
 * @brief   IPS (Intelligent Power Switch) module driver common interface.
 *
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
#ifndef __IPS_H
#define __IPS_H

#include <stdint.h>

 
/* Exported types ------------------------------------------------------------*/ 
  
/** 
  * @brief IPS Init Structure definition  
  */ 

typedef struct
{
  uint32_t Init;              /* Inserted for sake of generality */ 
}IPS_InitTypeDef;

/** 
  * @brief IPS  State structures definition  
  */ 
typedef enum
{
  IPS_SUCCESS          = 0x00,    /*!< No error */
  IPS_FAIL             = 0x01,    /*!< Error    */ 
  IPS_WRONG_CHANNEL    = 0x02,    /*!< Wrong IPS channel selected */
 }IPS_StatusTypeDef;

/** 
  * @brief IPS I/O error type structures definition  
  */ 
 typedef enum
{
  IPS_IO_SUCCESS         = 0x00,    /*!< No error */
  IPS_IO_FAIL            = 0x01,    /*!< Error    */
  IPS_ADC_INIT_FAILED    = 0x02,    /*!< ADC Init failed */
  IPS_ADC_CAL_FAILED     = 0x03,    /*!< ADC Calibration failed */
  IPS_ADC_CONF_CH_FAILED = 0x04,    /*!< ADC Configure Channel  failed */
  IPS_ADC_START_FAILED   = 0x05,    /*!< ADC Start Conversion failed */
  IPS_ADC_STOP_FAILED    = 0x06,    /*!< ADC Stop Conversion failed */
  IPS_ADC_STATE_FAILED   = 0x07,    /*!< ADC Get State failed */
  IPS_ADC_POLL_FAILED    = 0x08     /*!< ADC Poll for conversion failed */
}IO_ErrorType;

/** 
  * @brief  IPS handle Structure definition  
  */  
typedef struct
{
  uint8_t                       ipsChannel;          /* IPS channel to get sense measurement*/
  IPS_StatusTypeDef             Status;              /* IPS Status   */
  IO_ErrorType                  IO_Status;           /* IO Status */
  float                         SenseRawValue;       /* V-Sense raw value */  
  float                         GNDSenseRawValue;    /* GND Value */  
  float                         TemperatureValue;    /* Chip Temperature */
  float                         VccValue;            /* Vcc Value */
  float                         IValue;              /* Current Value */
}IPS_HandleTypeDef;

/**
 * @brief  IPS component id enumerator definition
 */
typedef enum
{
  IPS_NONE_COMPONENT = 0,
  ISP_VPS2535H_COMPONENT = 1
} IPS_ComponentTypeDef;

/**
 * @brief  IPS driver extended structure definition
 */
typedef struct
{
  IPS_ComponentTypeDef
  id; /* This id must be unique for each component belonging to this class that wants to extend common class */
  void *pData; /* This pointer is specific for each component */
} IPS_DrvExtTypeDef;

/** 
  * @brief  Intelligent Power Switch driver structure definition  
  */ 
typedef struct
{  
  IPS_StatusTypeDef            (*Init)(IPS_HandleTypeDef *);
  IPS_StatusTypeDef            (*Close)(void);
  IPS_StatusTypeDef            (*ConfigureMuxChannel)(uint8_t, uint8_t);
  IPS_StatusTypeDef            (*GetSenseChannelDiagnostic)(IPS_HandleTypeDef *);
  IPS_StatusTypeDef            (*GetTemperatureChipSense)(IPS_HandleTypeDef *);     
  IPS_StatusTypeDef            (*GetVccSense)(IPS_HandleTypeDef *hips);  
  IPS_StatusTypeDef            (*GetCurrentSense)(IPS_HandleTypeDef *hips);
  IPS_DrvExtTypeDef            *extData;
}IPS_DrvTypeDef;
                                
#endif /* __IPS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/   

