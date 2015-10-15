#ifndef zeld_ow
#define zeld_ow
#include <stdint.h>
#include <avr/pgmspace.h>

#define PART0 256,p0_notes,p0_delays,sizeof(p0_notes)/sizeof(*(p0_notes)),sizeof(p0_delays)/sizeof(*(p0_delays))
#define PART1 256,p1_notes,p1_delays,sizeof(p1_notes)/sizeof(*(p1_notes)),sizeof(p1_delays)/sizeof(*(p1_delays))
#define PART2 1024,p2_notes,p2_delays,sizeof(p2_notes)/sizeof(*(p2_notes)),sizeof(p2_delays)/sizeof(*(p2_delays))
/*

    Part: 0
    Freq: 16000000
    Number of voices: 1
    Note length: 211
    Delay length: 211

    Part: 1
    Freq: 16000000
    Number of voices: 1
    Note length: 248
    Delay length: 248

    Part: 2
    Freq: 16000000
    Number of voices: 1
    Note length: 342
    Delay length: 342

*/
const uint8_t p0_notes[] PROGMEM = {
66,0,0,0,66,0,66,0,66,0,66,0,66,0,0,74,0,66,0,0,66,0,66,0,66,0,66,0,66,0,0,74,0,66,0,0,66,0,66,0,66,0,66,0,66,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,66,0,0,88,0,66,66,59,52,49,44,0,44,0,44,41,37,33,33,33,33,37,41,37,0,0,41,44,44,49,49,44,41,44,49,55,55,49,44,49,55,59,59,52,46,39,44,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,66,0,0,88,0,66,66,59,52,49,44,0,44,0,44,41,37,33,27,29,0,34,0,0,44,41,0,0,0,33,34,0,44,0,0,44,41,0,33,34,0,44,52,49,0,41,44,0,55,66,59,59,52,46,39,44,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0,88,0
};
const uint8_t p0_delays[] PROGMEM = {
32,1,2,8,4,1,4,1,4,2,4,1,6,1,4,4,1,22,1,4,4,1,4,1,4,2,4,1,6,1,4,4,1,24,1,2,4,1,4,1,4,2,4,1,6,2,3,1,3,1,6,2,3,1,3,1,6,2,3,1,3,1,6,2,6,2,11,1,4,24,4,4,4,4,4,4,32,8,6,2,5,6,5,37,6,5,6,5,5,6,1,4,6,31,16,8,4,4,32,8,8,8,4,4,32,8,8,8,4,4,32,16,6,2,3,1,3,1,6,2,3,1,3,1,6,2,3,1,3,1,6,2,6,2,11,1,4,24,4,4,4,4,4,4,32,8,6,2,5,6,5,48,16,8,8,27,1,4,16,35,1,4,8,16,8,8,27,1,4,16,32,16,16,8,8,32,16,32,16,16,8,8,32,16,8,4,4,32,16,6,2,3,1,3,1,6,2,3,1,3,1,6,2,3,1,3,1,6,2,6,2
};

const uint8_t p1_notes[] PROGMEM = {
105,0,0,0,105,0,105,0,105,0,105,0,118,0,0,118,0,118,0,0,118,0,118,0,118,0,112,0,0,112,0,112,0,0,112,0,112,0,112,0,112,0,112,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,105,0,0,105,105,118,105,0,105,105,99,88,79,74,66,66,59,52,49,44,44,74,66,59,55,83,83,74,66,59,55,55,55,59,66,55,0,0,74,74,74,83,74,0,0,74,74,83,74,83,0,83,88,83,83,74,66,74,83,88,88,99,88,88,83,74,83,88,94,94,88,79,79,70,66,59,70,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,105,0,0,105,105,118,105,0,105,105,99,88,79,74,66,66,59,52,49,44,44,74,66,59,55,46,49,0,59,0,0,70,62,0,0,0,55,59,0,70,0,0,70,62,0,55,59,0,70,70,83,0,62,66,0,88,112,94,94,88,79,79,70,66,59,70,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0,141,0
};
const uint8_t p1_delays[] PROGMEM = {
32,1,2,8,4,1,4,1,4,2,4,1,6,1,4,4,1,22,2,8,4,1,4,2,4,1,6,1,4,4,1,24,1,2,4,1,4,1,4,2,4,1,8,3,1,3,1,6,2,3,1,3,1,6,2,3,1,3,1,6,2,6,2,11,1,4,5,6,5,8,4,4,4,4,4,4,12,4,4,4,4,4,8,8,5,6,5,12,4,4,4,4,4,8,8,6,5,5,6,1,4,5,5,6,5,6,1,4,5,6,5,6,9,1,3,2,11,2,3,16,8,8,11,3,2,11,2,3,16,8,8,16,12,4,11,2,3,8,8,6,2,3,1,3,1,6,2,3,1,3,1,6,2,3,1,3,1,6,2,6,2,11,1,4,5,6,5,8,4,4,4,4,4,4,12,4,4,4,4,4,8,8,5,6,5,48,16,8,8,27,1,4,16,35,1,4,8,16,8,8,27,1,4,16,32,16,16,8,8,32,16,32,16,16,8,8,32,16,16,12,4,11,2,3,8,8,6,2,3,1,3,1,6,2,3,1,3,1,6,2,3,1,3,1,6,2,6,2
};

const uint8_t p2_notes[] PROGMEM = {
66,0,0,66,0,66,0,66,0,66,0,0,66,0,66,0,66,0,74,0,0,74,0,74,0,74,0,74,0,0,74,0,74,0,74,0,83,0,0,83,0,83,0,83,0,83,0,0,83,0,83,0,83,0,83,0,88,0,0,88,0,0,79,70,66,0,0,66,0,66,0,74,0,66,0,0,66,0,0,74,0,0,74,0,74,0,83,0,74,0,0,74,0,0,83,0,0,83,0,83,0,94,0,83,0,0,83,0,0,55,0,55,55,62,55,0,55,0,62,0,62,62,66,62,0,62,62,62,66,0,66,66,74,66,0,66,66,66,59,0,59,59,66,59,0,59,59,59,88,0,0,88,0,0,88,0,0,79,70,66,0,0,66,0,66,0,74,0,66,0,0,66,0,0,74,0,0,74,0,74,0,83,0,74,0,0,74,0,0,83,0,0,83,0,83,0,94,0,83,0,0,83,0,0,88,0,0,88,0,88,0,99,88,0,0,88,0,0,94,0,66,0,55,0,46,0,33,0,27,0,23,0,0,0,21,0,0,88,0,88,0,88,0,88,0,0,0,94,0,66,0,55,0,46,0,33,0,27,0,23,0,0,0,21,0,0,88,0,88,0,88,0,88,0,0,0,62,0,0,62,0,62,0,66,0,62,0,0,62,0,62,0,62,0,66,0,0,66,0,66,0,74,0,66,0,0,66,0,66,0,66,0,59,0,0,59,0,59,0,59,0,59,0,0,59,0,59,0,59,0,88,0,0,88,0,0,0,88,0,0,79,70
};
const uint8_t p2_delays[] PROGMEM = {
11,1,4,4,1,4,2,4,1,11,1,4,4,1,4,2,4,1,11,1,4,4,1,4,2,4,1,11,1,4,4,1,4,2,4,1,11,1,4,4,1,4,2,4,1,11,1,4,4,1,4,2,4,1,8,8,6,2,8,6,2,8,8,8,6,2,8,4,1,4,2,4,1,6,2,8,6,2,8,6,2,8,4,1,4,2,4,1,6,2,8,6,2,8,6,2,8,4,1,4,2,4,1,6,2,8,6,2,8,8,8,5,6,5,8,8,8,8,8,8,5,6,5,8,8,5,6,6,7,8,5,6,5,8,8,5,6,5,8,8,5,6,5,8,8,5,6,6,5,2,8,6,2,8,6,2,8,8,8,6,2,8,4,1,4,2,4,1,6,2,8,6,2,8,6,2,8,4,1,4,2,4,1,6,2,8,6,2,8,6,2,8,4,1,4,2,4,1,6,2,8,6,2,8,6,2,8,4,1,4,2,5,6,2,8,6,2,8,4,1,4,2,4,1,4,1,4,2,4,1,6,2,8,16,6,2,8,4,1,4,2,4,1,6,2,8,16,4,1,4,2,4,1,4,1,4,2,4,1,6,2,8,16,6,2,8,4,1,4,2,4,1,6,2,8,16,6,2,8,4,1,4,2,4,1,6,2,8,4,1,4,2,4,1,6,2,8,4,1,4,2,4,1,6,2,8,4,1,4,2,4,1,6,2,8,4,1,4,2,4,1,6,2,8,4,1,4,2,4,1,6,2,8,6,1,2,8,6,1,8,8,8
};

#endif
