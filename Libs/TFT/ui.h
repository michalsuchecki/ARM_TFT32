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
	char* Tag;	// ID
	int X,Y;
	word Color;

	//UIElementType Type;
	// Status
	bool bRedraw : 1;
	bool bTouched: 1;	// bActive ?


	void virtual Redraw(TFT* Display);
	virtual ~UIElement();

	bool virtual IsOnElement(int x, int y);
};

class UIText : public UIElement
{
public:
	char* caption;
	UIText(int newX, int newY, char* newCaption, word newColor, char* newTag);
	~UIText();
	void Redraw(TFT* Display);
	bool IsOnElement(int x, int y);
};

class UIButton : public UIElement
{
private:
	word BorderColor;
	char* Caption;
	uint16_t SizeX, SizeY;
	uint16_t CapX, CapY;

public:
	UIButton(int newX, int newY, int newSizeX, int newSizeY, char* newCaption, word newColor, char* newTag);
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
	void AddButton(int x, int y, int sizex, int sizey, word Color, char* text, char* newTag);
	void AddText(int x, int y, word Color, char* Caption, char* Tag);
	void RemoveElement(char* Tag);
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
