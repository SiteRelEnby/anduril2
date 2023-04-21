// Sofirn SP36 (small Q8) config options for Anduril using the Attiny1616
// same as  the  BLF Q8, mostly
#include "cfg-blf-q8-t1616.h"
#undef MODEL_NUMBER
#define MODEL_NUMBER "0614"
// ATTINY: 1616

// voltage readings were a little high with the Q8 value
#undef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V, not 0.35V

// stop panicking at ~60% power or ~3000 lm
#ifdef THERM_FASTER_LEVEL
#undef THERM_FASTER_LEVEL
#endif
#define THERM_FASTER_LEVEL 130
