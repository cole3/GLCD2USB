/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */
#define GLCD_CTRL_RS_Pin GPIO_PIN_13
#define GLCD_CTRL_RS GPIO_PIN_13
#define GLCD_CTRL_RS_GPIO_Port GPIOC
#define GLCD_CTRL_RW_Pin GPIO_PIN_14
#define GLCD_CTRL_RW GPIO_PIN_14
#define GLCD_CTRL_RW_GPIO_Port GPIOC
#define GLCD_CTRL_E_Pin GPIO_PIN_15
#define GLCD_CTRL_E GPIO_PIN_15
#define GLCD_CTRL_E_GPIO_Port GPIOC
#define GLCD_DATA_PORT GPIOA
#define GLCD_DATA_PIN GPIOA
#define GLCD_DATA_0_Pin GPIO_PIN_0
#define GLCD_DATA_0_GPIO_Port GPIOA
#define GLCD_DATA_1_Pin GPIO_PIN_1
#define GLCD_DATA_1_GPIO_Port GPIOA
#define GLCD_DATA_2_Pin GPIO_PIN_2
#define GLCD_DATA_2_GPIO_Port GPIOA
#define GLCD_DATA_3_Pin GPIO_PIN_3
#define GLCD_DATA_3_GPIO_Port GPIOA
#define GLCD_DATA_4_Pin GPIO_PIN_4
#define GLCD_DATA_4_GPIO_Port GPIOA
#define GLCD_DATA_5_Pin GPIO_PIN_5
#define GLCD_DATA_5_GPIO_Port GPIOA
#define GLCD_DATA_6_Pin GPIO_PIN_6
#define GLCD_DATA_6_GPIO_Port GPIOA
#define GLCD_DATA_7_Pin GPIO_PIN_7
#define GLCD_DATA_7_GPIO_Port GPIOA
#define GLCD_CTRL_CS0_Pin GPIO_PIN_0
#define GLCD_CTRL_CS0 GPIO_PIN_0
#define GLCD_CTRL_CS0_GPIO_Port GPIOB
#define GLCD_CTRL_CS1_Pin GPIO_PIN_1
#define GLCD_CTRL_CS1 GPIO_PIN_1
#define GLCD_CTRL_CS1_GPIO_Port GPIOB
#define GLCD_CTRL_RESET_Pin GPIO_PIN_10
#define GLCD_CTRL_RESET GPIO_PIN_10
#define GLCD_CTRL_RESET_GPIO_Port GPIOB

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
