#include "ARD_Test.h"

//UI Interface = UI();

TFT Display = TFT();
UI Interface = UI(&Display);


void setup()
{
	Display.Init();
	Display.SetFont(SmallFont);
	Display.ClearScreen();

	Interface.AddText(10,20,VGA_LIME,"test", "TEST");
	Interface.AddText(10,30,VGA_AQUA,"inny tekst", "OTHER");
	Interface.AddText(10,40,VGA_BLUE,"kolejny tekst", "KUPA");
	Interface.AddText(10,50,VGA_RED,"kolejny tekst #2", "KUPA2");

	Interface.AddButton(10,60,100,25, VGA_NAVY, "Press LOL", "BT1");

	/*
	int count = Interface.ElementsCount();
	Interface.Debug(10,100, count);

	Interface.RemoveElement("OTHER");

	count = Interface.ElementsCount();
	Interface.Debug(10,110, count);

	Interface.RemoveElement("KUPA");

	count = Interface.ElementsCount();
	Interface.Debug(10,120, count);
	*/
}

void loop()
{
	Interface.Draw();
}
