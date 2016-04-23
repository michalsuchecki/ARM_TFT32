#include "ui.h"

UI::UI(TFT* NewDisplay)
{
	Display = NewDisplay;
	elementCount = 0;
}

void UI::Update()
{
	// INFO: Wystarczy redraw ?
	for(int i = 0; i < MAXELEMENT; i ++)
	{
	}
}

void UI::Draw()
{
	for(int i = 0; i < elementCount; i ++)
	{
		if(Elements[i]->bRedraw)
		{
			Elements[i]->Redraw(Display);
		}
	}
}

void UI::AddButton(int x, int y, int sizex, int sizey, word Color, char* text, char* newTag)
{

	if(elementCount < MAXELEMENT)
	{
		UIButton* newButton = new UIButton(x, y, sizex, sizey, text, Color, newTag);
		Elements[elementCount] = newButton;
		elementCount++;
	}

}

void UI::AddText(int x, int y, word Color, char* Caption, char* Tag)
{
	if(elementCount < MAXELEMENT)
	{
		UIText* newCaption = new UIText(x, y, Caption, Color, Tag);
		Elements[elementCount] = newCaption;
		elementCount++;
	}
}

void UI::RemoveElement(char* Tag)
{
	int i, idx = -1;
	for(i = 0; i < MAXELEMENT; i++)
	{
		if(Elements[i] != NULL && strcmp(Elements[i]->Tag, Tag) == 0)
		{
			idx = i;
			elementCount--;
			UIElement* element = Elements[i];
			Elements[i] = NULL;
			free(element);
			break;
		}
	}

	if(idx+1 == MAXELEMENT) return;
	for(i = idx+1; i < MAXELEMENT; i++)
	{
		Elements[i-1] = Elements[i];
		Elements[i] = NULL;
	}
}

int UI::ElementsCount()
{
	return elementCount;
}
// DEBUG

void UI::Debug(int x, int y, int value)
{
	char msg[32];
	itoa(value,msg,10);
	Display->SetColor(VGA_YELLOW);
	Display->PrintText(msg,x,y);
}

//-----------------------------------------------------------

UIElement::~UIElement()
{
	// Virtualny destruktor
}

// Text

void UIElement::Redraw(TFT* Display)
{
}

void UIText::Redraw(TFT* Display)
{
	Display->SetColor(Color);
	Display->PrintText(caption,X,Y);
	bRedraw=false;
}

UIText::UIText(int newX, int newY, char* newCaption, word newColor, char* newTag)
{
	Tag = newTag;
	Color = newColor;
	X = newX;
	Y = newY;
	caption = newCaption;
	bRedraw = true;
}

UIText::~UIText()
{
	free(caption);
	free(Tag);
}

// Button

UIButton::UIButton(int newX, int newY, int newSizeX, int newSizeY, char* newCaption, word newColor, char* newTag)
{
	X = newX;
	Y = newY;
	SizeX = newSizeX;
	SizeY = newSizeY;
	Caption = newCaption;
	Color = newColor;
	Tag = newTag;

	int str_x = strlen(newCaption) * 8;
	int str_y = 8;

	CapX = ((SizeX - str_x) / 2) + X;
	CapY = ((SizeY - str_y) / 2) + Y;

	BorderColor = VGA_WHITE;
}

UIButton::~UIButton()
{
	free(Caption);
	free(Tag);
}

void UIButton::Redraw(TFT* Display)
{
	Display->SetColor(Color);
	Display->FillRect(X,Y,SizeX-1,SizeY-1);
	Display->SetColor(BorderColor);
	Display->DrawRect(X,Y,SizeX,SizeY);
	Display->SetColor(VGA_WHITE);
	Display->PrintText(Caption,CapX, CapY);
	bRedraw = false;
}
