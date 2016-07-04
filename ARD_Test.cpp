#include "ARD_Test.h"

//UI Interface = UI();
TFT Display = TFT();
Touch touch = Touch();
UI Interface = UI(&Display, &touch);
MAX31855 thermo = MAX31855();

bool test = false;
unsigned long last_ms_time;

//PROGMEM
const char* labels[] =
{
	"OK",
	"CANCEL",
	"Press Me"
};

void OnTouch(int x, int y, TouchState State, char* Tag)
{

}

// DEBUG
void static Debug(char* info, word value, int x, int y)
{
	int str_len = strlen(info);
	char msg[64];
	itoa(value,msg,10);
	Display.SetColor(VGA_YELLOW);
	Display.PrintText(info,x,y,false);
	Display.PrintText("      ",x + str_len * 8,y, false);
	Display.PrintText(msg,x + str_len * 8,y, false);
}

void static Debug(char* info, char* value, int x, int y)
{
	int str_len = strlen(info);
	Display.SetColor(VGA_YELLOW);
	Display.PrintText(info,x,y,false);
	Display.PrintText("        ",x + str_len * 10,y, false);
	Display.PrintText(value,x + str_len * 10,y, false);
}

/*
void OnTouch(int x, int y, TouchState State)
{
    switch(State)
    {
    case T_Untouched:
    	Debug("Touch:", "Untouched", 10, 40);
    	break;
    case T_Touched:
    	Debug("Touch:", "Touched  ", 10, 40);
    	break;
    case T_Released:
    	Debug("Touch:", "Released", 10, 40);
    	break;
    }
}
*/

void _convert_float(char *buf, double num, int width, byte prec)
{
	char format[10];

	sprintf(format, "%%%i.%if", width, prec);
	sprintf(buf, format, num);
}

char* dtostrf(double value, uint8_t precision)
{
	char* buffer;
	char int_val[10];
	char dec_val[10];
	uint8_t int_len, dec_len;
	uint8_t buffsize = 0;
	double prec = 1;
	int decimal, integer;

	if(precision > 0)
	{
		for(int i = 0; i < precision; i++)
			prec *= 10;
	}
	else
	{
		prec = 0;
	}


	integer = value;
	value -= (int)value;
	if(value < 0) value *= -1;
	decimal = value * prec;

	itoa(integer, int_val, 10);
	itoa(decimal, dec_val, 10);

	int_len = strlen(int_val);
	dec_len = strlen(dec_val);
	buffsize = int_len;
	if(precision > 0)
		buffsize += precision + 2; // . + precision + \0

	buffer = (char*)malloc(buffsize);

	for(uint8_t i = 0; i < int_len; i++)
	{
		buffer[i] = int_val[i];
	}

	buffer[int_len] = '.';

	for(uint8_t i = 0; i < precision; i++)
	{
		if(i < dec_len)
			buffer[i + int_len + 1] = dec_val[i];
		else
			buffer[i + int_len + 1] = '0';
	}


	buffer[buffsize-1] = '\0';

	//Debug("test:", buffer, 10,60);
	return buffer;
}

void setup()
{
	Serial.begin(9600);
	Display.Init();
	Display.SetFont(SmallFont);
	Display.ClearScreen();

	Interface.OnTouch = OnTouch;


	Interface.AddBackground(0,0,319,50, VGA_GRAY);
	Interface.AddText(10,60, VGA_GREEN, VGA_RED, 1, 3);
	Interface.AddText(100,60, VGA_GREEN, 1, 3);
	Interface.AddButton(200,90,100,25, VGA_NAVY,2,1);
	Interface.AddButton(10,90,100,25, VGA_NAVY,2,2);

	last_ms_time = millis();
}



void loop()
{
	unsigned long curent_time = millis();
	uint16_t delta_time = curent_time - last_ms_time;
	last_ms_time = curent_time;

	//----------------------------------------

	char* result;

	Debug("DeltaTime [ms]: ", delta_time, 10, 10);


	word x = touch.GetX();
	word y = touch.GetY();

	Debug("X: ", x, 10, 30);
	Debug("Y: ", y, 10, 40);
	/*
	Debug("RawX: ", touch.GetRawX(), 100, 30);
	Debug("RawY: ", touch.GetRawY(), 100, 40);
*/
	//result = dtostrf(thermo.ReadCelsiusTemp(), 1);
	//Debug("Temp(C): ", result, 10, 20);
	//result = dtostrf(thermo.ReadInternalTemp(), 1);
	//Debug("Temp(int): ", result, 10, 30);

	/*
    if (touch.ProcessTouch(delta_time))
    {
    	Debug("X:",touch.GetX(),200,10);
    	Debug("Y:",touch.GetY(),270,10);
    }
    */

	//Interface.Draw();

    Interface.Update(delta_time);
    //delay(100);
}
