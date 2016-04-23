#include "touch.h"

Touch::Touch()
{
	x = 0;
	y = 0;

	P_CLK	= portOutputRegister(digitalPinToPort(T_CLK));
	B_CLK	= digitalPinToBitMask(T_CLK);
	P_CS	= portOutputRegister(digitalPinToPort(T_CS));
	B_CS	= digitalPinToBitMask(T_CS);
	P_DIN	= portOutputRegister(digitalPinToPort(T_DIN));
	B_DIN	= digitalPinToBitMask(T_DIN);
	P_DOUT	= portInputRegister(digitalPinToPort(T_DOUT));
	B_DOUT	= digitalPinToBitMask(T_DOUT);
	P_IRQ	= portInputRegister(digitalPinToPort(T_IRQ));
	B_IRQ	= digitalPinToBitMask(T_IRQ);

	pinMode(T_CLK,  OUTPUT);
    pinMode(T_CS,   OUTPUT);
    pinMode(T_DIN,  OUTPUT);
    pinMode(T_DOUT, INPUT);
    pinMode(T_IRQ,  OUTPUT);

	sbi(P_CS, B_CS);
	sbi(P_CLK, B_CLK);
	sbi(P_DIN, B_DIN);
	sbi(P_IRQ, B_IRQ);

	/*
	orient					= orientation;
	_default_orientation	= CAL_S>>31;
	touch_x_left			= (CAL_X>>14) & 0x3FFF;
	touch_x_right			= CAL_X & 0x3FFF;
	touch_y_top				= (CAL_Y>>14) & 0x3FFF;
	touch_y_bottom			= CAL_Y & 0x3FFF;
	disp_x_size				= (CAL_S>>12) & 0x0FFF;
	disp_y_size				= CAL_S & 0x0FFF;
	prec					= 10;
	 */
}

word Touch::GetX()
{
	return x;
}

word Touch::GetY()
{
	return y;
}

bool Touch::ProcessTouch()
{
	if(DataAvailable())
	{
		DataRead();
		return true;
	}
	else
		return false;

}

bool Touch::DataAvailable()
{
	pinMode(T_IRQ, INPUT);
	bool available = !(rbi(P_IRQ, B_IRQ));
	pinMode(T_IRQ,  OUTPUT);
	return available;
}

void Touch::DataRead()
{
	cbi(P_CS, B_CS);
	pinMode(T_IRQ,  INPUT);

	if (!rbi(P_IRQ, B_IRQ))
	{
		DeviceWrite(0x90);
		pulse_high(P_CLK, B_CLK);
		x = DeviceRead();
	}

	if (!rbi(P_IRQ, B_IRQ))
	{
		DeviceWrite(0xD0);
		pulse_high(P_CLK, B_CLK);
		y = DeviceRead();
	}

	pinMode(T_IRQ,  OUTPUT);
	sbi(P_CS, B_CS);
}

word Touch::DeviceRead()
{
	word data = 0;

	for(byte count=0; count<12; count++)
	{
		data <<= 1;
		// Pulse ? pulse_high(P_CLK, B_CLK);
		digitalWrite(T_CLK, HIGH);
		digitalWrite(T_CLK, LOW);
		if (digitalRead(T_DOUT))
			data++;
	}

	return data;
}

void Touch::DeviceWrite(byte data)
{
	byte temp = data;

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
