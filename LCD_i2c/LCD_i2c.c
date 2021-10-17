/*
*
*	https://mcinm.pl
*
*/
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
#include "LCD_i2c.h"
unsigned char conf=0;



void pcf_send(unsigned char byte)
{
	I2C_start();
	I2C_write(lcd_write_address);
	I2C_write(byte);
	I2C_stop();
}


void EN_LOW(void)
{

	conf &= ~(LCD_EN);
	pcf_send(conf);

}

void EN_HIGH(void)
{
	conf |= LCD_EN;
	pcf_send(conf);
}

void RS_LOW(void)
{
	conf &= ~(LCD_RS);
	pcf_send(conf);
}

void RS_HIGH(void)
{
	conf |= LCD_RS;
	pcf_send(conf);
}


// Wysyłanie komendy do wyświetlacza
void lcd_cmd(uint8_t cmd)
{
	RS_LOW(); // RS - niskie w przypadku wysyłania komend
	lcd_byte(cmd);
}

// Wysyłanie danych do wyświetlacza
void lcd_data(uint8_t data)
{
	RS_HIGH(); // RS - wysokie w przypadku wysyłania danych
	lcd_byte(data);
}

// Send 4 bits
static inline void lcd_send_4bits(unsigned char data)
{
  if (data&(1<<0)) conf |= (LCD_D4);
  else conf &= ~(LCD_D4);
  
  if (data&(1<<1)) conf |= (LCD_D5);
	else conf &= ~(LCD_D5);
	
	if (data&(1<<2)) conf |= (LCD_D6);
	else conf &= ~(LCD_D6);
	
	if (data&(1<<3)) conf |= (LCD_D7);
	else conf &= ~(LCD_D7);
	pcf_send(conf);
}


void lcd_byte(uint8_t byte)
{
	EN_HIGH();
	lcd_send_4bits(byte>>4); // Wpierw wysyłana jest starsza połowa bajtu
	EN_LOW();
	
	EN_HIGH();
	lcd_send_4bits(byte); // Wysłanie młodszej połowy bajtu
	EN_LOW();
	
	_delay_us(120);	
}

void lcd_init(void)
{	
	_delay_ms(15);
	
	EN_HIGH();
	lcd_send_4bits(0x03);
	EN_LOW();
	_delay_ms(4.1);
	EN_HIGH();
	lcd_send_4bits(0x03);
	EN_LOW();
	_delay_us(100);
	EN_HIGH();
	lcd_send_4bits(0x03);
	EN_LOW();
	_delay_us(100);
	EN_HIGH();
	lcd_send_4bits(0x02);
	EN_LOW();
	_delay_us(100);
	
	lcd_cmd( LCDC_FUNC|LCDC_FUNC4B|LCDC_FUNC2L|LCDC_FUNC5x7 );
	lcd_cmd( LCDC_ONOFF|LCDC_CURSOROFF );
	lcd_cmd( LCDC_ONOFF|LCDC_DISPLAYON );
	lcd_cmd( LCDC_ENTRY|LCDC_ENTRYR );

	lcd_clear();
}

void lcd_clear(void)
{
	lcd_cmd(0x01);
	_delay_ms(1);
}


void lcd_locate(uint8_t y, uint8_t x)
{
	uint8_t xy = y+x * 0x40;
	lcd_cmd((xy | 0x80));
}

void lcd_str(char * str)
{
	while (*str) lcd_data(*str++);
}

void lcd_int(uint16_t digit)
{
	char buff[4];
	itoa(digit, buff, 10);
	lcd_str(buff);
}

void lcd_define_character(uint8_t adres, const uint8_t *tab_pointer)
{
	lcd_cmd(0x40 | ((adres & 0x7) << 3));
	for (uint8_t i=0; i<8; i++) lcd_data(tab_pointer[i]);
	//for (uint8_t i=0; i<8; i++) lcd_data(pgm_read_byte(&tab_pointer[i]));
	lcd_cmd(0x80);
}
