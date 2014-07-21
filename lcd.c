#include "derivative.h"
#include "lcd.h"

void openlcd(void)
{
	LCD_DIR = 0xFF; /* configure LCD_DAT port for output */
	delay_1ms(100); /* Wait for LCD to be ready */
	put2lcd(0x28,CMD); /* set 4-bit data, 2-line display, 5x7 font */
	put2lcd(0x0F,CMD); /* turn on display, cursor, blinking */
	put2lcd(0x06,CMD); /* move cursor right */
	put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */
}

void puts2lcd (char *ptr)
{
	while (*ptr) { /* While character to send */
		put2lcd(*ptr,DATA); /* Write data to LCD */
		delay_50us(1); /* Wait for data to be written */
		ptr++; /* Go to next character */
	}
}


void put2lcd(char c, char type)
{
	char c_lo, c_hi;
	c_hi = (c & 0xF0) >> 2; /* Upper 4 bits of c */
	c_lo = (c & 0x0F) << 2; /* Lower 4 bits of c */
	
	if (type == DATA) LCD_DAT |= LCD_RS; /* select LCD data register */
	else LCD_DAT &= (~LCD_RS); /* select LCD command register */

	if (type == DATA)
		LCD_DAT = c_hi|LCD_E|LCD_RS; /* output upper 4 bits, E, RS high */
	else
	LCD_DAT = c_hi|LCD_E; /* output upper 4 bits, E, RS low */
	LCD_DAT |= LCD_E; /* pull E signal to high */
	
	__asm(nop); /* Lengthen E */
	__asm(nop);
	__asm(nop);
	
	LCD_DAT &= (~LCD_E); /* pull E to low */
	
	if (type == DATA)
		LCD_DAT = c_lo|LCD_E|LCD_RS; /* output lower 4 bits, E, RS high */
	else
		LCD_DAT = c_lo|LCD_E; /* output lower 4 bits, E, RS low */

	LCD_DAT |= LCD_E; /* pull E to high */
	
	__asm(nop); /* Lengthen E */
	__asm(nop);
	__asm(nop);

	LCD_DAT &= (~LCD_E); /* pull E to low */
	delay_50us(1); /* Wait for command to execute */
}

#define D50US 133 /* Inner loop takes 9 cycles; need 50x24 = 1200 cycles */
void delay_50us(int n)
{
	volatile int c;
	for (;n>0;n--)
	for (c=D50US;c>0;c--) ;
}


void delay_1ms(int n)
{
	for (;n>0;n--) delay_50us(200);
}

void clear(void) {
   char* maruf = "                     ";
   
   puts2lcd(maruf);
   puts2lcd(maruf);
   
  
}
