///////////////////////////////////////////AUTHOR INFORMATION///////////////////////////////////////////
//                                                                                                                                                                                       //
// 101044045                                                                                                                                             31 / 05 / 2014 //
//                                                                                                                                                                                       //
// Muhammed Maruf KILIÇ                                                                                                                                                 //
//                                                                                                                                                                                       //
// Bilgisayar Muhendisligi 3.Sinif                                                                                                                                       //
//                                                                                                                                                                                       //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////// INCLUDE //////////////////////////////////////////////////
#include <hidef.h>      /* common defines and macros */                                                                                                    //
#include "derivative.h"      /* derivative-specific definitions */                                                                                         //
#include <stdlib.h>                                                                                                                                                             //
#include <stdio.h>                                                                                                                                                              //
#include "lcd.h"                                                                                                                                                                //
////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////DEFINE SEI_CLI /////////////////////////////////////////////
#define ENABLE() __asm(cli)                                                                         
#define DISABLE()  __asm(sei)                                                                       
////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////DEFINE BITS //////////////////////////////////////////////
#define bit0 0x01                                                                                     
#define bit1 0x02                                                                                   
#define bit2 0x04                                                                                   
#define bit3 0x08                                                                                  
#define bit4 0x10                                                                                
#define bit5 0x20                                                                                   
#define bit6 0x40                                                                                   
#define bit7 0x80                                                                                  
                                                                                                      
#define TIME 87 //prescaler ms                                                                  
////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                      

///////////////////////////////////////////////// BUZZERS //////////////////////////////////////////////
#define VICTORY 1                                                                                   
#define OVER 0   

#define GARAGE_CAPACITY 20                                                                                   
                                                                                                  
#define C 1915                                                                                  
#define D 1700                                                                                 
#define E 1519                                                                                   
#define F 1432                                                                                      
#define G 1275                                                                                    
#define A 1136                                                                                    
#define B 1014                                                                                    
#define Bb 1073                                                                                  
                                                                                                 
#define MARIO_NOTES 24                                                                     
#define TERROR_NOTES 12                                                                           
#define QUES_LEN 10                                                                             
#define COUNT_DOWN 9                                                                             
                                                                                                 
#define ROW_NUM 4                                                                           
#define COL_NUM 4                                                                                
                                                                                                      
                                                                                                      
const unsigned char SEG_CODES[] = { 0x3F,0x06,0x5B,0x4F,                                        
                                    0x66,0x6D,0x7D,0x07,                                            
                                    0x7F,0x6F };                                                    
                                                                                                     
                                                                                                     
const unsigned int MARIO[] = { E, E, E, C, E, G, G, C, G, E, A, B, Bb, A, G, E,                    
                                                        G, A, F, G, E, C, D, B };                     
const unsigned int MARIO_DURATION[] = { 120, 240, 240, 120, 240, 480, 480, 360,                    
                                        360, 360, 240, 240, 120, 240, 160, 160,                     
                                        160, 240, 120, 240, 240, 120, 120, 120 };                   
                                                                                                    
volatile int gl_num=0,   // Num to show on 7segs                                                 
             gl_victory=0,                                                                         
             gl_note=0,                                                                             
             gl_is_time_over=FALSE,                                                                  
             gl_wait_time = 4,                                                                      
             gl_elapsed_sec = 0;                                                                     
                                                                                                      
                                                                                                    
const unsigned int TERROR[] = { C , C , C ,                                                          
                                C , C , C ,                                                          
                                C , C , C ,                                                         
                                C , C , C };                                                         
                                                                                                     
const unsigned int TERROR_DURATION[] = { 200 , 200 , 200 ,                                       
                                         200 , 200 , 200 ,                                          
                                         200 , 200 , 200 ,                                         
                                         200 , 200 , 200 };                                         
                                                                                                    
                                                                                                   
////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////INTERRUPT /////////////////////////////////////////////
interrupt(((0x10000 -Vtimch1)/2 ) -1) void garas_giris(void);                                      
interrupt(((0x10000 -Vtimch2)/2 ) -1) void garas_cikis(void);                                      
interrupt(((0x10000 -Vtimch5)/2 ) -1) void SoundBuzzer(void);                                      
interrupt(((0x10000 -Vrti)/2 ) -1) void realTime(void);                                        
////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////
void UserInterface();                                                                                                                                 
void PlaySound(int vic);                                                                                                          
int GetKey();                                                                                                                               
void init();                                                                                                                                             
void reset();                                                                                                                                            
void error(int temp);                                                                                                                                                 
void showTime();                                                                                                                                                                                                               
void fullMessage();                                                                     
void showSpeed();
void updateTime();

void showHighSpeed();
void averageCarInGarageF();
void totalCarInGarageF();
void goodBye();
////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////// GLOBAL VARIABLe/////////////////////////////////////////////////
                                                                                                                                                                                
                                                                                                                                                                               
int gidis = 0;                                                                                                                                                             
int donus = 0;                                                                                                                                                              
long counter = 0;                                                                                                                                                        
char realtime[10];                                                                                                                                                   
                                                                                                                                                                           
                                                                                                                                                                           
unsigned int speed;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
static int flagGeneral = 0;                                                                                                                                
                                                                                                                                                                                 
                                                                                                                                                                    
int in = 0;                                                                                                                                                            
int out = 0;                                                                                                                   
                                                                                                                                                                        
int countCarInGarage = 0;                                                                                              
                                                                                                                                  
int capacity = 0;
int temp = 0;

 //65
static int second1 = 0;
static int second2 = 0;

static int hour1 = 0; 
static int hour2 = 0;

static int mili1 = 0;
static int mili2 = 0;


static char Csecond1[5];
static char Csecond2[5];

static char Chour1[5];
static char Chour2[5];

static char Cmili1[5];
static char Cmili2[5];

static int timeCount = 0;


volatile static  int highSpeed = 0;  // high speed tamamdir show içerisinde bunu gösterelim
volatile static  int totalCarInGarage = 0; // programin basindan itibaren iceriye giren
volatile static  int averageCarInGarage = 0;// son 1 dk icerisinde ki garaja giren cikan araclar


////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////METER///////////////////////////////////////////////////
#define DISTANCE 150 // mm
////////////////////////////////////////////////////////////////////////////////////////////////////////

void main(void) {

    unsigned int time=0;
    int keyCode;
    int highSpeedNew = 0;

    DISABLE();

    init();

    ENABLE();

    while(1)
    { 

        if(!flagGeneral)
            UserInterface();
                
        delay_1ms(2);
        puts2lcd(Chour2);
        puts2lcd(Chour1);
        puts2lcd(":");
        puts2lcd(Csecond2);
        puts2lcd(Csecond1);
        puts2lcd(":");
        puts2lcd(Cmili2);
        puts2lcd(Cmili1);
        delay_1ms(10);
        
        updateTime();  
         
         keyCode = GetKey();
         switch(keyCode) {
          case 1:
              showHighSpeed();
              break;
          case 2:
              totalCarInGarageF();
            break;
          case 3:
            averageCarInGarageF();
            break;
          case 4:
            goodBye();
            __asm(swi);
            break;
          default:
            break;      
         }
         
          __asm(wai);

      
        if(gidis == 1 && donus == 1) {

            
            put2lcd(0x01,CMD);
            delay_1ms(2);
           
            if(in == 1 || (out == 1 && countCarInGarage != 0))
              showSpeed();
            
            if(in == 1 || out == 1){
                if(counter * 10 < 150){
                    highSpeedNew = DISTANCE / (counter*10); 
                    if(highSpeedNew > highSpeed)
                         highSpeed =  highSpeedNew; 
                    
                    PlaySound(VICTORY);
                   
                }
            }
            
            if((in == 1)) {
                if( countCarInGarage < GARAGE_CAPACITY) {
                       countCarInGarage++;
                       totalCarInGarage++;
                }else {
                        error(1);
                }
                
            }

            if((out == 1)) {
            
                if(countCarInGarage != 0){
                    countCarInGarage--;
                    totalCarInGarage++;
                }
                else {
                    error(2);
                }
            }

            delay_1ms(50);  
            PORTB = countCarInGarage;
            
             if(second2 == 0 && second1 != 0) {
                averageCarInGarage = totalCarInGarage / second1;    
             }else if(second2 == 0 && second1 == 0) {
                averageCarInGarage = totalCarInGarage;
             }
                
            reset();
        }

        put2lcd(0x01,CMD);
        delay_1ms(2);
           
    }


}// end of main


void init(){
  
    TSCR1 = 0x80;
    TSCR2 = 0x03;  

    TIOS = TIOS & ~0x02;     /* Configure PT1 as IC */ 
    TCTL4 = (TCTL4 | 0x04) & ~0x08;   /* Capture Rising Edge */ 
    TFLG1 |= 0x02;       /* Clear IC1 Flag */ 
    TIE = TIE | 0x02;       /* Enable IC1 Interrupt */ 
               
    /* Setup for IC2 */ 
    TIOS = TIOS & ~0x04;     /* Configure PT2 as IC */ 
    TCTL4 = (TCTL4 | 0x10) & ~0x20;   /* Capture Rising Edge */ 
    TFLG1 |= 0x04;         /* Clear IC2 Flag */ 
    TIE = TIE | 0x04; 

    //REAL TIME INTERRUPT
    CRGINT = 0x80;
    CRGFLG = 0x80;
    RTICTL = 0x49;//10 ms 


    DDRA = 0x0F;  // pb0-3 is out, others input  
    DDRB = 0xFF;
    DDRP = 0xFF;
    PTP = 0x0F;
    PORTB = 0x00;
    openlcd();
   
}


void reset() {
    TC1 = 0;
    TC2 = 0;
    counter = 0;
    gidis = 0;
    donus = 0;
    
    in = 0;
    out = 0;   
}


void showTime() {
    sprintf(realtime,"%ldms",counter * 10);
    puts2lcd(realtime);
    put2lcd(0xC0,CMD);
    sprintf(realtime,"T.Car : %d",countCarInGarage);
    puts2lcd(realtime);  
}

void showSpeed() {
    char tempp[10];
    char timee[10];
    
    
    puts2lcd("Speed is");
    put2lcd(0xC0,CMD);
    
    if(counter*10 < 150) {
       sprintf(tempp,"%ld m/s",DISTANCE / (counter*10));
          
    }else if(counter*10 < 1000) {
      sprintf(tempp,"0,%ld m/s",DISTANCE / (counter));

    }else {
       sprintf(tempp,"0,0%ld m/s",(DISTANCE*10) / (counter*10));
      
    }
    
    puts2lcd(tempp);
}

void error(int temp) {
  
    char choose1[]  = "GARAGE EMTPY";
    char choose2[] =  "GARAGE FULL"; 
    
    if(temp == 1){
      puts2lcd(choose2);
    }else if(temp == 2) {
       puts2lcd(choose1);
    }
      
    PlaySound(OVER);
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */
     
}

void fullMessage() {
    puts2lcd("Garage is FULL");
    delay_1ms(100);
    put2lcd(0xC0,CMD);
    puts2lcd("Wait...");
    delay_1ms(100);
    
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	  delay_1ms(2); /* wait until "clear display" command is complete */  
}

void showHighSpeed() {
     char temppp[10];
   
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */  
    
    sprintf(temppp,"%d",highSpeed);
    puts2lcd("High Speed : ");
    puts2lcd(temppp);
    delay_1ms(100);
    
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */  
 
}

void totalCarInGarageF() {
      char tempc[10];
     
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */  

    sprintf(tempc,"%d",totalCarInGarage);
    puts2lcd("Total Car : ");
    puts2lcd(tempc);     
    delay_1ms(100);
    
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */   
}

void averageCarInGarageF() {
     char tempc[10];
     
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */  

    sprintf(tempc,"%d", averageCarInGarage);
    puts2lcd("Average Car : ");
    puts2lcd(tempc);     
    delay_1ms(100);
    
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */ 
  
}

void goodBye() {
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */  
    
    puts2lcd("Good Bye !"); 
    put2lcd(0xC0,CMD);
    puts2lcd("Thanks...");
    delay_1ms(100);
    
    put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	delay_1ms(2); /* wait until "clear display" command is complete */  
}

void updateTime() {

      if(timeCount > 60)   {
          mili1++;
          timeCount = 0;      
      }
      
       if(mili1 >= 10) {
            mili2++;
            mili1 = 0;
       }
       
       if((mili2*10 + mili1) > 60) {
          second1++;
          mili1 = 0;
          mili2 = 0;
       }

      if(second1 >= 10) {
          second2++;
          second1 = 0;
      }

       if((second2*10 + second1) > 60) {
          hour1++;
          second1 = 0;
          second2 = 0;
       }
       
     
       sprintf(Chour1,"%d",hour1);
       sprintf(Chour2,"%d",hour2);
       sprintf(Csecond1,"%d",second1);
       sprintf(Csecond2,"%d",second2);
       sprintf(Cmili1,"%d",mili1);
       sprintf(Cmili2,"%d",mili2);
  
}


void UserInterface() {
  
    char choose1[] = "[1]High Speed";
    char choose2[] = "[2]Total car";
    char choose3[] = "[3]Average car 1s";
    char choose4[] = "[4]Exit";
    
    int flag = 0; 
    
    int count = 0;
    
   
    while(!flag){
      
      
      if(count % 2 == 0){
        
        puts2lcd(choose1);
        delay_1ms(100);
        put2lcd(0xC0,CMD);
        puts2lcd(choose2);
        delay_1ms(100);
      }else {
        
        puts2lcd(choose3);
        delay_1ms(100);
        put2lcd(0xC0,CMD);
        puts2lcd(choose4);
        delay_1ms(100);
        flag = 1;
        flagGeneral = 1;
      }
      
      
      put2lcd(0x01,CMD); /* clear screen, move cursor to home */
	  delay_1ms(2); /* wait until "clear display" command is complete */
	  count++;
 
    }
  
}



void PlaySound(int vic) 
{   
    DISABLE();
             
    TIOS = TIOS | 0x20;   /* Configure PT5 as Output */         
    TCTL1 = (TCTL1 | 0x04) & ~0x08; /* Set up PT5 to toggle on compare */ 
    TFLG1 = 0x20;     /* Clear Channel 5 flag */ 
    TIE = TIE | 0x20;
             
    gl_victory = vic;
    
    ENABLE();
    
    if(vic == VICTORY)
    {   
        for(gl_note=0 ; gl_note < MARIO_NOTES ; ++gl_note)
        {   
           delay_1ms(MARIO_DURATION[gl_note]/30); 
        }     
    }    
    else if(vic == OVER)
    {         
        for(gl_note=0 ; gl_note < TERROR_NOTES ; ++gl_note)
        {      
           delay_1ms(TERROR_DURATION[gl_note]/30); 
        }     
    }
     
    
  TFLG1 = 0x20; /* Clear Channel 5 flag */
  TIE = TIE & ~0x20;
  TIOS = TIOS & ~0x20;
}


interrupt(((0x10000 -Vtimch5)/2 ) -1) void SoundBuzzer(void) {
  
    switch(gl_victory)
    {
        case VICTORY: TC5 += MARIO[gl_note]*3; 
             break;
        case OVER : TC5 += TERROR[gl_note]*3; 
             break; 
    }
    
    TFLG1 |= 0x20;     /* Clear Channel 5 flag */   
}

      


interrupt(((0x10000 -Vtimch1)/2 ) -1) void garas_giris(void)
{ 
	gidis = 1;
		
	if(!in)
	  out = 1;	
		
	TFLG1 |= 0x02;
}


interrupt(((0x10000 -Vtimch2)/2 ) -1) void garas_cikis(void)
{
  donus = 1;
	
	if(!out)
	  in = 1;
	
	TFLG1 |= 0x04;
}

interrupt(((0x10000 -Vrti)/2 ) -1) void realTime(void) {
 
 
 if(gidis == 1 || donus == 1)
    counter += 1;
 
 
 timeCount++;
 
 CRGFLG = 0x80;
  
}

// Gets pressed key number from keypad
// Waits for any key to pressed otherwise won't return.
int GetKey() 
{
    int row,
        column;
                
    const char row_mask[ROW_NUM] = { 0xFE,0xFD,0xFB,0xF7 };
    const char col_mask[COL_NUM] = { 0x10,0x20,0x40,0x80 };        
    const unsigned int keys[ROW_NUM][COL_NUM] = { 1,2,3,10,
                                                  4,5,6,11,
                                                  7,8,9,12,
                                                  14,0,15,13 };
                
    for(row=0 ; row < ROW_NUM ; ++row){
        
        PORTA = 0xFF;// Reset PortA
        for(column=0; column < COL_NUM ;++column){
                  
            PORTA = PORTA & row_mask[row]; // Set specific row to 0
                                      
            if( (PORTA & col_mask[column]) == 0 ){
            // Check if any key is pressed
                
                  delay_1ms(50);                      
                  // Wait 50ms and check again for make sure key is pressed.
                  if( (PORTA & col_mask[column]) == 0 ){
                        return keys[row][column]; 
                  }                   
                 
            }
            
        }
    
    }    
    
    return -1;
    
}

