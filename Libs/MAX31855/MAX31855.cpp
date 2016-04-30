#include "MAX31855.h"

MAX31855::MAX31855()
{
	pinMode(SCK, OUTPUT);
	pinMode(CS, OUTPUT);
	pinMode(SO, INPUT);

	digitalWrite(CS, HIGH);
}

double MAX31855::ReadInternalTemp()
{
	int32_t _data = ReadData();

	// remove errors D3:D0
	_data >>= 4;

	// Read 12 bit data
	double internal = _data & 0x7FF;
	if (_data & 0x800)
	{
		// Convert to negative value by extending sign and casting to signed type.
		int16_t tmp = 0xF800 | (_data & 0x7FF);
	    internal = tmp;
	}
	internal *= 0.0625;

	return internal;
}

double MAX31855::ReadCelsiusTemp()
{
	int32_t _data = ReadData();

	// Error
	if(_data & 0x07)
		return 0;

	// Negative
	if(_data & 0x80000000)
	{
		_data = 0xFFFFC000 | ((_data >> 18) & 0x00003FFFF);
	}
	else
	{
		_data = _data >> 18;
	}

	double _result = _data;

	_result *= 0.25;

	return _result;
}

uint32_t MAX31855::ReadData()
{
	uint32_t data = 0;

	digitalWrite(SCK, LOW);
	delay(1);
	digitalWrite(CS, LOW);
	delay(1);

	for(int i = 31; i>=0; i--)
	{
		digitalWrite(SCK, LOW);
		delay(1);
		data <<= 1;
		if (digitalRead(SO))
		{
			data |= 1;
		}
		digitalWrite(SCK, HIGH);
		delay(1);
	}

	digitalWrite(CS, HIGH);
	return data;
}
