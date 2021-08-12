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

 
variables udata_acs
init_counter_1 res 1
init_counter_2 res 1
init_counter_3 res 1
clock_counter_high res 1
clock_counter_low res 1
clock_flag res 1
delay_counter_high res 1
delay_counter_low res 1
is_staged res 1
is_active res 1
release_flag res 1
saved_row_0 res 1
saved_row_1 res 1
saved_row_2 res 1
temp_row res 1
temp_side res 1
right_edge res 1
left_edge res 1
row_select_state res 1
drawing_state res 1




INIT_DELAY_COUNTER equ 0x32

 
org 0x0000
    goto init

org 0x0008
    goto $


init_delay:
    nop
    do_while_init_counter_1_not_zero:
        do_while_init_counter_2_not_zero:
            do_while_init_counter_3_not_zero:
                decf init_counter_3 ; 
                bnz do_while_init_counter_3_not_zero
            end_do_while_init_counter_3_not_zero:
            decf init_counter_2
            bnz do_while_init_counter_2_not_zero
        end_do_while_init_counter_2_not_zero:
        decf init_counter_1
        bnz do_while_init_counter_1_not_zero
    end_do_while_init_counter_1_not_zero:
    
    return
    

init:
    MOVLW 0x0F
    MOVWF ADCON1
    clrf PORTA
    clrf PORTC
    clrf PORTD
    clrf TRISA ;set trisx as output
    clrf TRISC
    clrf TRISD
    clrf is_staged 
    clrf is_active 
    clrf release_flag
    MOVLW B'00000001'
    MOVWF row_select_state
    clrf saved_row_0
    clrf saved_row_1
    clrf saved_row_2
    clrf temp_row
    clrf temp_side
    clrf right_edge
    clrf left_edge
    clrf drawing_state
    MOVLW D'90'
    MOVWF clock_counter_high
    setf clock_counter_low
    clrf clock_flag
init_complete:
    setf init_counter_3
    setf init_counter_2
    movlw INIT_DELAY_COUNTER
    movwf init_counter_1
    setf LATA
    setf LATC
    setf LATD
    call init_delay
    clrf LATA
    clrf LATC
    clrf LATD
sec_passed:
    goto main


    
rb0_check:
    btfss PORTB, 0 
    goto rb0_pressed ; currently pressed
rb0_unpressed:
    btfsc is_staged, 0
    goto rb0_noise
    btfsc is_active, 0
    goto rb0_released
    return

rb0_noise:
    clrf is_staged
    return

rb0_released:
    clrf is_active
    MOVLW B'00000001'
    MOVWF release_flag
    return


rb0_pressed:
    btfsc is_active, 0
    return
    btfss is_staged, 0
    goto rb0_pressed_init ; first time pressed
    DECFSZ delay_counter_low
    return
    DECFSZ delay_counter_high
    return
rb0_active:
    clrf is_staged
    MOVLW B'00000001'
    MOVWF is_active
    return

rb0_pressed_init:
    MOVLW B'00000001'
    MOVWF is_staged
	MOVLW D'5'
	MOVWF delay_counter_high
	setf delay_counter_low
    return


rb1_check:
    btfss PORTB, 1
    goto rb1_pressed ; currently pressed
rb1_unpressed:
    btfsc is_staged, 1
    goto rb1_noise
    btfsc is_active, 1
    goto rb1_released
    return

rb1_noise:
    clrf is_staged
    return

rb1_released:
    clrf is_active
    MOVLW B'00000010'
    MOVWF release_flag
    return


rb1_pressed:
    btfsc is_active, 1
    return
    btfss is_staged, 1
    goto rb1_pressed_init ; first time pressed
    DECFSZ delay_counter_low
    return
    DECFSZ delay_counter_high
    return
rb1_active:
    clrf is_staged
    MOVLW B'00000010'
    MOVWF is_active
    return

rb1_pressed_init:
    MOVLW B'00000010'
    MOVWF is_staged
	MOVLW D'5'
	MOVWF delay_counter_high
	setf delay_counter_low
    return


rb2_check:
    btfss PORTB, 2
    goto rb2_pressed ; currently pressed
rb2_unpressed:
    btfsc is_staged, 2
    goto rb2_noise
    btfsc is_active, 2
    goto rb2_released
    return

rb2_noise:
    clrf is_staged
    return

rb2_released:
    clrf is_active
    MOVLW B'00000100'
    MOVWF release_flag
    return


rb2_pressed:
    btfsc is_active, 2
    return
    btfss is_staged, 2
    goto rb2_pressed_init ; first time pressed
    DECFSZ delay_counter_low
    return
    DECFSZ delay_counter_high
    return
rb2_active:
    clrf is_staged
    MOVLW B'00000100'
    MOVWF is_active
    return

rb2_pressed_init:
    MOVLW B'00000100'
    MOVWF is_staged
	MOVLW D'5'
	MOVWF delay_counter_high
	setf delay_counter_low
    return


rb3_check:
    btfss PORTB, 3 
    goto rb3_pressed ; currently pressed
rb3_unpressed:
    btfsc is_staged, 3
    goto rb3_noise
    btfsc is_active, 3
    goto rb3_released
    return

rb3_noise:
    clrf is_staged
    return

rb3_released:
    clrf is_active
    MOVLW B'00001000'
    MOVWF release_flag
    return


rb3_pressed:
    btfsc is_active, 3
    return
    btfss is_staged, 3
    goto rb3_pressed_init ; first time pressed
    DECFSZ delay_counter_low
    return
    DECFSZ delay_counter_high
    return
rb3_active:
    clrf is_staged
    MOVLW B'00001000'
    MOVWF is_active
    return

rb3_pressed_init:
    MOVLW B'00001000'
    MOVWF is_staged
    MOVLW D'5'
    MOVWF delay_counter_high
    setf delay_counter_low
    return


row_select_0:
    btfsc release_flag, 1
    goto row_select_0_rb1
    btfsc release_flag, 0
    goto row_select_0_rb0
    btfsc release_flag, 3
    goto row_select_0_rb3
    btfsc release_flag, 2
    clrf release_flag
    MOVF clock_flag, W
    MOVWF LATA
    return

row_select_0_rb0:
    clrf release_flag
    comf saved_row_0
    return

row_select_0_rb1:
    clrf release_flag
    MOVLW B'00000010'
    MOVWF row_select_state
    MOVF saved_row_0, W
    MOVWF LATA
    goto row_select_1

row_select_0_rb3:
    clrf release_flag
    clrf row_select_state
    MOVLW B'00000001'
    MOVWF drawing_state
    MOVLW B'00000001'
    MOVWF temp_row
    MOVWF right_edge
    MOVWF left_edge
    clrf temp_side
    return


row_select_1:
    btfsc release_flag, 1
    goto row_select_1_rb1
    btfsc release_flag, 0
    goto row_select_1_rb0
    btfsc release_flag, 3
    goto row_select_1_rb3
    btfsc release_flag, 2
    goto row_select_1_rb2
    MOVF clock_flag, W
    MOVWF LATC
    return

row_select_1_rb0:
    clrf release_flag
    comf saved_row_1
    return

row_select_1_rb1:
    clrf release_flag
    MOVLW B'00000100'
    MOVWF row_select_state
    MOVF saved_row_1, W
    MOVWF LATC
    goto row_select_2

row_select_1_rb2:
    clrf release_flag
    MOVLW B'00000001'
    MOVWF row_select_state
    MOVF saved_row_1, W
    MOVWF LATC
    goto row_select_0

row_select_1_rb3:
    clrf release_flag
    clrf row_select_state
    MOVLW B'00000010'
    MOVWF drawing_state
    MOVLW B'00000001'
    MOVWF temp_row
    MOVWF right_edge
    MOVWF left_edge
    clrf temp_side
    return


row_select_2:
    btfsc release_flag, 2
    goto row_select_2_rb2
    btfsc release_flag, 0
    goto row_select_2_rb0
    btfsc release_flag, 3
    goto row_select_2_rb3
    btfsc release_flag, 1
    clrf release_flag
    MOVF clock_flag, W
    MOVWF LATD
    return

row_select_2_rb0:
    clrf release_flag
    comf saved_row_2
    return

row_select_2_rb2:
    clrf release_flag
    MOVLW B'00000010'
    MOVWF row_select_state
    MOVF saved_row_2, W
    MOVWF LATD
    goto row_select_1

row_select_2_rb3:
    clrf release_flag
    clrf row_select_state
    MOVLW B'00000100'
    MOVWF drawing_state
    MOVLW B'00000001'
    MOVWF temp_row
    MOVWF right_edge
    MOVWF left_edge
    clrf temp_side
    return


drawing_0:
    btfsc release_flag, 0
    goto drawing_0_rb0
    btfsc release_flag, 1
    goto drawing_0_rb1
    btfsc release_flag, 2
    goto drawing_0_rb2
    btfsc release_flag, 3
    goto drawing_0_rb3
    MOVF temp_row, W
    IORWF saved_row_0, W
    MOVWF LATA
    return


drawing_0_rb0:
    clrf release_flag
    comf temp_side
    return

drawing_0_rb2:
    clrf release_flag
    TSTFSZ temp_side
    goto drawing_0_rb2_left
drawing_0_rb2_right:
    btfsc right_edge, 7
    return
    RLCF right_edge, W
    RLCF right_edge, F
    MOVF right_edge, W
    IORWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_0, W
    MOVWF LATA
    return

drawing_0_rb2_left:
	MOVF right_edge, W
	SUBWF left_edge, W
	BTFSS STATUS, Z
    goto drawing_0_rb2_left_okay
    return

drawing_0_rb2_left_okay:
    COMF left_edge, W
    ANDWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_0, W
    MOVWF LATA
    RLCF left_edge, W
    RLCF left_edge, F
    return


drawing_0_rb1:
    clrf release_flag
    TSTFSZ temp_side
    goto drawing_0_rb1_left
drawing_0_rb1_right:
    MOVF left_edge, W
    CPFSEQ right_edge ; skip if equals
    goto drawing_0_rb1_right_okay
    return

drawing_0_rb1_right_okay:
    COMF right_edge, W
    ANDWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_0, W
    MOVWF LATA
    RRCF right_edge, W
    RRCF right_edge, F
    return

drawing_0_rb1_left:
    btfsc left_edge, 0
    return
    RRCF left_edge, W
    RRCF left_edge, F
    MOVF left_edge, W
    IORWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_0, W
    MOVWF LATA
    return

drawing_0_rb3:
    clrf release_flag
    clrf drawing_state
    MOVLW B'00000001'
    MOVWF row_select_state
    MOVF temp_row, W
    IORWF saved_row_0, F
    goto row_select_0


drawing_1:
    btfsc release_flag, 0
    goto drawing_1_rb0
    btfsc release_flag, 1
    goto drawing_1_rb1
    btfsc release_flag, 2
    goto drawing_1_rb2
    btfsc release_flag, 3
    goto drawing_1_rb3
    MOVF temp_row, W
    IORWF saved_row_1, W
    MOVWF LATC
    return


drawing_1_rb0:
    clrf release_flag
    comf temp_side
    return

drawing_1_rb2:
    clrf release_flag
    TSTFSZ temp_side
    goto drawing_1_rb2_left
drawing_1_rb2_right:
    btfsc right_edge, 7
    return
    RLCF right_edge, W
    RLCF right_edge, F
    MOVF right_edge, W
    IORWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_1, W
    MOVWF LATC
    return

drawing_1_rb2_left:
    MOVF right_edge, W
    SUBWF left_edge, W
    BTFSS STATUS, Z
    goto drawing_1_rb2_left_okay
    return

drawing_1_rb2_left_okay:
    COMF left_edge, W
    ANDWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_1, W
    MOVWF LATC
    RLCF left_edge, W
    RLCF left_edge, F
    return


drawing_1_rb1:
    clrf release_flag
    TSTFSZ temp_side
    goto drawing_1_rb1_left
drawing_1_rb1_right:
    MOVF left_edge, W
    CPFSEQ right_edge ; skip if equals
    goto drawing_1_rb1_right_okay
    return

drawing_1_rb1_right_okay:
    COMF right_edge, W
    ANDWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_1, W
    MOVWF LATC
    RRCF right_edge, W
    RRCF right_edge, F
    return

drawing_1_rb1_left:
    btfsc left_edge, 0
    return
    RRCF left_edge, W
    RRCF left_edge, F
    MOVF left_edge, W
    IORWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_1, W
    MOVWF LATC
    return

drawing_1_rb3:
    clrf release_flag
    clrf drawing_state
    MOVLW B'00000010'
    MOVWF row_select_state
    MOVF temp_row, W
    IORWF saved_row_1, F
    goto row_select_1



drawing_2:
    btfsc release_flag, 0
    goto drawing_2_rb0
    btfsc release_flag, 1
    goto drawing_2_rb1
    btfsc release_flag, 2
    goto drawing_2_rb2
    btfsc release_flag, 3
    goto drawing_2_rb3
    MOVF temp_row, W
    IORWF saved_row_2, W
    MOVWF LATD
    return


drawing_2_rb0:
    clrf release_flag
    comf temp_side
    return

drawing_2_rb2:
    clrf release_flag
    TSTFSZ temp_side
    goto drawing_2_rb2_left
drawing_2_rb2_right:
    btfsc right_edge, 7
    return
    RLCF right_edge, W
    RLCF right_edge, F
    MOVF right_edge, W
    IORWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_2, W
    MOVWF LATD
    return

drawing_2_rb2_left:
    MOVF right_edge, W
    SUBWF left_edge, W
    BTFSS STATUS, Z
    goto drawing_2_rb2_left_okay
    return

drawing_2_rb2_left_okay:
    COMF left_edge, W
    ANDWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_2, W
    MOVWF LATD
    RLCF left_edge, W
    RLCF left_edge, F
    return


drawing_2_rb1:
    clrf release_flag
    TSTFSZ temp_side
    goto drawing_2_rb1_left
drawing_2_rb1_right:
    MOVF left_edge, W
    CPFSEQ right_edge ; skip if equals
    goto drawing_2_rb1_right_okay
    return

drawing_2_rb1_right_okay:
    COMF right_edge, W
    ANDWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_2, W
    MOVWF LATD
    RRCF right_edge, W
    RRCF right_edge, F
    return

drawing_2_rb1_left:
    btfsc left_edge, 0
    return
    RRCF left_edge, W
    RRCF left_edge, F
    MOVF left_edge, W
    IORWF temp_row, F
    MOVF temp_row, W
    IORWF saved_row_2, W
    MOVWF LATD
    return

drawing_2_rb3:
    clrf release_flag
    clrf drawing_state
    MOVLW B'00000100'
    MOVWF row_select_state
    MOVF temp_row, W
    IORWF saved_row_2, F
    goto row_select_2





msec200_passed:
	MOVLW D'90'
	MOVWF clock_counter_high
	setf clock_counter_low
	comf clock_flag
	return


main:

    DECFSZ clock_counter_low
    goto no_clock_hit
    DECFSZ clock_counter_high
    goto no_clock_hit
    call msec200_passed

no_clock_hit:
    
    call rb0_check
    call rb1_check
    call rb2_check
    call rb3_check

    btfsc row_select_state, 0
        call row_select_0
    btfsc row_select_state, 1
        call row_select_1
    btfsc row_select_state, 2
        call row_select_2


    btfsc drawing_state, 0
        call drawing_0
    btfsc drawing_state, 1
        call drawing_1
    btfsc drawing_state, 2
        call drawing_2

    goto main
    
end




