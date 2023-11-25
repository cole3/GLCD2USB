#include "st7735.h"
#include "stdlib.h"
//#include "usart.h"
//#include "delay.h"	 

_lcd_dev lcddev;

u16 POINT_COLOR = 0x0000, BACK_COLOR = 0xFFFF;  
u16 DeviceCode;	 


void delay_ms(unsigned int ms)
{
    volatile int i;
    while (ms--) {
        for (i = 0; i < 800; i++);
    }
}

static void lcd_write_reg(u8 data)
{ 
	LCD_RS_CLR;
 	LCD_CS_CLR; 
	DATAOUT(data); 
	LCD_WR_CLR; 
	LCD_WR_SET; 
 	LCD_CS_SET; 	
}

static void lcd_write_data(u16 data)
{
	LCD_RS_SET;
	LCD_CS_CLR;
	DATAOUT(data);
	LCD_WR_CLR;
	LCD_WR_SET;
	LCD_CS_SET;

}

static void lcd_drawpoint_16bit(u16 color)
{
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;
	DATAOUT(color >> 8);	
	LCD_WR_CLR;
	LCD_WR_SET;	
	DATAOUT(color);	
	LCD_WR_CLR;
	LCD_WR_SET;	 
	LCD_CS_SET;
}

void lcd_register_write(u8 LCD_Reg, u16 LCD_RegValue)
{	
	lcd_write_reg(LCD_Reg);  
	lcd_write_data(LCD_RegValue);	    		 
}	   

void lcd_write_ram_prepare(void)
{
	lcd_write_reg(lcddev.wramcmd);
}	 

void lcd_draw_point(u16 x, u16 y)
{
	lcd_set_cursor(x,y);
#if LCD_USE8BIT_MODEL==1
	LCD_CS_CLR;
	LCD_RD_SET;
	LCD_RS_SET;
	DATAOUT(POINT_COLOR>>8);	
	LCD_WR_CLR;
	LCD_WR_SET;	
	DATAOUT(POINT_COLOR);	
	LCD_WR_CLR;
	LCD_WR_SET;	 
	LCD_CS_SET;
#else
	lcd_write_data(POINT_COLOR); 
#endif
}

void lcd_clear(u16 color)
{
	u32 i=0;      
	//lcd_set_windows(0, 0, lcddev.width - 1, lcddev.height - 1);	
	lcd_set_windows(0, 0, (lcddev.width - 1), (lcddev.height - 1));
#if LCD_USE8BIT_MODEL==1
	LCD_RS_SET;
	LCD_CS_CLR;	   
	for (i = 0; i < lcddev.width * lcddev.height; i++) {
		DATAOUT(color >> 8);	
		LCD_WR_CLR;
		LCD_WR_SET;	
		
		DATAOUT(color);	
		LCD_WR_CLR;
		LCD_WR_SET;	   
	}
	LCD_CS_SET;	
#else
    for (i = 0; i < lcddev.width * lcddev.height; i++) {
        lcd_drawpoint_16bit(color);
	}
#endif
} 

void lcd_set_param(void)
{ 
	lcddev.setxcmd = 0x2A;
	lcddev.setycmd = 0x2B;
	lcddev.wramcmd = 0x2C;
#if USE_HORIZONTAL==1
	lcddev.dir=1;
	lcddev.width = 64;
	lcddev.height = 128;			
	lcd_register_write(0x36, (1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
#else
	lcddev.dir = 0;
	lcddev.width = 128;
	lcddev.height = 64;
	lcd_register_write(0x36, (1<<3)|(1<<6)|(1<<7)); //BGR==1,MY==1,MX==1,MV==0
#endif
}	  

void lcd_reset(void)
{
	LCD_RST_SET;
	delay_ms(200);
	LCD_RST_CLR;
	delay_ms(800);	
	LCD_RST_SET;
	delay_ms(800);
}
 	 
void lcd_init(void)
{  									 
	//************* Start Initial Sequence **********//
	lcd_reset();
	
    lcd_write_reg(0x11); //Exit Sleep   
    delay_ms(120);   
	
	lcd_write_reg(0x28); // Display Off

	lcd_write_reg(0x26); //Set Default Gamma 
	lcd_write_data(0x01); 
	
#if 0
	lcd_write_reg(0xB1);//Set Frame Rate 
	lcd_write_data(0x0e); 
	lcd_write_data(0x14); 
	
	lcd_write_reg(0xC0); //Set VRH1[4:0] & VC[2:0] for VCI1 & G
	lcd_write_data(0x08); 
	lcd_write_data(0x05); 
	
	lcd_write_reg(0xC1); //Set BT[2:0] for AVDD & VCL & VGH &
	lcd_write_data(0x02); 
	
	lcd_write_reg(0xC5); //Set VMH[6:0] & VML[6:0] for VOMH &
	lcd_write_data(0x44); 
	lcd_write_data(0x48); 
	
	lcd_write_reg(0xC7);// Set VMF 
	lcd_write_data(0xC2); 
#endif
	
	lcd_write_reg(0x3a); //Set Color Format 
	lcd_write_data(0x05); 
	
#if 0
	lcd_write_reg(0x2A); //Set Column Address 
	lcd_write_data(0x00); 
	lcd_write_data(0x00); 
	lcd_write_data(0x00); 
	lcd_write_data(0x7F); 
	
	lcd_write_reg(0x2B); //Set Page Address 
	lcd_write_data(0x00);  
	lcd_write_data(0x00);  
	lcd_write_data(0x00);  
	lcd_write_data(0x3F); 
	
	lcd_write_reg(0xB4); 
	lcd_write_data(0x00); 
	
	lcd_write_reg(0xf2); //Enable Gamma b
	lcd_write_data(0x01); 
	
	lcd_write_reg(0x36); 
	lcd_write_data(0x48); 
	
	lcd_write_reg(0xE0); 
	lcd_write_data(0x3F);//p1 
	lcd_write_data(0x26);//p2 
	lcd_write_data(0x23);//p3 
	lcd_write_data(0x30);//p4 
	lcd_write_data(0x28);//p5 
	lcd_write_data(0x10);//p6 
	lcd_write_data(0x55);//p7 
	lcd_write_data(0xB7);//p8 
	lcd_write_data(0x40);//p9 
	lcd_write_data(0x19);//p10 
	lcd_write_data(0x10);//p11 
	lcd_write_data(0x1E);//p12 
	lcd_write_data(0x02);//p13 
	lcd_write_data(0x01);//p14 
	lcd_write_data(0x00);//p15 
	
	lcd_write_reg(0xE1); 
	lcd_write_data(0x00);//p1 
	lcd_write_data(0x19);//p2 
	lcd_write_data(0x1C);//p3 
	lcd_write_data(0x0F);//p4 
	lcd_write_data(0x14);//p5 
	lcd_write_data(0x0F);//p6 
	lcd_write_data(0x2A);//p7 
	lcd_write_data(0x48);//p8 
	lcd_write_data(0x3F);//p9 
	lcd_write_data(0x06);//p10 
	lcd_write_data(0x1D);//p11 
	lcd_write_data(0x21);//p12 
	lcd_write_data(0x3d);//p13 
	lcd_write_data(0x3e);//p14 
	lcd_write_data(0x3f);//p15 
	
#endif
	lcd_set_param();
	lcd_clear(WHITE);
	lcd_write_reg(0x29); // Display On  
}

void lcd_set_windows(u16 x0, u16 y0, u16 x1, u16 y1)
{	
	lcd_write_reg(lcddev.setxcmd);	
	lcd_write_data(x0 >> 8);
	lcd_write_data(0x00FF & x0);		
	lcd_write_data(x1 >> 8);
	lcd_write_data(0x00FF & x1);

	lcd_write_reg(lcddev.setycmd);	
	lcd_write_data(y0 >> 8);
	lcd_write_data(0x00FF & (y0 + 48));
	lcd_write_data(y1 >> 8);
	lcd_write_data(0x00FF & (y1 + 48));

	lcd_write_ram_prepare();
}   

void lcd_set_cursor(u16 x, u16 y)
{	  	    			
	lcd_write_reg(lcddev.setxcmd);	
	lcd_write_data(x >> 8);
	lcd_write_data(0x00FF & x);		
	lcd_write_data(0x0001);
	lcd_write_data(0x003F);
	
	lcd_write_reg(lcddev.setycmd);	
	lcd_write_data(y >> 8);
	lcd_write_data(0x00FF & y);		
	lcd_write_data(0x0001);
	lcd_write_data(0x00Df);
	lcd_write_ram_prepare();
} 

#if 0
void lcd_direction(u8 direction)
{ 
    switch(direction){
        case 0:
            lcddev.width = 320;
            lcddev.height = 480;	
            lcd_register_write(0x36,(1<<3)|(0<<6)|(0<<7));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 1:
            lcddev.width = 480;
            lcddev.height = 320;
            lcd_register_write(0x36, (1<<3)|(0<<7)|(1<<6)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
            break;
        case 2:
            lcddev.width = 320;
            lcddev.height = 480;
            lcd_register_write(0x36, (1<<3)|(1<<6)|(1<<7));//BGR==1,MY==0,MX==0,MV==0
            break;
        case 3:
            lcddev.width = 480;
            lcddev.height = 320;
            lcd_register_write(0x36, (1<<3)|(1<<7)|(1<<5));//BGR==1,MY==1,MX==0,MV==1
            break;
        default:
            break;
	}
}	  
#endif

void lcd_write_full_data(u16 color, u8 *bitmap)
{
	u32 i = 0;
    u32 j = 0;
    u32 k = 0;
	lcd_set_windows(0, 0, (lcddev.width - 1), (lcddev.height - 1));

    for (i = 0; i < 8; i++) {
        for (k = 0; k < 8; k++) {
            for (j = 0; j < 128; j++) {
                if (bitmap[i*128 + j] & (1 << k))
                    lcd_drawpoint_16bit(color);
                else
                    lcd_drawpoint_16bit(BLACK);
            }
        }
    }
} 

