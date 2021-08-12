#include "pragmas.h"
#include "LCD.h"
#include "ADC.h"
#include <stdio.h>
#include <string.h>

unsigned char state = 1; 

unsigned char pass_num = 0;
unsigned int pass_arr[3];

unsigned char second_counter = 0;
unsigned char half_sec_counter = 0;
unsigned char countdown = 90;
unsigned char remaining_attempts = 3;
unsigned char blink_flag = 0;
unsigned char refresh_state = 0;

unsigned char adc_dial_read_start = 1;
unsigned char adc_dial_read_done = 0;
unsigned char adc_temp_read_done = 0;
unsigned char adc_flag = 0;
unsigned short adc_dial_value;
unsigned short adc_temp_value;
float temp_value;

unsigned char state2_init_flag = 1;
unsigned char state2_exit_flag = 0;

unsigned char state3_init_flag = 1;
unsigned char state4_init_flag = 1;
unsigned char rb4_pressed = 0;

unsigned char state2_clk_init_flag = 1;
unsigned short state2_init_adc_value;

void __interrupt(high_priority) isr()
{
    
    if (TMR0IE == 1 && TMR0IF == 1) {    
        if(++second_counter == 20){
            second_counter = 0;
            if(--countdown == 0){
                state2_exit_flag = 1;
                state = 4;
            }
        }
        TMR0H = 0x0B;
        TMR0L = 0xDB; 
        TMR0IF = 0;
    }
    
    if (TMR1IE==1 && TMR1IF == 1) {    
        if(++half_sec_counter == 80){
            half_sec_counter = 0;
            if(remaining_attempts < 3){
                blink_flag = (blink_flag == 0) ? 1 : 0;
            }
        }
        
        
        if(++refresh_state == 4){
           refresh_state = 0;
        }
        

        if(adc_flag){
            ADCON0bits.CHS = 0x02;
        }else{
            ADCON0bits.CHS = 0x00;
        }
        
        ADCON0bits.GODONE = 1; //Start convertion   
        
        TMR1H = 0x0B;
        TMR1L = 0xDB; 
        TMR1IF = 0;
    }
    
    
    
    if (RBIE == 1 && RBIF == 1) {
        if (PORTBbits.RB4 == 0)
            rb4_pressed = 1;
        
        RBIF = 0;
    }
    
    
    
    if (INT0IE==1 && INT0IF == 1){
        if(adc_dial_value <= 999){
            if(state == 1){
                pass_arr[pass_num] = adc_dial_value/10;
                pass_num += 1;
            }else if(state == 2){
                TMR0ON = 1;
                if((adc_dial_value/10) == pass_arr[pass_num]){
                    pass_num += 1;
                }else{
                    remaining_attempts -= 1;
                    if(remaining_attempts == 1)
                        PORTCbits.RC5 = 1;
                    else if(remaining_attempts == 0){
                        state2_exit_flag = 1;
                        state = 4;
                    }
                }
            }
        }
     
        INT0IF = 0;
    }
    
    
    
    if (ADIE == 1 && ADIF == 1) {

        if(!adc_flag){
            adc_dial_read_done = 1;
            adc_dial_value = (unsigned short)((ADRESH << 8)+ADRESL);
            
            if((state == 1 || state == 2) && pass_num == 1)
                adc_dial_value = (unsigned short) (1023 - adc_dial_value);
                
        }else{
            adc_temp_value = (unsigned short)((ADRESH << 8)+ADRESL);
            adc_temp_read_done = 1;
        }

        ADIF = 0;
    }
}


void clearLCDRow(byte row){
    LCDGoto(1, row);
    for(int i = 0; i < 16; i++){
        LCDStr(" ");
    }
}

unsigned char get_digit(unsigned int number){
        switch(number) {
        case 0: return 0x3F;
        case 1: return 0x06;
        case 2: return 0x5B;
        case 3: return 0x4F;
        case 4: return 0x66;
        case 5: return 0x6D;
        case 6: return 0x7D;
        case 7: return 0x07;
        case 8: return 0x7F;
        case 9: return 0x6F;
        }
}

unsigned char get_attempt(void){
        switch(remaining_attempts) {
        case 1: return 0x08;
        case 2: return 0x48;
        case 3: return 0x49;
        }
}


void init(void){
    
  PEIE = 0;
  GIE = 0;
  
  TRISA = 0x00;
  LATA = 0x00;
  
  /* Timer0 Interrupt is used for 90 second countdown
   * 16-bit mode with prescaler of 1:8
   * Currently disabled by setting TMR0ON and TMR0IE to 0
   * FFFF-BDB=62500; 62500*8*(second_counter that counts to 20)/(40mhz/4 = 10mhz) = 1 second
   */
  T0CON = 0;
  T0PS1 = 1;
  TMR0H = 0x0B;
  TMR0L = 0xDB; 
  TMR0IF = 0;
  TMR0IE = 0;
  
  /* Timer1 Interrupt is used for 500ms blinking led and 7segment active digit change
   * two 8-bit operations with a prescaler of 1:1
   * Currently disabled by setting TMR1ON and TMR1IE to 0
   * FFFF-BDB=62500; 62500*(half_sec_counter that counts to 80)/(40mhz/4 = 10mhz) = 500ms
   */
  T1CON = 0;
  T1RUN = T1OSCEN = 1;
  TMR1H = 0x0B;
  TMR1L = 0xDB; 
  TMR1IF = 0;
  TMR1IE = 0;
  
  
 // RB0 Interrupt
  TRISB = 0x01; // Set RB0 as input pin and other pins as output
  INT0IF = 0;
  INT0IE = 1;
  
  // RB Port Change Interrupt
  RBIF = 0;
  RBIE = 0; // Currently disabled
  
  // ADC Interrupt
  ADIF = 0;
  ADIE = 1;
  
  
  InitADC();
  InitLCD();
  
  
  PEIE = 1;
  GIE = 1;
  
  LCDGoto(1, 1);
  LCDStr("SuperSecureSafe!");
  

  // Busy wait for 3 seconds
  __delay_ms(3000);
  
}


void state1(void){
    
    if(pass_num == 3){
        state = 2;
        return;
    }
    
    if(adc_dial_read_start){
        ADCON0bits.CHS = 0x00; 
        ADCON0bits.GODONE = 1;   
        adc_dial_read_start = 0;
    }
    
    if(adc_dial_read_done){
        adc_dial_read_done = 0;
        adc_dial_read_start = 1;
        
        LCDGoto(1 + 3*pass_num, 2);
        char buf[17];
        if(adc_dial_value <= 999){
            sprintf(buf, "%02d", adc_dial_value/10);
        }else{
            sprintf(buf, "%s", "XX");
        }
        
        LCDStr(buf);
    }
    
}

void state2_init(void){
    state2_init_flag = 0;
    state2_clk_init_flag = 1;
    state2_exit_flag = 0;
    
    refresh_state = 0;
    
    remaining_attempts = 3;
    pass_num = 0;
    countdown = 90;
    blink_flag = 0;

    adc_dial_read_done = 0;
    adc_temp_read_done = 0;
    adc_flag = 0;
    
    
    // For 7Segment
    TRISA = 0x07;  // 0:2 pins are input for ADC, 3:5 are output for 7Segment
    TRISD = 0;
  
    // For Heater
    TRISC = 0;
    
    
    // TMR0 initial value
    TMR0H = 0x0B;
    TMR0L = 0xDB; 
    TMR0IF = 0;
    TMR0IE = 1;
    second_counter = 0;
    
    // TMR1 initial value
    TMR1H = 0x0B;
    TMR1L = 0xDB; 
    TMR1IF = 0;
    TMR1IE = 1;
    half_sec_counter = 0;
    
    TMR0ON = 0;
    TMR1ON = 1;
    
    
    // ADC Interrupt
    ADIF = 0;
    ADIE = 1;
    
    // RB0 Interrupt
    TRISB = 0x01; // Set RB0 as input pin and other pins as output
    INT0IF = 0;
    INT0IE = 1;
    
    clearLCDRow(1);
    LCDGoto(1, 1);
    LCDStr("Input Password:");
    clearLCDRow(2);
    LCDGoto(1, 2);
    LCDStr("__-__-__");
    
}

void state2_exit(void){
    ADIE = 0;
    INT0IE = 0;
    TMR0IE = 0;
    TMR1IE = 0;
    TMR0ON = 0;
    TMR1ON = 0;

    state2_exit_flag = 0;
    
    if (state == 3){
        state3_init_flag = 1;
    }else{
        state4_init_flag = 1;
    }
}


void state2(void){
    
    if(state2_init_flag)
        state2_init();
    
    if(state2_exit_flag){
        state2_exit();
        return;
    }

    if(pass_num == 3){
        state = 3;
        state2_exit();
        return;
    }
        
    
    if(blink_flag == 1)
        LATB = 0xFE;
    else
        LATB = 0x00;
    
    
    if(adc_dial_read_done){
        adc_dial_read_done = 0;
        adc_flag = 1;        
                
        if(state2_clk_init_flag){
            state2_clk_init_flag = 0;
            state2_init_adc_value = adc_dial_value/10;
        }else if((adc_dial_value/10) != state2_init_adc_value){
            TMR0ON = 1;
        }
    }
    
    
    
    if(adc_temp_read_done){
        adc_temp_read_done = 0;
        adc_flag = 0;

        temp_value = adc_temp_value * 5.0f / 1024.0f * 100.0f; // temperature value
        if(remaining_attempts == 1 && temp_value > 40){
            state = 4;
            state2_exit();
            return;
        }
    }
    
    switch(refresh_state) {
        case 0: 
            LATA = 8;
            LATD = get_attempt();
            break;
        case 1: 
            LATA = 16; 
            LATD = get_digit(countdown/10);
            break;
        case 2: 
            LATA = 32;
            LATD = get_digit(countdown%10);
            break;
        case 3:
            LATA = 0;
            LCDGoto(1 + 3*pass_num, 2);
            char buf[17];
            if(adc_dial_value <= 999){
                sprintf(buf, "%02d", adc_dial_value/10);
            }else{
                sprintf(buf, "%s", "XX");
            }
     
            LCDStr(buf);
            break;
    }
    
    
    
}




void state3(void){
  
    if(state3_init_flag){
        state3_init_flag = 0;
        
        LCDGoto(1, 1);
        LCDStr("Unlocked; Press");
        LCDGoto(1, 2);
        LCDStr("RB4 to lock!");
  
        // Turn off the heater
        PORTCbits.RC5 = 0;
  
        // Turn off PORTB leds
        TRISB = 0;  
        LATB = 0x10;
        
        // Clear 7Segment Display
        LATA = 0;
        
        // RB Port Change Interrupt
        rb4_pressed = 0;
        TRISBbits.RB4 = 1; 
        RBIF = 0;
        RBIE = 1;
    }
    
    if (rb4_pressed){
        RBIE = 0;

        rb4_pressed = 0;
        state2_init_flag = 1;
        state = 2;
        return;
    }
  
}


void state4(void){
    
    if(state4_init_flag){
        state4_init_flag = 0;
        
        clearLCDRow(1);
        clearLCDRow(2);
        LCDGoto(1, 1);
        LCDStr("You Failed!");
  
        // Turn off the heater
        PORTCbits.RC5 = 0;
  
        // Turn on all the PORTB leds
        TRISB = 0;
        LATB = 0xFF;
        
        // Clear 7Segment display
        LATA = 0;
    }

}

void main(void) {
  
  init();
  
  clearLCDRow(1);
  LCDGoto(1, 1);
  LCDStr("Set Password:");
  clearLCDRow(2);
  LCDGoto(1, 2);
  LCDStr("__-__-__");
    
  while(1){
    switch(state) {
        case 1: state1(); break;
        case 2: state2(); break;
        case 3: state3(); break;
        case 4: state4(); break;
    }
  }
  
  return;
}
