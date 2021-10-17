/*
*
*	https://mcinm.pl
*
*/
#define LCD_RS 0x01
#define LCD_RW 0x02
#define LCD_EN 0x04

#define LCD_D4 0x10
#define LCD_D5 0x20
#define LCD_D6 0x40
#define LCD_D7 0x80
#define lcd_write_address 0x7e

#define LCDC_CLS					0x01
#define LCDC_HOME					0x02
#define LCDC_ENTRY					0x04
#define LCDC_ENTRYR					0x02
#define LCDC_ENTRYL					0
#define LCDC_MOVE					0x01
#define LCDC_ONOFF					0x08
#define LCDC_DISPLAYON				0x04
#define LCDC_CURSORON				0x02
#define LCDC_CURSOROFF				0
#define LCDC_BLINKON				0x01
#define LCDC_SHIFT					0x10
#define LCDC_SHIFTDISP				0x08
#define LCDC_SHIFTR					0x04
#define LCDC_SHIFTL					0
#define LCDC_FUNC					0x20
#define LCDC_FUNC8B					0x10
#define LCDC_FUNC4B					0
#define LCDC_FUNC2L					0x08
#define LCDC_FUNC1L					0
#define LCDC_FUNC5x10				0x04
#define LCDC_FUNC5x7				0
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80


#include "I2C_lib.h"





void pcf_send(unsigned char byte);
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t data);
void lcd_byte(uint8_t byte);
void lcd_init(void);
void lcd_locate(uint8_t y, uint8_t x);
void lcd_clear(void);
void lcd_define_character(uint8_t adres, const uint8_t *tab_pointer);
void lcd_str(char * str);
void lcd_int(uint16_t digit);
