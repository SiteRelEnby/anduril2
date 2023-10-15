// adapted from wurkkos-ts10 15/10/2023
#pragma once

#include "chan-aux.c"

void set_level_zero();

void set_level_main(uint8_t level);
bool gradual_tick_main(uint8_t gt);


Channel channels[] = {
    { // main LEDs
        .set_level    = set_level_main,
        .gradual_tick = gradual_tick_main
    },
    { // aux LEDs
        .set_level    = set_level_aux,
        .gradual_tick = gradual_tick_null
    }
};


void set_level_zero() {
    PWM1_LVL = 0;
    PWM2_LVL = 0;
    //PWM_CNT = 0;  // reset phase
}

// single set of LEDs with 2 stacked power channels, DDFET+1 or DDFET+linear
void set_level_main(uint8_t level) {
    PWM_DATATYPE ch1_pwm = PWM_GET(pwm1_levels, level);
    PWM_DATATYPE ch2_pwm = PWM_GET(pwm2_levels, level);

    PWM1_LVL = ch1_pwm;
    PWM2_LVL = ch2_pwm;
    // wait to sync the counter and avoid flashes
    // (unnecessary w/ buffered registers)
    //while(actual_level && (PWM_CNT > (top - 32))) {}
    //PWM_TOP = top;
    // force reset phase when turning on from zero
    // (because otherwise the initial response is inconsistent)
    //if (! actual_level) PWM_CNT = 0;
}

bool gradual_tick_main(uint8_t gt) {
    PWM_DATATYPE pwm1 = PWM_GET(pwm1_levels, gt);
    PWM_DATATYPE pwm2 = PWM_GET(pwm2_levels, gt);

    GRADUAL_ADJUST_STACKED(pwm1, PWM1_LVL, PWM_TOP_INIT);
    GRADUAL_ADJUST_SIMPLE (pwm2, PWM2_LVL);

    if (   (pwm1 == PWM1_LVL)
        && (pwm2 == PWM2_LVL)
       ) {
        return true;  // done
    }
    return false;  // not done yet
}

