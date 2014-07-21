#define LCD_DAT PORTK /* Port K drives LCD data pins, E, and RS */
#define LCD_DIR DDRK /* Direction of LCD port */
#define LCD_E 0x02 /* LCD E signal */
#define LCD_RS 0x01 /* LCD Register Select signal */
#define CMD 0 /* Command type for put2lcd */
#define DATA 1 /* Data type for put2lcd */


/* Prototypes for functions in lcd.c */
void openlcd(void); /* Initialize LCD display */
void put2lcd(char c, char type); /* Write command or data to LCD controller */
void puts2lcd (char *ptr); /* Write a string to the LCD display */
void delay_50us(int n); /* Delay n 50 microsecond intervals */
void delay_1ms(int n); /* Delay n 1 millisecond intervals */
void clear(void);
