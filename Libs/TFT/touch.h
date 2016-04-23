#ifndef LIBS_TFT_TOUCH_H_
#define LIBS_TFT_TOUCH_H_

#include "common.h"

#define CAL_X 0x00378F66UL
#define CAL_Y 0x03C34155UL
#define CAL_S 0x000EF13FUL

#define T_CLK 25
#define T_CS 26
#define T_DIN 27
#define T_DOUT 29
#define T_IRQ 30

class Touch{
public:
	Touch();
	bool ProcessTouch();
	word GetX();
	word GetY();
private:
	bool DataAvailable();
	void DataRead();
	void DeviceWrite(byte data);
	word DeviceRead();
private:
	word x,y;
	regtype *P_CLK, *P_CS, *P_DIN, *P_DOUT, *P_IRQ;
	regsize B_CLK, B_CS, B_DIN, B_DOUT, B_IRQ;
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
