// Noctigon KR4 (no DD FET) PWM helper functions
// Copyright (C) 2020-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "chan-rgbaux.c"

// single set of LEDs with linear power channel
//void set_level_main(uint8_t level) {
//set_level_legacy(level);
/* 
    //written based on set_level_legacy
    if (level == 0){
      #ifdef LED_OFF_DELAY
        // for drivers with a slow regulator chip (eg, boost converter),
        // delay before turning off to prevent flashes
        delay_4ms(LED_OFF_DELAY/4);
      #endif
      // disable the power channel, if relevant
      #ifdef LED_ENABLE_PIN
        LED_ENABLE_PORT &= ~(1 << LED_ENABLE_PIN);
      #endif
      #ifdef LED2_ENABLE_PIN
        LED2_ENABLE_PORT &= ~(1 << LED2_ENABLE_PIN);
      #endif
    } else {
        // enable the power channel, if relevant
        #ifdef LED_ENABLE_PIN
            #ifdef LED_ON_DELAY
            uint8_t led_enable_port_save = LED_ENABLE_PORT;
            #endif

            LED_ENABLE_PORT |= (1 << LED_ENABLE_PIN);
            LED2_ENABLE_PORT |= (1 << LED2_ENABLE_PIN);

            // for drivers with a slow regulator chip (eg, boost converter),
            // delay before lighting up to prevent flashes
            #ifdef LED_ON_DELAY
            // only delay if the pin status changed
            if (LED_ENABLE_PORT != led_enable_port_save)
                delay_4ms(LED_ON_DELAY/4);
            #endif
        #endif
        // PWM array index = level - 1
        level --;

        #if PWM_CHANNELS >= 1
        PWM1_LVL = PWM_GET(pwm1_levels, level);
        #endif

        #ifdef USE_DYN_PWM
            uint16_t top = PWM_GET(pwm_tops, level);
            #if defined(PWM1_CNT) && defined(PWM1_PHASE_SYNC)
            // wait to ensure compare match won't be missed
            // (causes visible flickering when missed, because the counter
            //  goes all the way to 65535 before returning)
            // (see attiny1634 reference manual page 103 for a warning about
            //  the timing of changing the TOP value (section 12.8.4))
            // (but don't wait when turning on from zero, because
            //  it'll reset the phase below anyway)
            // to be safe, allow at least 32 cycles to update TOP
            while(actual_level && (PWM1_CNT > (top - 32))) {}
            #endif
            // pulse frequency modulation, a.k.a. dynamic PWM
            PWM1_TOP = top;
        #endif  // ifdef USE_DYN_PWM
        #if defined(PWM1_CNT) && defined(PWM1_PHASE_RESET_ON)
            // force reset phase when turning on from zero
            // (because otherwise the initial response is inconsistent)
            if (! actual_level) {
                PWM1_CNT = 0;
                #if defined(PWM2_CNT) && defined(PWM2_PHASE_RESET_ON)
                PWM2_CNT = 0;
                #endif
                #if defined(PWM3_CNT) && defined(PWM3_PHASE_RESET_ON)
                PWM3_CNT = 0;
                #endif
            }
        #endif
    }
    #ifdef USE_DYNAMIC_UNDERCLOCKING
    auto_clock_speed();
    #endif
}*/


    /* copied from KR4:
    if (level == 0) {
        CH1_PWM = 0;
        PWM_CNT = 0;  // reset phase
        CH1_ENABLE_PORT &= ~(1 << CH1_ENABLE_PIN);  // disable opamp
        return;
    }

    CH1_ENABLE_PORT |= (1 << CH1_ENABLE_PIN);  // enable opamp

    level --;  // PWM array index = level - 1
    PWM_DATATYPE ch1_pwm = PWM_GET(pwm1_levels, level);
    // pulse frequency modulation, a.k.a. dynamic PWM
    uint16_t top = PWM_GET16(pwm_tops, level);

    CH1_PWM = ch1_pwm;
    // wait to sync the counter and avoid flashes
    while(actual_level && (PWM_CNT > (top - 32))) {}
    PWM_TOP = top;
    // force reset phase when turning on from zero
    // (because otherwise the initial response is inconsistent)
    if (! actual_level) PWM_CNT = 0;
} */

bool gradual_tick_main(uint8_t gt) {
    PWM_DATATYPE pwm1 = PWM_GET(pwm1_levels, gt);

    GRADUAL_ADJUST_SIMPLE(pwm1, CH1_PWM);

    if (   (pwm1 == CH1_PWM)
       ) {
        return true;  // done
    }
    return false;  // not done yet
}

