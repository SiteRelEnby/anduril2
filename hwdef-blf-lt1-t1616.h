// BLF LT1 driver layout using the Attiny1616
// Copyright (C) 2021-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

/*
 * Driver pinout:
 * eSwitch:     PA5
 * Aux LED:     PB5
 * PWM warm:    PB0 (TCA0 WO0)
 * PWM neutral: PB1 (TCA0 WO1)
 * Voltage:     VCC
 */


#define LAYOUT_DEFINED

#include <avr/io.h>

#define HWDEF_C_FILE hwdef-blf-lt1-t1616.c

// allow using aux LEDs as extra channel modes
#include "chan-rgbaux.h"

// channel modes:
// * 0. channel 1 only
// * 1. channel 2 only
// * 2. both channels, tied together, max "200%" power
// * 3. both channels, manual blend, max "100%" power
// * 4. both channels, auto blend, reversible
#define NUM_CHANNEL_MODES 6
enum channel_modes_e {
    CM_CH1 = 0,
    CM_CH2,
    CM_BOTH,
    CM_BLEND,
    CM_AUTO,
    CM_AUX
};

// right-most bit first, modes are in fedcba9876543210 order
#define CHANNEL_MODES_ENABLED 0b0000000000011111
#define USE_CHANNEL_MODE_ARGS
// _, _, _, 128=middle CCT, 0=warm-to-cool
#define CHANNEL_MODE_ARGS     0,0,0,128,0,0

// can use some of the common handlers
#define USE_CALC_2CH_BLEND

#define PWM_DATATYPE uint8_t
#define PWM1_DATATYPE PWM_DATATYPE
#define PWM2_DATATYPE PWM_DATATYPE
#define PWM_TOP_INIT 255

#ifdef ATTINY
#undef ATTINY
#endif
#define ATTINY 1616
#include <avr/io.h>

#define PWM_CHANNELS 2

#ifndef SWITCH_PIN
#define SWITCH_PIN     PIN5_bp
#define SWITCH_PORT    VPORTA.IN
#define SWITCH_ISC_REG PORTA.PIN2CTRL
#define SWITCH_VECT    PORTA_PORT_vect
#define SWITCH_INTFLG  VPORTA.INTFLAGS
#endif


// usually PWM1_LVL would be a hardware register, but we need to abstract
// it out to a soft brightness value, in order to handle tint ramping
// (this allows smooth thermal regulation to work, and makes things
//  otherwise simpler and easier)
uint8_t PWM1_LVL;

// warm tint channel
#ifndef PWM1_PIN
#define PWM1_PIN PB1                //
//#define TINT1_LVL TCA0.SINGLE.CMP1  // CMP1 is the output compare register for PB1
#define CH1_PWM  TCA0.SINGLE.CMP1  // CMP1 is the output compare register for PB1
#endif

// cold tint channel
#ifndef PWM2_PIN
#define PWM2_PIN PB0                //
//#define TINT2_LVL TCA0.SINGLE.CMP0  // CMP0 is the output compare register for PB0
#define CH2_PWM TCA0.SINGLE.CMP0  // CMP0 is the output compare register for PB0
#endif

// average drop across diode on this hardware
#ifndef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 7  // add 0.35V
#endif


// lighted button
#ifndef AUXLED_PIN
#define AUXLED_PIN  PIN5_bp
#define AUXLED_PORT PORTB
#endif


// with so many pins, doing this all with #ifdefs gets awkward...
// ... so just hardcode it in each hwdef file instead
inline void hwdef_setup() {

    // set up the system clock to run at 5 MHz instead of the default 3.33 MHz
    _PROTECTED_WRITE( CLKCTRL.MCLKCTRLB, CLKCTRL_PDIV_4X_gc | CLKCTRL_PEN_bm );

    //VPORTA.DIR = ...;
    VPORTB.DIR = PIN0_bm | PIN1_bm | PIN5_bm;  // Outputs: Aux LED and PWMs
    //VPORTC.DIR = ...;

    // enable pullups on the unused pins to reduce power
    PORTA.PIN0CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN1CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm | PORT_ISC_BOTHEDGES_gc;  // eSwitch
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;

    //PORTB.PIN0CTRL = PORT_PULLUPEN_bm; // cold tint channel
    //PORTB.PIN1CTRL = PORT_PULLUPEN_bm; // warm tint channel
    PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTB.PIN3CTRL = PORT_PULLUPEN_bm;
    PORTB.PIN4CTRL = PORT_PULLUPEN_bm;
    //PORTB.PIN5CTRL = PORT_PULLUPEN_bm; // Aux LED

    PORTC.PIN0CTRL = PORT_PULLUPEN_bm;
    PORTC.PIN1CTRL = PORT_PULLUPEN_bm;
    PORTC.PIN2CTRL = PORT_PULLUPEN_bm;
    PORTC.PIN3CTRL = PORT_PULLUPEN_bm;

    // set up the PWM
    // TODO: add references to MCU documentation
    TCA0.SINGLE.CTRLB = TCA_SINGLE_CMP0EN_bm | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
    TCA0.SINGLE.PER = 255;
    TCA0.SINGLE.CTRLA = TCA_SINGLE_CLKSEL_DIV1_gc | TCA_SINGLE_ENABLE_bm;
}

