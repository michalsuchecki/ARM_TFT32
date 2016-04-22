#include "ARD_Test.h"

TFT display = TFT();

void setup()
{
	display.Init();
	display.SetFont(SmallFont);
	display.ClearScreen();
	display.SetColor(200,0,0);
	display.FillRect(0,0,319,239);
	display.SetColor(255,255,255);
	display.PrintChar('B',10,10);
	display.PrintText("Tost z maslem",10,20);
}

void loop()
{
	/*
	delay(200);
	display.SetColor(255,0,0);
	display.FillRect(0,0,319,239);
	delay(200);
	display.SetColor(0,0,255);
	display.FillRect(0,0,319,239);
	delay(200);
	display.SetColor(0,255,0);
	display.FillRect(0,0,319,239);
	*/
}
