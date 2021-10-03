#define LCD_DATA_PORT PORTD
#define LCD_DATA_DDR DDRD

#define LCD_D7 6
#define LCD_D6 3
#define LCD_D5 4
#define LCD_D4 5

#define LCD_RSPORT PORTB
#define LCD_RSDDR DDRB
#define LCD_RS 4

#define LCD_RWPORT PORTB
#define LCD_RWDDR DDRB
#define LCD_RW 1

#define LCD_ENPORT PORTB
#define LCD_ENDDR DDRB
#define LCD_EN 3


// RS PIN
#define RS_HIGH LCD_RSPORT |= (1<<LCD_RS)
#define RS_LOW LCD_RSPORT &= ~(1<<LCD_RS)
// EN PIN
#define EN_HIGH LCD_ENPORT |= (1<<LCD_EN)
#define EN_LOW LCD_ENPORT &= ~(1<<LCD_EN)


void lcd_byte(unsigned char data);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_clear(void);
void lcd_init(void);
void lcd_str(char * str);
void lcd_int(signed short num);
void lcd_cursor(unsigned char y, unsigned char x);
void lcd_define_character(unsigned char addr, const unsigned char *tab_pointer);

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
