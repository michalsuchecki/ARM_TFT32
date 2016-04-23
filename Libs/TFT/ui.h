#ifndef LIBS_TFT_UI_H_
#define LIBS_TFT_UI_H_

#include "tft.h"

#define MAXELEMENT 10

enum UIElementType
{
	UI_Background,
	UI_Button,
	UI_Text,
	UI_Graph
};

class UIElement
{
public:
	char* Tag;	// ID
	int X,Y;
	word Color;

	UIElementType Type;
	// Status
	bool bRedraw : 1;
	bool bTouched: 1;


	void virtual Redraw(TFT* Display);
	virtual ~UIElement();
};

class UIText : public UIElement
{
public:
	char* caption;
	UIText(int newX, int newY, char* newCaption, word newColor, char* newTag);
	~UIText();
	void Redraw(TFT* Display);
};

class UIButton : public UIElement
{
	word BorderColor;
	char* Caption;
	int SizeX, SizeY;
	int CapX, CapY;
public:
	UIButton(int newX, int newY, int newSizeX, int newSizeY, char* newCaption, word newColor, char* newTag);
	~UIButton();
	void Redraw(TFT* Display);
};

class UI
{
public:
	UI(TFT* NewDisplay);
	void Draw();
	void Update();
public:
	void AddButton(int x, int y, int sizex, int sizey, word Color, char* text, char* newTag);
	void AddText(int x, int y, word Color, char* Caption, char* Tag);
	void RemoveElement(char* Tag);
	int  ElementsCount();
public:
	void Debug(int x, int y, int value);
private:
	TFT* Display;
	UIElement* Elements[10];
	uint8_t elementCount;
};

#endif
