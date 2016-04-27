#include "ARD_Test.h"

//UI Interface = UI();
TFT Display = TFT();
UI Interface = UI(&Display);
Touch touch = Touch();

bool test = false;
unsigned long last_ms_time;

void (*OnTouchcallback)(int x, int y, TouchState State, char* Tag);

void OnTouch(int x, int y, TouchState State, char* Tag)
{

}

void Debug(char* info,  word value, int x, int y)
{
	int str_len = strlen(info);
	char msg[64];
	itoa(value,msg,10);
	Display.SetColor(VGA_YELLOW);
	Display.PrintText(info,x,y,false);
	Display.PrintText("      ",x + str_len * 8,y, false);
	Display.PrintText(msg,x + str_len * 8,y, false);
}

void Debug(char* info,  char* value, int x, int y)
{
	int str_len = strlen(info);
	Display.SetColor(VGA_YELLOW);
	Display.PrintText(info,x,y,false);
	Display.PrintText("        ",x + str_len * 10,y, false);
	Display.PrintText(value,x + str_len * 10,y, false);
}


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


void setup()
{
	//Serial.begin(9600);
	//Serial.println("TFT Test Console :)");

	//OnTouchcallback = OnTouch;

	Display.Init();
	Display.SetFont(SmallFont);
	Display.ClearScreen();

	touch.OnTouch = OnTouch;

	//Interface.AddText(10,20,VGA_LIME,"test", "TEST");
	//Interface.AddText(10,30,VGA_AQUA,"inny tekst", "OTHER");
	//Interface.AddText(10,40,VGA_BLUE,"kolejny tekst", "KUPA");
	//Interface.AddText(10,50,VGA_RED,"kolejny tekst #2", "KUPA2");

	//Interface.AddButton(10,60,100,25, VGA_NAVY, "Press LOL", "BT1");

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
	last_ms_time = millis();
}

void loop()
{
	unsigned long curent_time = millis();
	uint16_t delta_time = curent_time - last_ms_time;
	last_ms_time = curent_time;

	Debug("DeltaTime [ms]: ",delta_time, 10,10);

    if (touch.ProcessTouch(delta_time))
    {
    	Debug("X:",touch.GetX(),200,10);
    	Debug("Y:",touch.GetY(),270,10);
    }

	Interface.Draw();
}
