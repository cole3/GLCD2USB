/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v2.0_Cube
  * @brief          : USB Device Custom HID interface file.
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

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */
#define GLCD2USB_RID_GET_INFO      1    /* get display info */
#define GLCD2USB_RID_SET_ALLOC     2    /* allocate/free display */
#define GLCD2USB_RID_GET_BUTTONS   3    /* get state of the four buttons */
#define GLCD2USB_RID_SET_BL        4    /* set backlight brightness */
#define GLCD2USB_RID_GET_IR        5    /* get last ir message */
#define GLCD2USB_RID_WRITE         8    /* write some bitmap data to the display */
#define GLCD2USB_RID_WRITE_4       (GLCD2USB_RID_WRITE+0)
#define GLCD2USB_RID_WRITE_8       (GLCD2USB_RID_WRITE+1)
#define GLCD2USB_RID_WRITE_16      (GLCD2USB_RID_WRITE+2)
#define GLCD2USB_RID_WRITE_32      (GLCD2USB_RID_WRITE+3)
#define GLCD2USB_RID_WRITE_64      (GLCD2USB_RID_WRITE+4)
#define GLCD2USB_RID_WRITE_128     (GLCD2USB_RID_WRITE+5)

typedef struct {
    unsigned char report_id;
    char name[32];
    unsigned short width, height;
    unsigned char flags;
} __attribute__ ((packed)) display_info_t;

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
    0x06, 0x00, 0xff,              // USAGE_PAGE (Vendor specific)^M
    0x09, 0x01,                    // USAGE (Vendor Usage 1)^M
    0xa1, 0x01,                    // COLLECTION (Application)^M
    0x15, 0x00,                    //   LOGICAL_MINIMUM (0)^M
    0x26, 0xff, 0x00,              //   LOGICAL_MAXIMUM (255)^M
    0x75, 0x08,                    //   REPORT_SIZE (8)^M

    0x85, GLCD2USB_RID_GET_INFO,   //   REPORT_ID^M
    0x95, sizeof(display_info_t)-1,//   REPORT_COUNT^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_SET_ALLOC,  //   REPORT_ID^M
    0x95, 1,                       //   REPORT_COUNT (1)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_GET_BUTTONS,//   REPORT_ID^M
    0x95, 1,                       //   REPORT_COUNT (1)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_SET_BL,     //   REPORT_ID^M
    0x95, 1,                       //   REPORT_COUNT (1)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_WRITE_4,    //   REPORT_ID^M
    0x95, 4+3,                     //   REPORT_COUNT (7)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_WRITE_8,    //   REPORT_ID^M
    0x95, 8+3,                     //   REPORT_COUNT (11)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_WRITE_16,   //   REPORT_ID^M
    0x95, 16+3,                    //   REPORT_COUNT (19)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_WRITE_32,   //   REPORT_ID^M
    0x95, 32+3,                    //   REPORT_COUNT (35)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_WRITE_64,   //   REPORT_ID^M
    0x95, 64+3,                    //   REPORT_COUNT (67)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

    0x85, GLCD2USB_RID_WRITE_128,  //   REPORT_ID^M
    0x95, 128+3,                   //   REPORT_COUNT (131)^M
    0x09, 0x00,                    //   USAGE (Undefined)^M
    0xb2, 0x02, 0x01,              //   FEATURE (Data,Var,Abs,Buf)^M

  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

extern void print(char* fmt, ...);
extern uint8_t fb[940];
extern uint8_t data_ready;
/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
    USBD_CUSTOM_HID_HandleTypeDef *hhid = (USBD_CUSTOM_HID_HandleTypeDef *)(hUsbDeviceFS.pClassData);

    if (hhid->ReportId == GLCD2USB_RID_WRITE) {
        uint16_t addr = hhid->Report_buf[1] + (uint16_t)256 * hhid->Report_buf[2];
        uint8_t row = addr / 128;
        uint8_t col = addr % 128;
        uint8_t size = hhid->Report_buf[3];
        uint8_t i;
        //print("GLCD2USB_RID_WRITE: %d (%d,%d) size %d\n", hhid->Report_buf[0], addr/128, addr%128, hhid->Report_buf[3]);
        data_ready = 1;
        for (i = 0; i < size; i++)
            fb[row * 128 + col + i] = hhid->Report_buf[4 + i];
    } else if (hhid->ReportId == GLCD2USB_RID_SET_ALLOC) {
        print("GLCD2USB_RID_SET_ALLOC: %d %d\n", hhid->Report_buf[0], hhid->Report_buf[1]);
    } else if (hhid->ReportId == GLCD2USB_RID_SET_BL) {
        print("GLCD2USB_RID_SET_BL: %d %d\n", hhid->Report_buf[0], hhid->Report_buf[1]);
    } else {
        print("OutEvent unknown: %d %d\n", hhid->Report_buf[0], hhid->Report_buf[1]);
    }
    return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

