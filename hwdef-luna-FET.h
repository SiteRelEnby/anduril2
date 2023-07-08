#ifndef HWDEF_EMISAR_D4_H
#define HWDEF_EMISAR_D4_H

//copied from hwdef-emisar-d4.h

/*           driver layout
 *           ----
 *   Reset -|1  8|- VCC
 * eswitch -|2  7|-
 * AUX LED -|3  6|- PWM (FET)
 *     GND -|4  5|-
 *           ----
 */

#define LAYOUT_DEFINED

#define PWM_CHANNELS 1

//#define AUXLED_PIN   PB4    // pin 3

#ifndef SWITCH_PIN
#define SWITCH_PIN   PB3    // pin 2
#define SWITCH_PCINT PCINT3 // pin 2 pin change interrupt
#endif

#ifndef PWM1_PIN
#define PWM1_PIN PB1        // pin 5, 1x7135 PWM
#define PWM1_LVL OCR0B      // OCR0A is the output compare register for PB1
#endif

#define ADC_PRSCL   0x07    // clk/128

// average drop across diode on this hardware
#ifndef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V
#endif

//TODO(?):
//#define PWM1_PHASE_RESET_OFF  // force reset while shutting off
//#define PWM1_PHASE_RESET_ON   // force reset while turning on
//#define PWM1_PHASE_SYNC       // manual sync while changing level
#define FAST 0x23           // fast PWM channel 1 only
#define PHASE 0x21          // phase-correct PWM channel 1 only

#define USE_INDICATOR_LED
#define USE_INDICATOR_LED_WHILE_RAMPING
#define AUXLED_PIN   PB4    // pin 3

//tactical or SOS, pick one
#define USE_TACTICAL_MODE
#undef USE_SOS_MODE

#endif
