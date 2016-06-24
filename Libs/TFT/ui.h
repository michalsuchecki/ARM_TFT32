#ifndef LIBS_TFT_UI_H_
#define LIBS_TFT_UI_H_

#include "tft.h"
#include "touch.h"

#define MAXELEMENT 10

enum UIElementType
{
	UI_None,
	UI_Background,
	UI_Button,
	UI_Text,
	UI_ProgressBar,
	UI_Graph
};

extern const char* labels[];

struct SElement
{
	uint8_t TagId;
	uint8_t CaptionId;

	UIElementType Type;

	word ColorPrimary;
	word ColorSecondary;

	uint16_t X,Y;
	uint16_t SizeX,SizeY;

	bool bRedraw : 1;
	bool bTouched: 1;
	bool bTransparent: 1;
};

class UI
{
public:
	UI(TFT* NewDisplay, Touch* NewTouch);
	void Draw();
public:
	void AddBackground(int x, int y, int sizex, int sizey, word Color);
	void AddButton(int x, int y, int sizex, int sizey, word Color, uint8_t capId, uint8_t TagId);
	void AddText(int x, int y, word Color, uint8_t CapId, uint8_t TagId);
	void RemoveElement(uint8_t Tag);
	int  ElementsCount();
	void Update(uint16_t deltaTime);
	void (*OnTouch)(int x, int y, TouchState State, char* Tag);
public:
	void Debug(int x, int y, int value);
private:
	TFT* Display;
	Touch* Sensor;
	SElement Elements[MAXELEMENT];
	uint8_t elementCount;
};

#endif
