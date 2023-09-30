// Mateminco MT35-Mini / Astrolux FT03
// Copyright (C) 2022-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later
#pragma once

/*
 *           ----
 *   Reset -|1  8|- VCC
 * eswitch -|2  7|- Aux LED
 *  1x7135 -|3  6|- NC
 *     GND -|4  5|- FET
 *           ----
 */
#include <avr/io.h>
//#define NUM_CHANNEL_MODES   2
#define NUM_CHANNEL_MODES   1
enum CHANNEL_MODES {
    CM_MAIN = 0//,
//    CM_AUX
};
#define PWM_BITS      8       // attiny85 only supports up to 8 bits
#define PWM_GET       PWM_GET8
#define PWM_DATATYPE  uint8_t
#define PWM_DATATYPE2 uint16_t
#define PWM1_DATATYPE uint8_t   // 1x7135 ramp
#define PWM2_DATATYPE uint8_t   // DD FET ramp

//original D4 is essentially the same as this light
#define HWDEF_C_FILE hwdef-emisar-d4.c

#define PWM_TOP_INIT 255

#ifdef USE_CHANNEL_MODE_ARGS
#undef USE_CHANNEL_MODE_ARGS
#endif

#define PWM_CHANNELS 2

#ifndef SWITCH_PIN
#define SWITCH_PIN   PB3    // pin 2
#define SWITCH_PCINT PCINT3 // pin 2 pin change interrupt
#endif

#ifndef PWM1_PIN
#define PWM1_PIN PB4        // pin 3, 1x7135 PWM
#define PWM1_LVL OCR1B      // OCR1B is the output compare register for PB0
#endif
#define CH1_PWM PWM1_LVL

#ifndef PWM2_PIN
#define PWM2_PIN PB0        // pin 5, FET PWM
#define PWM2_LVL OCR0A      // OCR0A is the output compare register for PB4
#endif
#define CH2_PWM PWM2_LVL

#define ADC_PRSCL   0x07    // clk/128

// average drop across diode on this hardware
#ifndef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 7  // add 0.35V
#endif

// lighted button
#ifndef AUXLED_PIN
#define AUXLED_PIN   PB2    // pin 7
#endif

#define FAST 0xA3           // fast PWM both channels
#define PHASE 0xA1          // phase-correct PWM both channels

inline void hwdef_setup() {
    // configure PWM channels
    DDRB = (1 << PWM1_PIN)
         | (1 << PWM2_PIN);

    TCCR0B = 0x01; // pre-scaler for timer (1 => 1, 2 => 8, 3 => 64...)
    TCCR0A = PHASE;

    // configure e-switch
    PORTB = (1 << SWITCH_PIN);  // e-switch is the only input
    PCMSK = (1 << SWITCH_PIN);  // pin change interrupt uses this pin
}

#define LAYOUT_DEFINED

