#ifndef __LCD_H
#define __LCD_H		
//#include "sys.h"	 
#include "main.h"
#include "stdlib.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {										    
	u16  width;
	u16  height;
	u16  id;
	u8   dir;
	u16	 wramcmd;
	u16  setxcmd;
	u16  setycmd;
} _lcd_dev; 	

extern _lcd_dev lcddev;

//#define USE_HORIZONTAL  	1
//#define LCD_USE8BIT_MODEL   1
#if USE_HORIZONTAL==1
#define LCD_W 64
#define LCD_H 128
#else
#define LCD_W 128
#define LCD_H 64
#endif

extern u16  POINT_COLOR;
extern u16  BACK_COLOR;

#define	LCD_CS_SET   HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET)
#define	LCD_RS_SET   HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_SET)
#define	LCD_WR_SET   HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_SET)
#define	LCD_RD_SET	 HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_SET)
#define	LCD_RST_SET	 HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_SET)
								    
#define	LCD_CS_CLR   HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET)
#define	LCD_RS_CLR   HAL_GPIO_WritePin(LCD_RS_GPIO_Port, LCD_RS_Pin, GPIO_PIN_RESET)
#define	LCD_WR_CLR   HAL_GPIO_WritePin(LCD_WR_GPIO_Port, LCD_WR_Pin, GPIO_PIN_RESET)
#define	LCD_RD_CLR   HAL_GPIO_WritePin(LCD_RD_GPIO_Port, LCD_RD_Pin, GPIO_PIN_RESET)
#define	LCD_RST_CLR  HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, GPIO_PIN_RESET)

#define DATAOUT(x) GPIOA->ODR=x;
#define DATAIN     GPIOA->IDR;

// direct
#define L2R_U2D  0
#define L2R_D2U  1
#define R2L_U2D  2
#define R2L_D2U  3
#define U2D_L2R  4
#define U2D_R2L  5
#define D2U_L2R  6
#define D2U_R2L  7
#define DFT_SCAN_DIR  L2R_U2D


#define WHITE       0xFFFF
#define BLACK      	0x0000	  
#define BLUE       	0x001F  
#define BRED        0xF81F
#define GRED 	 	0xFFE0
#define GBLUE	 	0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN 	    0xBC40 
#define BRRED 		0xFC07
#define GRAY  		0x8430
#define DARKBLUE    0x01CF
#define LIGHTBLUE   0x7D7C
#define GRAYBLUE    0x5458
#define LIGHTGREEN  0x841F
#define LIGHTGRAY   0xEF5B
#define LGRAY 		0xC618
#define LGRAYBLUE   0xA651
#define LBBLUE      0x2B12
	    															  
extern u16 BACK_COLOR, POINT_COLOR ;  

void lcd_init(void);
void lcd_clear(u16 color);	 
void lcd_set_cursor(u16 x, u16 y);
void lcd_draw_point(u16 x, u16 y);
u16  lcd_read_point(u16 x, u16 y);
void lcd_draw_line(u16 x0, u16 y0, u16 x1, u16 y1);
void lcd_draw_rectangle(u16 x0, u16 y0, u16 x1, u16 y1);		   
void lcd_set_windows(u16 x0, u16 y0,u16 x1,u16 y1);
void lcd_draw_point_16bit(u16 color);
u16 lcd_read_data(void);
void lcd_direction(u8 direction);
void lcd_write_full_data(u16 color, u8 *bitmap);


// register
#define R0             0x00
#define R1             0x01
#define R2             0x02
#define R3             0x03
#define R4             0x04
#define R5             0x05
#define R6             0x06
#define R7             0x07
#define R8             0x08
#define R9             0x09
#define R10            0x0A
#define R12            0x0C
#define R13            0x0D
#define R14            0x0E
#define R15            0x0F
#define R16            0x10
#define R17            0x11
#define R18            0x12
#define R19            0x13
#define R20            0x14
#define R21            0x15
#define R22            0x16
#define R23            0x17
#define R24            0x18
#define R25            0x19
#define R26            0x1A
#define R27            0x1B
#define R28            0x1C
#define R29            0x1D
#define R30            0x1E
#define R31            0x1F
#define R32            0x20
#define R33            0x21
#define R34            0x22
#define R36            0x24
#define R37            0x25
#define R40            0x28
#define R41            0x29
#define R43            0x2B
#define R45            0x2D
#define R48            0x30
#define R49            0x31
#define R50            0x32
#define R51            0x33
#define R52            0x34
#define R53            0x35
#define R54            0x36
#define R55            0x37
#define R56            0x38
#define R57            0x39
#define R59            0x3B
#define R60            0x3C
#define R61            0x3D
#define R62            0x3E
#define R63            0x3F
#define R64            0x40
#define R65            0x41
#define R66            0x42
#define R67            0x43
#define R68            0x44
#define R69            0x45
#define R70            0x46
#define R71            0x47
#define R72            0x48
#define R73            0x49
#define R74            0x4A
#define R75            0x4B
#define R76            0x4C
#define R77            0x4D
#define R78            0x4E
#define R79            0x4F
#define R80            0x50
#define R81            0x51
#define R82            0x52
#define R83            0x53
#define R96            0x60
#define R97            0x61
#define R106           0x6A
#define R118           0x76
#define R128           0x80
#define R129           0x81
#define R130           0x82
#define R131           0x83
#define R132           0x84
#define R133           0x85
#define R134           0x86
#define R135           0x87
#define R136           0x88
#define R137           0x89
#define R139           0x8B
#define R140           0x8C
#define R141           0x8D
#define R143           0x8F
#define R144           0x90
#define R145           0x91
#define R146           0x92
#define R147           0x93
#define R148           0x94
#define R149           0x95
#define R150           0x96
#define R151           0x97
#define R152           0x98
#define R153           0x99
#define R154           0x9A
#define R157           0x9D
#define R192           0xC0
#define R193           0xC1
#define R229           0xE5							  		 
#endif  
	 
	 



