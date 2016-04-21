#include "ARD_Test.h"

TFT display = TFT();

void setup()
{
	display.Init();
	delay(500);
	display.SetBackColor(100,0,00);
	display.ClearScreen();
	display.SetColor(0,255,0);
	display.FillRect(0,20,50,50);
	display.SetColor(255,0,0);
	display.DrawRect(100,100,100,20);
}

void loop()
{

}
