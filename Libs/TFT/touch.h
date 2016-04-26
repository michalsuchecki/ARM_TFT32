#ifndef LIBS_TFT_TOUCH_H_
#define LIBS_TFT_TOUCH_H_

#include "common.h"

/*
#define CAL_X 0x00378F66
#define CAL_Y 0x03C34155
#define CAL_S 0x000EF13F
*/

#define T_CLK 25
#define T_CS 26
#define T_DIN 27
#define T_DOUT 29
#define T_IRQ 30

enum TouchState{
	T_Touched,
	//T_Moving,
	T_Realesed
};

class Touch{
public:
	Touch();
	bool ProcessTouch();
	word GetX();
	word GetY();
	TouchState GetState();
	bool DataAvailable();
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

};

#endif

/*
void UTouch::touch_WriteData(byte data)
{
	byte temp;

	temp=data;
	cbi(P_CLK, B_CLK);

	for(byte count=0; count<8; count++)
	{
		if(temp & 0x80)
			digitalWrite(T_DIN, HIGH);
		else
			digitalWrite(T_DIN, LOW);
		temp = temp << 1;
		digitalWrite(T_CLK, LOW);
		digitalWrite(T_CLK, HIGH);
	}
}

word UTouch::touch_ReadData()
{
	word data = 0;

	for(byte count=0; count<12; count++)
	{
		data <<= 1;
		digitalWrite(T_CLK, HIGH);
		digitalWrite(T_CLK, LOW);
		if (digitalRead(T_DOUT))
			data++;
	}
	return(data);
}
*/
