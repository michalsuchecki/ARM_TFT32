#include "ui.h"

UI::UI(TFT* NewDisplay, Touch* NewTouch)
{
	OnTouch = NULL;
	Display = NewDisplay;
	Sensor = NewTouch;
	elementCount = 0;
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

void UI::Update(uint16_t deltaTime)
{
	if(Sensor->ProcessTouch(deltaTime))
	{
		word x = Sensor->GetX();
		word y = Sensor->GetY();

		for(uint8_t i = 0; i < elementCount; i++)
		{
			if(Elements[i] != NULL)  // Potrzebne ?
			{
				if(Elements[i]->IsOnElement(x,y))
				{
					Elements[i]->bTouched = true;
				}
				else
				{
					Elements[i]->bTouched = false;
				}
				Elements[i]->bRedraw = true;
			}
		}

#ifdef DEBUG
		//Serial.print(x);
		//Serial.print(" ");
		//Serial.println(y);
#endif

	}

	Draw();
}

//-------------------------------------------------------------------------------------------
void UI::AddButton(int x, int y, int sizex, int sizey, word Color, uint8_t capId, uint8_t TagId)
{
	if(elementCount < MAXELEMENT)
	{
		UIButton* newButton = new UIButton(x,y, sizex, sizey, capId, Color, TagId);
		Elements[elementCount++] = newButton;
	}
}

void UI::AddText(int x, int y, word Color, uint8_t CapId, uint8_t TagId)
{
	if(elementCount < MAXELEMENT)
	{
		UIText* newCaption = new UIText(x, y, CapId, Color, TagId);
		Elements[elementCount++] = newCaption;
	}
}

void UI::RemoveElement(uint8_t Tag)
{
	int i, idx = -1;
	for(i = 0; i < MAXELEMENT; i++)
	{
		if(Elements[i] != NULL && Elements[i]->TagId == Tag)
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
	//Display->PrintText(msg,x,y);
}

//-----------------------------------------------------------

UIElement::~UIElement()
{
	// Virtualny destruktor
}

void UIElement::Redraw(TFT* Display)
{
}

bool UIElement::IsOnElement(int x, int y)
{
	return false;
}

// Text

void UIText::Redraw(TFT* Display)
{
	Display->SetColor(Color);
	Display->PrintText(labels[CaptionId],X,Y);
	bRedraw=false;
}

UIText::UIText(int newX, int newY, uint8_t newCapId, word newColor, uint8_t newTag)
{
	Color = newColor;
	X = newX;
	Y = newY;

	TagId = newTag;
	CaptionId = newCapId;

	bRedraw = true;
}

UIText::~UIText()
{
}

bool UIText::IsOnElement(int x, int y)
{
	return false;
}

// Button


UIButton::UIButton(int newX, int newY, int newSizeX, int newSizeY, uint8_t newCapId, word newColor, uint8_t newTag)
{
	X = newX;
	Y = newY;
	SizeX = newSizeX;
	SizeY = newSizeY;
	//Caption = newCaption;
	Color = newColor;
	//Tag = newTag;

	TagId = newTag;
	CaptionId = newCapId;
	int str_x = strlen(labels[CaptionId]) * 8;
	int str_y = 8;

	CapX = ((SizeX - str_x) / 2) + X;
	CapY = ((SizeY - str_y) / 2) + Y;

	color c = TFT::WORDToRGB(Color);
	c.r *= BORDER_COLOR_FACTOR;
	c.g *= BORDER_COLOR_FACTOR;
	c.b *= BORDER_COLOR_FACTOR;

	BorderColor = TFT::RGBtoWORD(c);

	bRedraw = true;
	bTouched = false;
}

UIButton::~UIButton()
{
}

void UIButton::Redraw(TFT* Display)
{
	// Tlo
	Display->SetColor(bTouched ? BorderColor : Color);
	Display->FillRect(X,Y,SizeX-1,SizeY-1);
	// Ramka
	Display->SetColor(bTouched ? VGA_WHITE : BorderColor);
	Display->DrawRect(X,Y,SizeX,SizeY);
	// Tekst
	Display->SetColor(VGA_WHITE);
	Display->PrintText(labels[CaptionId],CapX, CapY);
	bRedraw = false;
}


bool UIButton::IsOnElement(int x, int y)
{

#ifdef DEBUG
		Serial.print("Touch at: ");
		Serial.print(x);
		Serial.print(" ");
		Serial.print(y);

		Serial.print(" Element: ");
		Serial.print(X);
		Serial.print(" ");
		Serial.println(Y);

#endif
	if((x >= X && x <= (X + SizeX))
	&& (y >= Y && y <= (Y + SizeY)))
	{
		Serial.println(" OnElement!");
		return true;
	}
	else
	{
		Serial.println("");
		return false;
	}
}
