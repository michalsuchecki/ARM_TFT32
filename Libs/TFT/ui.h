#ifndef LIBS_TFT_UI_H_
#define LIBS_TFT_UI_H_

#include "tft.h"
#include "touch.h"

#define MAXELEMENT 10

enum UIElementType
{
	UI_Background,
	UI_Button,
	UI_Text,
	UI_Graph
};

extern const char* labels[];

class UIElement
{
public:
	int X,Y;
	word Color;

	//UIElementType Type;
	// Status
	bool bRedraw : 1;
	bool bTouched: 1;	// bActive ?

	uint8_t TagId;
	uint8_t CaptionId;


	void virtual Redraw(TFT* Display);
	virtual ~UIElement();

	bool virtual IsOnElement(int x, int y);
};

class UIText : public UIElement
{
public:
	UIText(int newX, int newY, uint8_t newCapId, word newColor, uint8_t newTag);
	~UIText();
	void Redraw(TFT* Display);
	bool IsOnElement(int x, int y);
};

class UIButton : public UIElement
{
private:
	word BorderColor;
	uint16_t SizeX, SizeY;
	uint16_t CapX, CapY;

public:
	UIButton(int newX, int newY, int newSizeX, int newSizeY, uint8_t newCapId, word newColor, uint8_t newTag);
	~UIButton();
	void Redraw(TFT* Display);
	bool IsOnElement(int x, int y);
};

class UI
{
public:
	UI(TFT* NewDisplay, Touch* NewTouch);
	void Draw();
public:
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
	UIElement* Elements[10];
	uint8_t elementCount;
};

#endif
