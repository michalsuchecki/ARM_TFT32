#ifndef LIBS_MAX31855_MAX31855_H_
#define LIBS_MAX31855_MAX31855_H_

#include "Arduino.h"

/*
 * GND - 1 -|-------| - 8 - N/C
 *          |*      |
 *  T- - 2 -|       | - 7 - SOut
 *          |  MAX  |
 *  T+ - 3 -| 31588 | - 6 - _CS_
 *          |       |
 * VCC - 4 -|-------| - 5 - SCK
 */

#define SO  3
#define CS  4
#define SCK 5

// --------------------------------------------------

#define cbi(reg, bitmask) *reg &= ~bitmask
#define sbi(reg, bitmask) *reg |= bitmask
#define rbi(reg, bitmask) ((*reg) & bitmask)

#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

class MAX31855
{
public:
	MAX31855();
	double ReadInternalTemp();
	double ReadCelsiusTemp();
private:
	uint32_t ReadData();
};

#endif
