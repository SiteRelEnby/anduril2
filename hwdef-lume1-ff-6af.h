#ifndef HWDEF_LUME1_1616_FET_6BUCK_H
#define HWDEF_LUME1_1616_FET_6BUCK_H

/* LUME1-FF-6AF Driver with ATTINY1616

    HW Config for 2022 Lume1 Driver with 6A Buck + FET
    FireFlyLite E12R, E07X, PL09mu etc (2022)

    Switching over from ATTINY1634 to 1-series yields the following gains:
    - Factory calibrated temperature sensor removes external temp sensor need
    - DAC output for LED current control instead of filtered PWM
    - 3-pin programming using UPDI interface instead of 6 pin ISP
    - UDR support using three current sense resistors + FET control
    - Voltage reading from VCC pin (removes need for Vreg) 

*/

#define LAYOUT_DEFINED

#ifdef ATTINY
#undef ATTINY
#endif
#define ATTINY 1616
#include <avr/io.h>

// average drop across diode on this hardware
#ifndef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 0  // PFET for RRP, essentially 0 v-drop
#endif

// Define e-switch Pin and ISR

#ifndef SWITCH_PIN   // PC3 
#define SWITCH_PIN     PIN3_bp
#define SWITCH_PORT    VPORTC.IN
#define SWITCH_ISC_REG PORTC.PIN3CTRL
#define SWITCH_VECT    PORTC_PORT_vect
#define SWITCH_INTFLG  VPORTC.INTFLAGS
#endif

// Define DAC control and PWM for FET

#define PWM_CHANNELS 2
#define PWM_BITS 8
#define USE_DYN_PWM  // dynamic frequency and speed

#define PWM1_LVL DAC0.DATA
#define PWM1_TOP VREF.CTRLA

#ifndef PWM2_PIN
#define PWM2_TOP TCA0.SINGLE.PER
#define PWM2_PIN PB2
#define PWM2_LVL TCA0.SINGLE.CMP2
#endif

// Define Pins

// For UDR Path 1 (dimmest mode) - PA7
#define LED_PATH1_PIN PIN7_bm
#define LED_PATH1_PORT PORTA_OUT

// For UDR Path 2 (low mode) - PB5
#define LED_PATH2_PIN PIN5_bm
#define LED_PATH2_PORT PORTB_OUT

// For UDR Path 2 (low mode) - PB5
#define LED_PATH2_PIN   PIN5_bm
#define LED_PATH2_PORT  PORTB_OUT

// For UDR Path 3 (brightest mode) - PB4
#define LED_PATH3_PIN   PIN4_bm
#define LED_PATH3_PORT  PORTB_OUT

// Enable pin for buck and op-amp - PB3
#define LED_ENABLE_PIN   PIN3_bm
#define LED_ENABLE_PORT  PORTB_OUT
#define LED_ON_DELAY 20  // how many ms to delay turning on the lights after enabling the channel

// Define Aux LED Pins

// lighted switch aux led (PC1)
#ifndef AUXLED_PIN
#define AUXLED_PIN  PIN1_bp
#define AUXLED_PORT PORTC
#endif

#define AUXLED_R_PIN   PIN0_bp    // PC0 / PP15
#define AUXLED_G_PIN   PIN0_bp    // PB0 / PP14
#define AUXLED_B_PIN   PIN1_bp    // PB1 / PP13

#define AUXLED_R_PORT   PORTC
#define AUXLED_G_PORT   PORTB
#define AUXLED_B_PORT   PORTB

// Others..
// with so many pins, doing this all with #ifdefs gets awkward...
// ... so just hardcode it in each hwdef file instead

inline void hwdef_setup() {

    // set up the system clock to run at 10 MHz instead of the default 3.33 MHz
    // TODO: for this DAC controlled-light, try to decrease the clock speed or use the ULP
    _PROTECTED_WRITE( CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_2X_gc | CLKCTRL_PEN_bm );

    // set pins as 1 for output pins

    VPORTA.DIR = PIN1_bm | PIN6_bm | PIN7_bm;
    VPORTB.DIR = PIN0_bm | PIN1_bm | PIN2_bm | PIN3_bm | PIN4_bm | PIN5_bm;
    VPORTC.DIR = PIN0_bm | PIN1_bm;

    // now set pullups on input pins, and unused pins (reduce power)

    PORTA.PIN0CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
    PORTC.PIN3CTRL = PORT_ISC_BOTHEDGES_gc;

    // set up the DAC (used for the buck in this case)

    VREF.CTRLA |= VREF_DAC0REFSEL_2V5_gc; 
    VREF.CTRLB |= VREF_DAC0REFEN_bm;
    DAC0.CTRLA = DAC_ENABLE_bm | DAC_OUTEN_bm;
    DAC0.DATA = 255;

    // set up the PWM (used for FET in this case)
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP2EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    TCA0.SINGLE.PER = 255-1;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV2_gc | TCA_SINGLE_ENABLE_bm;
}

#endif
