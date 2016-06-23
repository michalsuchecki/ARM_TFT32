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
			// TODO
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
			Display->SetColor(current.ColorPrimary);
			Display->PrintText(labels[current.CaptionId],current.X,current.Y);

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
		/*
		word x = Sensor->GetX();
		word y = Sensor->GetY();

		for(uint8_t i = 0; i < elementCount; i++)
		{
			if(ElementsOld[i] != NULL)  // Potrzebne ?
			{
				if(ElementsOld[i]->IsOnElement(x,y))
				{
					ElementsOld[i]->bTouched = true;
				}
				else
				{
					ElementsOld[i]->bTouched = false;
				}
				ElementsOld[i]->bRedraw = true;
			}
		}
		*/

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
		SElement newButton;

		newButton.Type = UI_Button;
		newButton.CaptionId = capId;
		newButton.TagId = TagId;

		newButton.ColorPrimary = Color;

		newButton.X = x;
		newButton.Y = y;
		newButton.SizeX = sizex;
		newButton.SizeY = sizey;

		color c = TFT::WORDToRGB(Color);

		c.r *= BORDER_COLOR_FACTOR;
		c.g *= BORDER_COLOR_FACTOR;
		c.b *= BORDER_COLOR_FACTOR;

		newButton.ColorSecondary = TFT::RGBtoWORD(c);

		newButton.bRedraw = true;
		newButton.bTouched = false;

		Elements[elementCount++] = newButton;
	}
}

void UI::AddText(int x, int y, word Color, uint8_t CapId, uint8_t TagId)
{
	if(elementCount < MAXELEMENT)
	{
		SElement newCaption;

		newCaption.Type = UI_Text;
		newCaption.CaptionId = CapId;
		newCaption.TagId = TagId;

		newCaption.ColorPrimary = Color;
		newCaption.ColorSecondary = VGA_WHITE;

		newCaption.X = x;
		newCaption.Y = y;

		newCaption.bRedraw = true;
		newCaption.bTouched = false;

		Elements[elementCount++] = newCaption;
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

//-----------------------------------------------------------

/*
bool UIButton::IsOnElement(int x, int y)
{
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
*/
