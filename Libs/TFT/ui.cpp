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
	for(uint8_t i = 0; i < elementCount; i++)
	{
		SElement current = Elements[i];

		if(!current.bRedraw) continue;

		switch(current.Type)
		{
		case UI_Background:
			Display->SetColor(current.ColorPrimary);
			Display->FillRect(current.X,current.Y,current.SizeX,current.SizeY);
			Elements[i].bRedraw = false;
			break;
		case UI_Button:
			// Tlo
			Display->SetColor(current.bTouched ? current.ColorSecondary : current.ColorPrimary);
			Display->FillRect(current.X,current.Y,current.SizeX-1,current.SizeY-1);
			// Ramka
			Display->SetColor(current.bTouched ? VGA_WHITE : current.ColorSecondary);
			Display->DrawRect(current.X,current.Y,current.SizeX,current.SizeY);
			// Tekst
			Display->SetColor(VGA_WHITE);
			Display->PrintText(labels[current.CaptionId], ((current.SizeX - strlen(labels[current.CaptionId]) * 8) / 2) + current.X, ((current.SizeY - 8) / 2) + current.Y);

			Elements[i].bRedraw = false;
		break;
		case UI_Text:
			// Tlo
			if(!current.bTransparent)
			{
			Display->SetColor(current.ColorSecondary);
			Display->FillRect(current.X, current.Y, current.SizeX, current.SizeY);
			}
			// Tekst
			Display->SetColor(current.ColorPrimary);
			Display->PrintText(labels[current.CaptionId],current.X,current.Y,true);

			Elements[i].bRedraw = false;
			break;
		UI_None:
		default:
			break;
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
			if(Elements[i].Type == UI_Button)
			{
				SElement button = Elements[i];

				if((x >= button.X  && x <= button.X + button.SizeX)
				&& (y >= button.Y  && y <= button.Y + button.SizeY)
				)

				{
					Elements[i].bTouched = true;
					Elements[i].bRedraw = true;
				}
				else
				{
					Elements[i].bTouched = false;
					Elements[i].bRedraw = true;
				}
			}
		}

#ifdef DEBUG
		Serial.print(x);
		Serial.print(" ");
		Serial.println(y);
#endif

	}
	else
	{
		if(Sensor->GetState() == T_Released)
		{
			for(uint8_t i = 0; i < elementCount; i++)
			{
				if(Elements[i].Type == UI_Button)
				{
					Elements[i].bTouched = false;
					Elements[i].bRedraw = true;
				}
			}
		}
	}

	Draw();
}

//-------------------------------------------------------------------------------------------

void UI::AddBackground(int x, int y, int sizex, int sizey, word Color)
{
	SElement element;

	element.Type = UI_Background;

	element.ColorPrimary = Color;

	element.X = x;
	element.Y = y;
	element.SizeX = sizex;
	element.SizeY = sizey;

	element.bRedraw = true;
	element.bTouched = false;

	Elements[elementCount++] = element;
}

void UI::AddButton(int x, int y, int sizex, int sizey, word Color, uint8_t capId, uint8_t TagId)
{
	if(elementCount < MAXELEMENT)
	{
		SElement element;

		element.Type = UI_Button;
		element.CaptionId = capId;
		element.TagId = TagId;

		element.ColorPrimary = Color;

		element.X = x;
		element.Y = y;
		element.SizeX = sizex;
		element.SizeY = sizey;

		color c = TFT::WORDToRGB(Color);

		c.r *= BORDER_COLOR_FACTOR;
		c.g *= BORDER_COLOR_FACTOR;
		c.b *= BORDER_COLOR_FACTOR;

		element.ColorSecondary = TFT::RGBtoWORD(c);

		element.bRedraw = true;
		element.bTouched = false;

		Elements[elementCount++] = element;
	}
}

void UI::AddText(int x, int y, word Color, word Background, uint8_t CapId, uint8_t TagId)
{
	if(elementCount < MAXELEMENT)
	{
		SElement element;

		element.Type = UI_Text;
		element.CaptionId = CapId;
		element.TagId = TagId;

		element.ColorPrimary = Color;
		element.ColorSecondary = Background;

		element.X = x;
		element.Y = y;

		element.SizeY = Display->GetFontSizeY();
		element.SizeX = Display->GetFontSizeX() * strlen(labels[CapId]);

		element.bRedraw = true;
		element.bTouched = false;
		element.bTransparent = false;

		Elements[elementCount++] = element;
	}
}

void UI::AddText(int x, int y, word Color, uint8_t CapId, uint8_t TagId)
{
	if(elementCount < MAXELEMENT)
	{
		SElement element;

		element.Type = UI_Text;
		element.CaptionId = CapId;
		element.TagId = TagId;

		element.ColorPrimary = Color;

		element.X = x;
		element.Y = y;

		element.bRedraw = true;
		element.bTouched = false;
		element.bTransparent = true;

		Elements[elementCount++] = element;
	}
}

void UI::RemoveElement(uint8_t Tag)
{
	// TODO: Refactoring !
	/*
	int i, idx = -1;
	for(i = 0; i < MAXELEMENT; i++)
	{
		if(ElementsOld[i] != NULL && ElementsOld[i]->TagId == Tag)
		{
			idx = i;
			elementCount--;
			UIElement* element = ElementsOld[i];
			ElementsOld[i] = NULL;
			free(element);
			break;
		}
	}

	if(idx+1 == MAXELEMENT) return;
	for(i = idx+1; i < MAXELEMENT; i++)
	{
		ElementsOld[i-1] = ElementsOld[i];
		ElementsOld[i] = NULL;
	}
	*/
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
