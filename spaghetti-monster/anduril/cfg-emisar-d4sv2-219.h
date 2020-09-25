// Emisar D4Sv2-219 config options for Anduril
#include "cfg-emisar-d4sv2.h"
#undef MODEL_NUMBER
#define MODEL_NUMBER "0134"
// ATTINY: 1634

#undef PWM1_LEVELS
#undef PWM2_LEVELS
#undef PWM3_LEVELS
#define PWM1_LEVELS 1,1,2,2,3,3,4,5,5,6,7,8,9,10,11,12,13,17,18,19,20,21,22,24,26,28,30,33,35,38,41,44,47,50,54,57,61,65,69,74,79,84,89,94,100,106,113,119,126,134,142,150,158,167,176,186,196,207,218,230,242,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,12,16,21,25,30,35,41,46,52,58,64,71,77,84,92,99,107,115,124,133,142,151,161,172,182,193,205,217,229,242,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#define PWM3_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,4,6,7,9,10,12,13,15,17,18,20,22,24,26,28,30,33,35,37,40,43,45,48,50,53,56,59,62,65,69,72,76,80,83,87,91,95,99,104,108,113,117,123,127,132,138,143,148,154,160,166,172,178,185,192