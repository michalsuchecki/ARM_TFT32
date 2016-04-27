#ifndef LIBS_TFT_TOUCH_H_
#define LIBS_TFT_TOUCH_H_

#include "common.h"

// czêstotliwosc z jaka aktualizujemy dane np 25/sek
#define REFRESH_RATE 10

// Piny
#define T_CLK 25
#define T_CS 26
#define T_DIN 27
#define T_DOUT 29
#define T_IRQ 30

//--------------------------------------------------------

#define PROCESS_TIME (1000/REFRESH_RATE)

enum TouchState
{
	T_Untouched,	// Gdy nie dotykamy paluchem
	T_Touched,		// Gdy przytrzymujemy paluch na ekranie
	//T_Moving,		// Gdy przeci¹gamy paluch po ekranie [TODO]
	T_Released		// Gdy puœcimy paluch
};

class Touch
{
public:
	Touch();
	bool ProcessTouch(uint16_t delta_time);
	word GetX();
	word GetY();
	TouchState GetState();
	bool DataAvailable();
	void (*OnTouch)(int x, int y, TouchState state);
private:
	void DataRead();
	void DeviceWrite(byte data);
	word DeviceRead();
private:
	word x,y;
	uint8_t step_x, step_y;
	//uint16_t start_x, start_y;
	uint16_t min_x, min_y, max_x, max_y;
	regtype *P_CLK, *P_CS, *P_DIN, *P_DOUT, *P_IRQ;
	regsize B_CLK, B_CS, B_DIN, B_DOUT, B_IRQ;
	TouchState State;
	uint16_t delta;
};

#endif
