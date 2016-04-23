#include "ARD_Test.h"

//UI Interface = UI();

TFT Display = TFT();
UI Interface = UI(&Display);
Touch touch = Touch();

bool test = false;

void Debug(word value, int x, int y)
{
	char msg[32];
	itoa(value,msg,10);
	Display.SetColor(VGA_YELLOW);
	Display.PrintText(msg,x,y);

}

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
    if (touch.ProcessTouch())
    {
    	if(!test)
    	{
    	Debug(touch.GetX(),10,80);
    	Debug(touch.GetY(),10,90);
    	test=true;
    	}
    }
	Interface.Draw();
}
