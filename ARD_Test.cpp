#include "ARD_Test.h"

TFT display = TFT();

void setup()
{
	display.Init();
	display.ClearScreen();
}

void loop()
{
	delay(200);
	display.SetColor(255,0,0);
	display.FillRect(0,0,319,239);
	delay(200);
	display.SetColor(0,0,255);
	display.FillRect(0,0,319,239);
	delay(200);
	display.SetColor(0,255,0);
	display.FillRect(0,0,319,239);
}
