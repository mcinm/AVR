#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "LCD.h"

// Send 4 bits
static inline void lcd_send_4bits(unsigned char data)
{
  if (data&(1<<0)) LCD_data_PORT |= (1<<LCD_D4);
  else LCD_DATA_PORT &= ~(1<<LCD_D4);
  
  if (data&(1<<1)) LCD_DATA_PORT |= (1<<LCD_D5);
	else LCD_DATA_PORT &= ~(1<<LCD_D5);
	
	if (data&(1<<2)) LCD_DATA_PORT |= (1<<LCD_D6);
	else LCD_DATA_PORT &= ~(1<<LCD_D6);
	
	if (data&(1<<3)) LCD_DATA_PORT |= (1<<LCD_D7);
	else LCD_DATA_PORT &= ~(1<<LCD_D7);
}

// Send byte - just send 4 bytes, 2 times
void lcd_byte(unsigned char data)
{
  EN_HIGH;
  lcd_send_4bits(data>>4);
  EN_LOW;
  
  EN_HIGH;
  lcd_send_4bits(data);
  EN_LOW;
  
  _delay_us(120);
}


// Send command
void lcd_cmd(unsigned char cmd)
{
  RS_LOW;
  lcd_byte(cmd);
}

// Send data
void lcd_data(unsigned char data)
{
  RS_HIGH;
  lcd_byte(data);
}

// Clear display
lcd_clear(void)
{
  lcd_cmd(0x01);
  _delay_ms(2);
}


// Init dispay
void lcd_init()
{
	lcd_init_pins();
	DDRB |= (1<<LCD_RS) | (1<<LCD_EN);
	
	LCD_RSPORT &= ~(1<<LCD_RS);
	LCD_ENPORT &= ~(1<<LCD_EN);
	
	_delay_ms(15);
	
	EN_HIGH;
	lcd_send_4bits(0x03);
	EN_LOW;
	_delay_ms(4.1);
	EN_HIGH;
	lcd_send_4bits(0x03)
	EN_LOW;
	_delay_us(100);
	EN_HIGH;
	lcd_send_4bits(0x03);
	EN_LOW;
	_delay_us(100);
	EN_HIGH;
	lcd_send_4bits(0x02);
	EN_LOW;
	_delay_us(100);
	
	lcd_cmd( LCDC_FUNC|LCDC_FUNC4B|LCDC_FUNC2L|LCDC_FUNC5x7 );
	lcd_cmd( LCDC_ONOFF|LCDC_CURSOROFF );
	lcd_cmd( LCDC_ONOFF|LCDC_DISPLAYON );
	lcd_cmd( LCDC_ENTRY|LCDC_ENTRYR );

	lcd_clear();
}


// Send string
void lcd_str(char * str)
{
  while (*str) lcd_data(*str++);
}

// Send digit/number
void lcd_int(signed short num)
{
  char buff[4];
  itoa(num, buff, 10);
  lcd_str(buff);
}

// Set cursor
void lcd_cursor(unsigned char y, unsigned char x)
{
  unsigned char xy = x+y * 0x40;
  lcd_cmd((xy | 0x80));
}

// Define own characters
void lcd_define_character(unsigned char addr, const unsigned char *tab_pointer)
{
  lcd_cmd(0x40 | ((addr & 0x7) << 3));
  for (unsigned char i=0; i<8; i++) lcd_data(&tab_pointer[i]); // Load from RAM
  //for (unsigned char i=0; i<8; i++) lcd_data(pgm_read_byte(&tab_pointer[i])); // Load from flash
  lcd_cmd(0x80);
}
