LIST P=18F4620
    
#include <P18F4620.INC>

config OSC = HSPLL      ; Oscillator Selection bits (HS oscillator, PLL enabled (Clock Frequency = 4 x FOSC1))
config FCMEN = OFF      ; Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
config IESO = OFF       ; Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

; CONFIG2L
config PWRT = ON        ; Power-up Timer Enable bit (PWRT enabled)
config BOREN = OFF      ; Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
config BORV = 3         ; Brown Out Reset Voltage bits (Minimum setting)

; CONFIG2H
config WDT = OFF        ; Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
config WDTPS = 32768    ; Watchdog Timer Postscale Select bits (1:32768)

; CONFIG3H
config CCP2MX = PORTC   ; CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
config PBADEN = OFF     ; PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
config LPT1OSC = OFF    ; Low-Power Timer1 Oscillator Enable bit (Timer1 configured for higher power operation)
config MCLRE = ON       ; MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

; CONFIG4L
config STVREN = OFF     ; Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
config LVP = OFF        ; Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
config XINST = OFF      ; Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

; CONFIG5L
config CP0 = OFF        ; Code Protection bit (Block 0 (000800-003FFFh) not code-protected)
config CP1 = OFF        ; Code Protection bit (Block 1 (004000-007FFFh) not code-protected)
config CP2 = OFF        ; Code Protection bit (Block 2 (008000-00BFFFh) not code-protected)
config CP3 = OFF        ; Code Protection bit (Block 3 (00C000-00FFFFh) not code-protected)

; CONFIG5H
config CPB = OFF        ; Boot Block Code Protection bit (Boot block (000000-0007FFh) not code-protected)
config CPD = OFF        ; Data EEPROM Code Protection bit (Data EEPROM not code-protected)

; CONFIG6L
config WRT0 = OFF       ; Write Protection bit (Block 0 (000800-003FFFh) not write-protected)
config WRT1 = OFF       ; Write Protection bit (Block 1 (004000-007FFFh) not write-protected)
config WRT2 = OFF       ; Write Protection bit (Block 2 (008000-00BFFFh) not write-protected)
config WRT3 = OFF       ; Write Protection bit (Block 3 (00C000-00FFFFh) not write-protected)

; CONFIG6H
config WRTC = OFF       ; Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) not write-protected)
config WRTB = OFF       ; Boot Block Write Protection bit (Boot Block (000000-0007FFh) not write-protected)
config WRTD = OFF       ; Data EEPROM Write Protection bit (Data EEPROM not write-protected)

; CONFIG7L
config EBTR0 = OFF      ; Table Read Protection bit (Block 0 (000800-003FFFh) not protected from table reads executed in other blocks)
config EBTR1 = OFF      ; Table Read Protection bit (Block 1 (004000-007FFFh) not protected from table reads executed in other blocks)
config EBTR2 = OFF      ; Table Read Protection bit (Block 2 (008000-00BFFFh) not protected from table reads executed in other blocks)
config EBTR3 = OFF      ; Table Read Protection bit (Block 3 (00C000-00FFFFh) not protected from table reads executed in other blocks)

; CONFIG7H
config EBTRB = OFF      ; Boot Block Table Read Protection bit (Boot Block (000000-0007FFh) not protected from table reads executed in other blocks)

zero_num equ b'00111111'
one_num equ b'00000110'
two_num equ b'01011011'
three_num equ b'01001111'
four_num equ b'01100110'
five_num equ b'01101101'
six_num equ b'01111101'
seven_num equ b'00000111'
eight_num equ b'01111111'
nine_num equ b'01101111'
space_chr equ b'00000000'
underscore_chr equ b'00001000'
A_chr equ b'01011111'
B_chr equ b'01111100'
C_chr equ b'01011000'
D_chr equ b'01011110'
E_chr equ b'01111011'
F_chr equ b'01110001'
G_chr equ b'01101111'
H_chr equ b'01110100'
I_chr equ b'00000100'
J_chr equ b'00001110'
K_chr equ b'01110101'
L_chr equ b'00111000'
M_chr equ b'01010101'
N_chr equ b'01010100'
O_chr equ b'01011100'
P_chr equ b'01110011'
R_chr equ b'01010000'
S_chr equ b'01100100'
T_chr equ b'01111000'
U_chr equ b'00011100'
V_chr equ b'00101010'
Y_chr equ b'01101110'
Z_chr equ b'01011011'

variables udata_acs
rb3_button_flag res 1
state_reg res 1
sub_tmp_var res 1
portb_var res 1
global_countdown res 1
sec_counter res 1
half_sec_counter res 1
dumb_var res 1
delay_counter res 1
chr1 res 1
chr2 res 1
chr3 res 1
chr4 res 1
chr5 res 1
chr6 res 1
disp1_val res 1
disp2_val res 1
disp3_val res 1
disp4_val res 1
review_conf_state res 1
read_conf_state res 1
read_direction res 1
last_saved_chr res 1
current_chr res 1
num_of_chr res 1
last_button res 1
next_index res 1
tmp res 1
inactivity_counter res 1
first_click_flag res 1

org     0x00
goto    init

org     0x08
goto    isr             ;go to interrupt service routine
 
init_delay:
    setf delay_counter
    do_while_init_counter_1_not_zero:
        decf delay_counter
        bnz do_while_init_counter_1_not_zero
    end_do_while_init_counter_1_not_zero:
    
    return
    
little_delay:
    movlw d'60'
    movwf delay_counter
    do_while_little_counter_1_not_zero:
        decf delay_counter
        bnz do_while_little_counter_1_not_zero
    end_do_while_little_counter_1_not_zero:
    
    return

;;;;;;;;;;;;;;;;;;; ABOUT DESIGN ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Current state is being stored in state_reg and the states are encoded with
; one-hot encoding. The value of the state_reg indicates what will
; be displayed in seven segment display and what will happen when buttonx 
; is pressed. I used two timers TMR0 to adjust the countdown and TMR1 for 
; inactivity interrupt in write state and half second interrupt in read state.
; In the beginning of the program, condition of the RB3 is being checked
; and if it is released, tmr0 and rb interrupts are enabled and 
; main subroutine starts. In main subroutine, firstly keypad buttons being checked.
; To check the columns, rb0, rb1 and rb2 is being set to low, respectively. 
; After that, rd3, rd2, rd1 and rd0 is being checked in each column to detect the button press.
; first_click_flag indicates whether the currently pressed button is the first button pressed
; after the initialization step or return from the review state or return from the
; inactivity interrupt. Using this flag important since after these three events
; tmr1 interrupt is disabled. With the first button press, tmr1 is being enabled again.
; Last pressed button is also stored to indicate whether current button is different from
; the previous one or not. If it is different, current character is saved by calling
; save_new_chr. save_new_chr also controls whether there are six char or not. If there are
; six character it updates the current state as read state. After the keypad check,
; the values will be displayed are updated by calling update_display and the updated values
; displayed in seven segment display by calling refresh_display. review_conf_state keeps the
; index of the character in disp2 for the review state. For instance, if it equals to 3
; that means chr3, chr4, chr5 and chr6 will be displayed. read_conf_state is similar but it 
; is for the read state.
 
init:
    ;Change analog to digital
    movlw 07h
    movwf ADCON1

    ;Disable interrupts
    clrf    INTCON
    clrf    INTCON2

    ;Init variables
    clrf rb3_button_flag ; Flag for RB3 button, will be set when rb3 is pressed
    clrf state_reg	 ; Register to indicate current state, write, review or read
    clrf sub_tmp_var
    movlw d'20'
    movwf global_countdown  ; Countdown register to keep 20 sec
    clrf sec_counter	    ; Counter register for TMR0
    clrf half_sec_counter   ; Counter register for TMR1 for read state
    movlw underscore_chr    ; Init all six characters as underscore
    movwf chr1
    movwf chr2
    movwf chr3
    movwf chr4
    movwf chr5
    movwf chr6
    movwf last_saved_chr    ; Register to keep last saved character for disp3
    movwf current_chr	    ; Register to keep current character for disp4
    movlw d'1'
    movwf review_conf_state ; Register to keep the index of the char displayed in disp2
			    ; for instance if it is two then char2, char3, char4 and char5
			    ; will be displayed in review state
    movwf read_conf_state   ; Similar to review_conf_state but this is for read state
    movwf read_direction    ; Register to keep the shift direction in read state
			    ; if it is one shift to right, otherwise to left
    movwf next_index	    ; This reg will keep the index of the next character 
			    ; for the pressed button in write state
    clrf num_of_chr	    ; Number of character saved
    clrf last_button	    ; To indicate whether the button is changed or not
    clrf inactivity_counter	; Counter register for TMR1 for write state
    bsf first_click_flag, 0	; Will be set when no button pressed yet 
    
    
    ;Configure Output Ports
    clrf TRISA
    clrf TRISD

    ;Configure RB3 and RB4 as input
    movlw   b'00011000' ; w_reg =  b'00011000'
    movwf   TRISB       ; TRISB = w_reg = b'00011000' 
    bcf     INTCON2, 7  ; Pull-ups are enabled - clear INTCON2<7>
    movf PORTB,W

    ;Initialize Timer0
    movlw   b'00000010' ;choose 16-bit mode
                        ;Timer0 increment from internal clock with a prescaler of 1:8.
			;Disable Timer0 by setting TMR0ON to 0 (for now)
    movwf   T0CON       ;T0CON = b'00000010'
    
    movlw   0x0B        ;FFFF-BDB=62500; 62500*8*(sec_counter that counts to 20)/(40mhz/4 = 10mhz) = 1 second;
    movwf   TMR0H
    movlw   0xDB
    movwf   TMR0L
    
    ;Initialize Timer1
    movlw   b'01111000' ;read/write in two 8-bit operations
                        ;Timer1 increment from internal clock with a prescaler of 1:8.
			;Disable Timer1 by setting TMR1ON to 0 (for now)
    movwf   T1CON       ;T1CON = b'01111000'
    
    movlw   0x0B        ;FFFF-BDB=62500; 62500*8*(half_sec_counter that counts to 10)/(40mhz/4 = 10mhz) = 0.5 second;
    movwf   TMR1H
    movlw   0xDB
    movwf   TMR1L

    ;Enable interrupts
    bsf     PIE1, 0     ;Enable Timer1 interrupt
    movlw   b'11100000' ;Enable Global, peripheral, Timer0 interrupts by setting GIE, PEIE, TMR0IE bits to 1
    movwf   INTCON
    goto phase_0


phase_0:
    btfsc PORTB, 3 ;Check if RB3 is pressed
    goto phase_0_unpressed ; No, then goto unpressed state
    bsf rb3_button_flag, 0 ; Yes, set 0th bit to 1 in order to indicate the button is pressed
    goto phase_0

phase_0_unpressed:
    btfss rb3_button_flag, 0 ;Check if RB3 released
    goto phase_0 ; No, it was not pressed earlier
    bsf state_reg, 0 ; Yes, set 0th bit to 1 in order to indicate we are in Message Write state
    bsf INTCON, 3 ; Enable RB interrupt by setting RBIE bit to 1
    bsf T0CON, 7 ;Enable TMR0 interrupt by setting TMR0ON to 1
    goto main

main:
    
    setf TRISD ; Configure pins of PORTD as input
    clrf LATA ; Clear PORTA to keep display dark during the keypad check
    movlw b'00000110' ; RB0 low, others high
    movwf LATB ; Check the first column of the keypad
    call little_delay
    movff PORTD, tmp
    btfss   tmp, 3 ; Check if button1 is pressed
	goto button1_pressed ; Yes, then go to pressed state
    btfss   tmp, 2 ; Check if button4 is pressed
	goto button4_pressed 
    btfss   tmp, 1 ; Check if button7 is pressed
	goto button7_pressed 
    btfss   tmp, 0 ; Check if buttonstar is pressed
	goto buttonstar_pressed

    movlw b'00000101' ; RB1 low, others high
    movwf LATB ; Check the second column of the keypad
    call little_delay
    movff PORTD, tmp
    btfss   tmp, 3 ; Check if button2 is pressed
	goto button2_pressed ; Yes, then go to pressed state
    btfss   tmp, 2 ; Check if button5 is pressed
	goto button5_pressed 
    btfss   tmp, 1 ; Check if button8 is pressed
	goto button8_pressed 
    btfss   tmp, 0 ; Check if button0 is pressed
	goto button0_pressed 
	
    movlw b'00000011' ; RB2 low, others high
    movwf LATB ; Check the third column of the keypad
    call little_delay
    movff PORTD, tmp 
    btfss   tmp, 3 ; Check if button3 is pressed
	goto button3_pressed ; Yes, then go to pressed state
    btfss   tmp, 2 ; Check if button6 is pressed
	goto button6_pressed
    btfss   tmp, 1 ; Check if button9 is pressed
	goto button9_pressed
    btfss   tmp, 0 ; Check if buttonhash is pressed
	goto buttonhash_pressed
    
end_check:
    
    clrf TRISD ; Configure pins of PORTD as output
    call update_display ; Update the seven segment display
    call refresh_display ; Refresh the seven segment display	    


    goto main
    

save_new_chr:
    movf current_chr, w
    xorlw underscore_chr	   
    btfsc   STATUS, Z               ;Do not save if the current chr is underscore
	return
    movff current_chr, last_saved_chr	
    incf num_of_chr
    movf num_of_chr, w		    ;Find the correct place for current char
    DCFSNZ WREG
	movff current_chr, chr1
    DCFSNZ WREG
	movff current_chr, chr2
    DCFSNZ WREG
	movff current_chr, chr3
    DCFSNZ WREG
	movff current_chr, chr4
    DCFSNZ WREG
	movff current_chr, chr5
    DCFSNZ WREG
	movff current_chr, chr6
    movf num_of_chr, w
    sublw d'6'
    btfss   STATUS, Z               ;Check if we have reached to six chars
	return                      ;No, then return
    movlw   0x0B		    ;Yes, then prepare for read state
    movwf   TMR1H
    movlw   0xDB
    movwf   TMR1L
    bsf     T1CON, 0    ;Enable Timer1 by setting TMR1ON to 1
    clrf state_reg  
    bsf state_reg, 2    ;Update the state as Message Read state
    return

set_inactivity:
    bcf first_click_flag, 0	
    bsf     T1CON, 0    ;Enable Timer1 by setting TMR1ON to 1
    return

clear_inactivity_timer:
    clrf    inactivity_counter	;When new button is pressed clear the timer
    movlw   0x0B
    movwf   TMR1H
    movlw   0xDB
    movwf   TMR1L
    return
    
button1_pressed:
    goto end_check

button2_pressed:
    btfss   PORTD, 3                ; Check if being pressed
	   goto button2_pressed         ; Yes, still being pressed wait for released
    btfss   state_reg, 0 ; check if state is message_write
	   goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity timer
    call clear_inactivity_timer    ; New button click reset the inactivity timer
    movf last_button, w             
    sublw d'2'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button2_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'2' 
    movwf last_button               ;Update the last pressed button
    clrf next_index
    bsf next_index, 0
button2_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button2_1
    btfsc next_index, 1
	goto button2_2
    goto button2_3
button2_1:
    movlw A_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button2_2:
    movlw B_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button2_3:
    movlw C_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
    
button3_pressed:
    btfss   PORTD, 3                ; Check if being pressed
	   goto button3_pressed         ; Yes, still being pressed wait for released
    btfss   state_reg, 0 ; check if state is message_write
	goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity
    call clear_inactivity_timer    ; New button click reset the inactivity timer
    movf last_button, w             
    sublw d'3'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button3_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'3' 
    movwf last_button               ;Update the recently pressed button
    clrf next_index
    bsf next_index, 0
button3_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button3_1
    btfsc next_index, 1
	goto button3_2
    goto button3_3
button3_1:
    movlw D_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button3_2:
    movlw E_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button3_3:
    movlw F_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
    
button4_pressed:
    btfss   PORTD, 2 
	goto button4_pressed ; still being pressed
    btfss   state_reg, 0 ; check if state is message_write
	   goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity
    call clear_inactivity_timer    ; New button click reset the inactivity timer
    movf last_button, w             
    sublw d'4'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button4_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'4' 
    movwf last_button               ;Update the recently pressed button
    clrf next_index
    bsf next_index, 0
button4_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button4_1
    btfsc next_index, 1
	goto button4_2
    goto button4_3
button4_1:
    movlw G_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button4_2:
    movlw H_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button4_3:
    movlw I_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
	
button5_pressed:
    btfss   PORTD, 2 
	goto button5_pressed ; still being pressed
    btfss   state_reg, 0 ; check if state is message_write
	goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity
    call clear_inactivity_timer    ; New button click start the inactivity timer again
    movf last_button, w             
    sublw d'5'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button5_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'5' 
    movwf last_button               ;Update the recently pressed button
    clrf next_index
    bsf next_index, 0
button5_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button5_1
    btfsc next_index, 1
	goto button5_2
    goto button5_3
button5_1:
    movlw J_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button5_2:
    movlw K_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button5_3:
    movlw L_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
	
button6_pressed:
    btfss   PORTD, 2 
	goto button6_pressed ; still being pressed
    btfss   state_reg, 0 ; check if state is message_write
	goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity
    call clear_inactivity_timer    ; New button click start the inactivity timer again
    movf last_button, w             
    sublw d'6'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button6_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'6' 
    movwf last_button               ;Update the recently pressed button
    clrf next_index
    bsf next_index, 0
button6_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button6_1
    btfsc next_index, 1
	goto button6_2
    goto button6_3
button6_1:
    movlw M_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button6_2:
    movlw N_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button6_3:
    movlw O_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
	
button7_pressed:
    btfss   PORTD, 1 
	goto button7_pressed ; still being pressed
    btfss   state_reg, 0 ; check if state is message_write
	goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity
    call clear_inactivity_timer    ; New button click start the inactivity timer again
    movf last_button, w             
    sublw d'7'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button7_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'7' 
    movwf last_button               ;Update the recently pressed button
    clrf next_index
    bsf next_index, 0
button7_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button7_1
    btfsc next_index, 1
	goto button7_2
    goto button7_3
button7_1:
    movlw P_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button7_2:
    movlw R_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button7_3:
    movlw S_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
    
button8_pressed:
    btfss   PORTD, 1 
	goto button8_pressed ; still being pressed
    btfss   state_reg, 0 ; check if state is message_write
	goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity
    call clear_inactivity_timer    ; New button click start the inactivity timer again
    movf last_button, w             
    sublw d'8'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button8_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'8' 
    movwf last_button               ;Update the recently pressed button
    clrf next_index
    bsf next_index, 0
button8_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button8_1
    btfsc next_index, 1
	goto button8_2
    goto button8_3
button8_1:
    movlw T_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button8_2:
    movlw U_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button8_3:
    movlw V_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
    
button9_pressed:
    btfss   PORTD, 1 
	goto button9_pressed ; still being pressed
    btfss   state_reg, 0 ; check if state is message_write
	goto end_check ; goto end_check if state is not message_write
    btfsc   first_click_flag, 0     ; Check if this is first button click after init or after review state
        call set_inactivity         ; Yes, then set inactivity
    call clear_inactivity_timer    ; New button click start the inactivity timer again
    movf last_button, w             
    sublw d'9'
    btfsc   STATUS, Z               ;Check if pressed button is changed
	   goto button9_body            ;No, button is not changed
    call save_new_chr               ;Yes, button is changed save the current character
    movlw d'9' 
    movwf last_button               ;Update the recently pressed button
    clrf next_index
    bsf next_index, 0
button9_body:
    btfsc  next_index, 0	    ;Check for the next char to display
	goto button9_1
    btfsc next_index, 1
	goto button9_2
    goto button9_3
button9_1:
    movlw Y_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 1
    goto end_check
button9_2:
    movlw Z_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 2
    goto end_check
button9_3:
    movlw space_chr
    movwf current_chr
    clrf next_index
    bsf next_index, 0
    goto end_check
    
button0_pressed:
    goto end_check
    
buttonstar_pressed:
    btfss   PORTD, 0 
	goto buttonstar_pressed ; still being pressed
    btfss   state_reg, 1 ; check if state is message_review
	goto end_check ; goto end_check if state is not message_review
    movf review_conf_state, w
    xorlw   d'1'                 
    btfsc   STATUS, Z              ;Check if it is left end
	goto end_check		   ;Yes, goto end_check since cannot go further
    decf   review_conf_state	   ;No, then shift to left
    goto end_check
    
    
buttonhash_pressed:
    btfss   PORTD, 0 
	goto buttonhash_pressed ; still being pressed
    btfss   state_reg, 1 ; check if state is message_review
	goto end_check ; goto end_check if state is not message_review
    movf review_conf_state, w
    xorlw   d'3'                   
    btfsc   STATUS, Z              ;Check if it is right end
	goto end_check		   ;Yes, goto end_check since cannot go further
    incf   review_conf_state	   ;No, then shift to right
    goto end_check
    
isr:
    btfsc   INTCON, 0           ;Is this PORTB on change interrupt
    goto rb4_interrupt          ;Yes, then goto rb4_interrupt
    btfsc   INTCON, 2           ;Is this TMR0 interupt
    goto timer_interrupt        ;Yes, then goto timer_interrupt
    btfss   PIR1, 0		;Is this a TMR1 interrupt?
    goto timer_1_interrupt	;Yes, then goto timer_1_interrupt

;;;;;;;;;;;;;;;;;;;;;;;; Timer1 interrupt handler part ;;;;;;;;;;;;;;;;;;;;;;;;;;
; Timer1 will be used for both the shift interrupt of read state and inactivity
; interrupt of write state that is why we check the state at first in the below code
timer_1_interrupt:
    bcf	    PIR1, 0		   ;Clear TMR1IF
    btfsc   state_reg, 0           ;Is the state Message Write
        goto timer_1_inactivity_interrupt   ;Yes, goto inactivity interrupt
    incf    half_sec_counter, f     ;Timer interrupt handler part begins here by incrementing count variable
    movf    half_sec_counter, w     ;Move count to Working register
    sublw   d'10'                   ;Decrement 10 from Working register
    btfss   STATUS, Z               ;Is the result Zero?
    goto    timer1_interrupt_exit   ;No, then exit from interrupt service routine
    clrf    half_sec_counter        ;Yes, then clear count variable
    btfss   read_direction, 0	    ;Check if the shift direction is to the right
    goto timer_1_read_left	    ;No, then go to shift left state

timer_1_read_right:
    movf read_conf_state, w
    xorlw   d'3'                   
    btfsc   STATUS, Z              ;Check if we are in right end
    goto timer_1_read_right_end	   ;Yes, then goto right end handler
    incf read_conf_state	   ;No, then increment read conf state to shift to right
    goto timer1_interrupt_exit
    
timer_1_read_right_end:
    decf read_conf_state	   ;Decrement read conf state to shift to left
    bcf   read_direction, 0	   ;Change shift direction to left
    goto timer1_interrupt_exit
    
timer_1_read_left:
    movf read_conf_state, w
    xorlw   d'1'                   
    btfsc   STATUS, Z              ;Check if we are in left end
    goto timer_1_read_left_end	   ;Yes, then goto right end handler
    decf read_conf_state	   ;No, then decrement read conf state to shift to left
    goto timer1_interrupt_exit
    
timer_1_read_left_end:
    incf read_conf_state	   ;Increment read conf state to shift to right
    bsf read_direction, 0	   ;Change shift direction to right
    goto timer1_interrupt_exit
    
    
timer1_interrupt_exit:
    movlw   0x0B                ;FFFF-BDB=62500; 62500*8*10 = 5000000 instruction cycle;
    movwf   TMR1H
    movlw   0xDB
    movwf   TMR1L
    retfie 1

timer_1_inactivity_interrupt:
    incf    inactivity_counter, f     ;Timer interrupt handler part begins here by incrementing count variable
    movf    inactivity_counter, w     ;Move count to Working register
    sublw   d'20'                   ;Decrement 20 from Working register
    btfss   STATUS, Z               ;Is the result Zero?
    goto    timer1_interrupt_exit   ;No, then exit from interrupt service routine
    clrf    inactivity_counter       ;Yes, then clear count variable
    call save_new_chr               ;Save the current character
    clrf last_button		; Clear the last pressed button info
    bsf first_click_flag, 0	    ;Set first_click_flag
    movlw underscore_chr
    movwf current_chr		    ;disp4 should be underscore after inact interrupt
    goto timer1_interrupt_exit      ;exit from interrupt service routine
    
    
;;;;;;;;;;;;;;;;;;;;;;;; Timer interrupt handler part ;;;;;;;;;;;;;;;;;;;;;;;;;;
timer_interrupt:
    bcf	    INTCON, 2               ;Clear TMR0IF
    incf    sec_counter, f          ;Timer interrupt handler part begins here by incrementing count variable
    movf    sec_counter, w          ;Move count to Working register
    sublw   d'20'                   ;Decrement 20 from Working register
    btfss   STATUS, Z               ;Is the result Zero?
    goto    timer_interrupt_exit    ;No, then exit from interrupt service routine
    clrf    sec_counter             ;Yes, then clear count variable
    DCFSNZ  global_countdown	    ;Check if countdown reached to zero
    goto global_countdown_end	    ;Yes, goto global_countdown_end label

timer_interrupt_exit:
    movlw   0x0B                ;FFFF-BDB=62500; 62500*8*20 = 10000000 instruction cycle;
    movwf   TMR0H
    movlw   0xDB
    movwf   TMR0L
    retfie 1

global_countdown_end:
    movlw   0x0B
    movwf   TMR1H
    movlw   0xDB
    movwf   TMR1L
    bsf     T1CON, 0    ;Enable Timer1 by setting TMR1ON to 1
    clrf state_reg	
    bsf state_reg, 2	;Update the state as Message Read state
    retfie 1

;;;;;;;;;;;;;;;;;;; RB4 interrupt-on-change handler part ;;;;;;;;;;;;;;;;;;;;;
rb4_interrupt:
    movf    PORTB, w            ;Read PORTB to working register
    movwf   portb_var           ;Save it to shadow register
    btfsc   portb_var, 4        ;Test its 4th bit whether it is cleared
    goto    rb4_interrupt_released  ; RB4 is 1, button is released, so change state

rb4_interrupt_pressed:
    movf    portb_var, w        ;Put shadow register to W
    movwf   LATB                ;Write content of W to actual PORTB, so that we will be able to clear RBIF
    bcf     INTCON, 0           ;Clear PORTB on change FLAG
    retfie 1

rb4_interrupt_released:
    btfsc state_reg, 0 ; Check if current state is message_write_state
    goto rb4_interrupt_write	; Yes, then goto rb4_interrupt_write 
    btfsc state_reg, 1 ; Check if current state is message_review_state
    goto rb4_interrupt_review	; Yes, then goto rb4_interrupt_review

rb4_interrupt_released_exit:
    movf    portb_var, w        ;Put shadow register to W
    movwf   LATB                ;Write content of W to actual PORTB, so that we will be able to clear RBIF
    bcf     INTCON, 0           ;Clear PORTB on change FLAG
    retfie 1

rb4_interrupt_write:
    bcf     T1CON, 0		; Disable Timer1 by setting TMR1ON to 1
				; to pause inactivity interrupt
    clrf state_reg
    bsf state_reg, 1		; Update the state as Message Review state
    clrf last_button		; Clear the last pressed button info
    movlw underscore_chr
    movwf current_chr		; Discard the current chr and set it as underscore
    movlw d'1'
    movwf review_conf_state	; Reset the review configuration state
    goto rb4_interrupt_released_exit

rb4_interrupt_review:
    bsf first_click_flag, 0
    clrf state_reg
    bsf state_reg, 0		; Update the state as Message Write state
    goto rb4_interrupt_released_exit

    
ONES_TABLE:
    movwf dumb_var
    incf dumb_var
    DCFSNZ dumb_var
    RETLW zero_num
    DCFSNZ dumb_var
    RETLW one_num
    DCFSNZ dumb_var
    RETLW two_num
    DCFSNZ dumb_var
    RETLW three_num
    DCFSNZ dumb_var
    RETLW four_num
    DCFSNZ dumb_var
    RETLW five_num
    DCFSNZ dumb_var
    RETLW six_num
    DCFSNZ dumb_var
    RETLW seven_num
    DCFSNZ dumb_var
    RETLW eight_num
    RETLW nine_num
    
    

;;;;;;;;;;;; Update Seven Segment Display ;;;;;;;;;;;;
update_display:
    btfsc state_reg, 0          ;Check if the current state is Message Write state
    goto update_write		;Yes, then goto update_write
    btfsc state_reg, 2		;Check if the current state is Message Read state
    goto update_read		;Yes, then goto update_read
    movf review_conf_state, w
    DCFSNZ WREG                
    goto review_conf_1
    DCFSNZ WREG 
    goto review_conf_2
    goto review_conf_3

review_conf_1:
    movff chr1, disp1_val
    movff chr2, disp2_val
    movff chr3, disp3_val
    movff chr4, disp4_val
    return
    
review_conf_2:
    movff chr2, disp1_val
    movff chr3, disp2_val
    movff chr4, disp3_val
    movff chr5, disp4_val
    return
    
review_conf_3:
    movff chr3, disp1_val
    movff chr4, disp2_val
    movff chr5, disp3_val
    movff chr6, disp4_val
    return
    
 
update_read:
    movf read_conf_state, w
    DCFSNZ WREG                
    goto review_conf_1
    DCFSNZ WREG 
    goto review_conf_2
    goto review_conf_3

update_write:
    movff last_saved_chr, disp3_val	;Assign last saved character to disp3_val
    movff current_chr, disp4_val	;Assign current character to disp4_val
update_countdown:
    movf    global_countdown, w          ;Move countdown value to working register
    xorlw   d'20'			 ;Check if wreg equals 20
    btfsc   STATUS, Z			 ;Is the result zero?
    goto    display_20			 ;Yes, then goto display_20
    movlw   d'10'
    subwf   global_countdown, 0 
    BN display_less_than_ten             ;Branch if global_countdown < 10
    movlw   one_num
    movwf   disp1_val
    movff   global_countdown, sub_tmp_var
    movlw   d'10'
    subwf   sub_tmp_var, 0		 ;To get the rightmost decimal digit subtract ten
    call ONES_TABLE			 ;Get the rightmost digit
    movwf   disp2_val			 ;Assign rightmost digit to disp2_val
    return
    
display_less_than_ten:
    movlw   zero_num
    movwf   disp1_val
    movf   global_countdown, w
    call ONES_TABLE
    movwf   disp2_val
    return

display_20:
    movlw   two_num
    movwf   disp1_val
    movlw   zero_num
    movwf   disp2_val
    return

refresh_display:
    movlw   b'00000100'
    movwf   LATA
    movff   disp1_val, LATD	;Update the disp1 with disp1_val
    call init_delay
    movlw   b'00001000'
    movwf   LATA
    movff   disp2_val, LATD	;Update the disp2 with disp2_val
    call init_delay
    movlw   b'00010000'
    movwf   LATA
    movff   disp3_val, LATD	;Update the disp3 with disp3_val
    call init_delay
    movlw   b'00100000'
    movwf   LATA
    movff   disp4_val, LATD	;Update the disp4 with disp4_val
    call init_delay
    return

    
end