#include "tft.h"

TFT::TFT()
{
	bch = 0;
	bcl = 0;
	fch = 0;
	fcl = 0;

	P_RS = portOutputRegister(digitalPinToPort(RS));
	B_RS = digitalPinToBitMask(RS);
	P_WR = portOutputRegister(digitalPinToPort(WR));
	B_WR = digitalPinToBitMask(WR);
	P_CS = portOutputRegister(digitalPinToPort(CS));
	B_CS = digitalPinToBitMask(CS);
	P_RST = portOutputRegister(digitalPinToPort(RST));
	B_RST = digitalPinToBitMask(RST);
}

void TFT::Init(void)
{
	// EHOUSE SHIELD - Set the TFT_RD pin permanently HIGH
	pinMode(24, OUTPUT);
	digitalWrite(24, HIGH);

	pinMode(RS, OUTPUT);
	pinMode(WR, OUTPUT);
	pinMode(CS, OUTPUT);
	pinMode(RST, OUTPUT);

	SetDirectionRegisters();

	sbi(P_RST, B_RST);
	delay(5);
	cbi(P_RST, B_RST);
	delay(15);
	sbi(P_RST, B_RST);
	delay(15);

	cbi(P_CS, B_CS);

	// LCD_Init_Commands
	LCD_Write_COM_DATA(0x00,0x0001);
	LCD_Write_COM_DATA(0x03,0xA8A4);
	LCD_Write_COM_DATA(0x0C,0x0000);
	LCD_Write_COM_DATA(0x0D,0x080C);
	LCD_Write_COM_DATA(0x0E,0x2B00);
	LCD_Write_COM_DATA(0x1E,0x00B7);
	LCD_Write_COM_DATA(0x01,0x2B3F);
	LCD_Write_COM_DATA(0x02,0x0600);
	LCD_Write_COM_DATA(0x10,0x0000);
	LCD_Write_COM_DATA(0x11,0x6070);
	LCD_Write_COM_DATA(0x05,0x0000);
	LCD_Write_COM_DATA(0x06,0x0000);
	LCD_Write_COM_DATA(0x16,0xEF1C);
	LCD_Write_COM_DATA(0x17,0x0003);
	LCD_Write_COM_DATA(0x07,0x0233);
	LCD_Write_COM_DATA(0x0B,0x0000);
	LCD_Write_COM_DATA(0x0F,0x0000);
	LCD_Write_COM_DATA(0x41,0x0000);
	LCD_Write_COM_DATA(0x42,0x0000);
	LCD_Write_COM_DATA(0x48,0x0000);
	LCD_Write_COM_DATA(0x49,0x013F);
	LCD_Write_COM_DATA(0x4A,0x0000);
	LCD_Write_COM_DATA(0x4B,0x0000);
	LCD_Write_COM_DATA(0x44,0xEF00);
	LCD_Write_COM_DATA(0x45,0x0000);
	LCD_Write_COM_DATA(0x46,0x013F);
	LCD_Write_COM_DATA(0x30,0x0707);
	LCD_Write_COM_DATA(0x31,0x0204);
	LCD_Write_COM_DATA(0x32,0x0204);
	LCD_Write_COM_DATA(0x33,0x0502);
	LCD_Write_COM_DATA(0x34,0x0507);
	LCD_Write_COM_DATA(0x35,0x0204);
	LCD_Write_COM_DATA(0x36,0x0204);
	LCD_Write_COM_DATA(0x37,0x0502);
	LCD_Write_COM_DATA(0x3A,0x0302);
	LCD_Write_COM_DATA(0x3B,0x0302);
	LCD_Write_COM_DATA(0x23,0x0000);
	LCD_Write_COM_DATA(0x24,0x0000);
	LCD_Write_COM_DATA(0x25,0x8000);
	LCD_Write_COM_DATA(0x4f,0x0000);
	LCD_Write_COM_DATA(0x4e,0x0000);
	LCD_Write_COM(0x22);

	sbi (P_CS, B_CS);

	SetColor(255, 255, 255);
	SetBackColor(0, 0, 0);
}

void TFT::DrawPixel(int x, int y)
{
	cbi(P_CS, B_CS);
	SetXY(x, y, x, y);
	SetPixel((fch<<8)|fcl);
	sbi(P_CS, B_CS);
	ClearXY();
}

void TFT::SetPixel(word color)
{
	LCD_Write_DATA((color>>8),(color&0xFF));
}

void TFT::DrawRect(int x, int y, int xl, int yl)
{
	DrawHorizontalLine(x,y,xl);
	DrawHorizontalLine(x,y+yl,xl);
	DrawVerticalLine(x,y+1,yl-2);
	DrawVerticalLine(x+xl,y+1,yl-2);
}

void TFT::FillRect(int x, int y, int xl, int yl)
{
	cbi(P_CS, B_CS);
	SetXY(x, y, x+xl, y+yl);
	sbi(P_RS, B_RS);
	FastFill16(fch,fcl,((xl+1)*(yl+1)));
	sbi(P_CS, B_CS);
	ClearXY();
}

void TFT::DrawLine(int x, int y, int x2, int y2)
{
	int dx, dy, cx, cy, sx, sy,	ox, oy,steps;

	ox = 0;
	oy = 0;

	dx = (x > x2) ? x - x2 : x2 - x;
	dy = (y > y2) ? y - y2 : y2 - y;

	steps = (dx >= dy) ? dx : dy; // >=

	sx = (dx!=0) ? ((x2-x) * 100 / steps) : 0;
	sy = (dy!=0) ? ((y2-y) * 100 / steps) : 0;

	DrawPixel(x, y);

	while(steps--)
	{
		ox += sx;
		oy += sy;

		cx = x + ox / 100;
		cy = y + oy / 100;

		DrawPixel(cx, cy);
	}
}

void TFT::DrawHorizontalLine(int x, int y, int l)
{
	if (l<0)
	{
		l = -l;
		x -= l;
	}
	cbi(P_CS, B_CS);
	SetXY(x, y, x+l, y);

	sbi(P_RS, B_RS);
	FastFill16(fch,fcl,l);

	sbi(P_CS, B_CS);
	ClearXY();
}

void TFT::DrawVerticalLine(int x, int y, int l)
{
	if (l<0)
	{
		l = -l;
		y -= l;
	}
	cbi(P_CS, B_CS);
	SetXY(x, y, x, y+l);

	sbi(P_RS, B_RS);
	FastFill16(fch,fcl,l);

	sbi(P_CS, B_CS);
	ClearXY();
}


void TFT::SetColor(byte r, byte g, byte b)
{
	fch=((r&248)|g>>5);
	fcl=((g&28)<<3|b>>3);
}

void TFT::SetColor(word color)
{
	fch=byte(color>>8);
	fcl=byte(color & 0xFF);
}

void TFT::SetBackColor(byte r, byte g, byte b)
{
	bch=((r&248)|g>>5);
	bcl=((g&28)<<3|b>>3);
}

void TFT::SetBackColor(uint32_t color)
{
	bch=byte(color>>8);
	bcl=byte(color & 0xFF);
}

void TFT::SetXY(word x1, word y1, word x2, word y2)
{
	swap(word, x1, y1);
	swap(word, x2, y2);
	y1=RX-y1;
	y2=RX-y2;
	swap(word, y1, y2);

	LCD_Write_COM_DATA(0x44,x2,x1);
	LCD_Write_COM_DATA(0x45,y1);
	LCD_Write_COM_DATA(0x46,y2);
	LCD_Write_COM_DATA(0x4e,x1);
	LCD_Write_COM_DATA(0x4f,y1);
	LCD_Write_COM(0x22);
}

void TFT::ClearXY()
{
	SetXY(0,0,RX,RY);
}

void TFT::ClearScreen()
{
 	cbi(P_CS, B_CS);
	ClearXY();
	sbi(P_RS, B_RS);
	FastFill16(0,0,SCREEN_SIZE);
	sbi(P_CS, B_CS);
}

int TFT::GetDisplayXSize()
{
	return RESX;
}

int TFT::GetDisplayYSize()
{
	return RESY;
}

// Private Methods

void TFT::SetDirectionRegisters()
{
	REG_PIOC_OER=0x000FF3FC;
	REG_PIOC_OWER=0x000FF3FC;
	/*
	REG_PIOA_OER=0x0000c000; //PA14,PA15 enable
	REG_PIOB_OER=0x04000000; //PB26 enable
	REG_PIOD_OER=0x0000064f; //PD0-3,PD6,PD9-10 enable
	REG_PIOA_OER=0x00000080; //PA7 enable
	REG_PIOC_OER=0x0000003e; //PC1 - PC5 enable
	*/
}
void TFT::FastFill16(int ch, int cl, long pix)
{
	long blocks;

	/*
	REG_PIOA_CODR=0x0000C080;
	REG_PIOC_CODR=0x0000003E;
	REG_PIOD_CODR=0x0000064F;
	REG_PIOA_SODR=((ch & 0x06)<<13) | ((cl & 0x40)<<1);
	(ch & 0x01) ? REG_PIOB_SODR = 0x4000000 : REG_PIOB_CODR = 0x4000000;
	REG_PIOC_SODR=((cl & 0x01)<<5) | ((cl & 0x02)<<3) | ((cl & 0x04)<<1) | ((cl & 0x08)>>1) | ((cl & 0x10)>>3);
	REG_PIOD_SODR=((ch & 0x78)>>3) | ((ch & 0x80)>>1) | ((cl & 0x20)<<5) | ((cl & 0x80)<<2);
*/
	PIOC->PIO_ODSR = ((PIOC->PIO_ODSR&(~0x000FF3FC)) | ((((uint32_t)cl)<<2) | (((uint32_t)ch)<<12)));

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);
	}
	if ((pix % 16) != 0)
	{
		for (int i=0; i<(pix % 16)+1; i++)
		{
			pulse_low(P_WR, B_WR);
		}
	}
}

void TFT::LCD_Write_COM(char VL)
{
	cbi(P_RS, B_RS);
	LCD_Write_BUS(0x00,VL);
}

void TFT::LCD_Write_DATA(char VH,char VL)
{
	sbi(P_RS, B_RS);
	LCD_Write_BUS(VH,VL);
}

void TFT::LCD_Write_DATA(char VL)
{
	sbi(P_RS, B_RS);
	LCD_Write_BUS(0x00,VL);
}

void TFT::LCD_Write_COM_DATA(char com,char DH, char DL)
{
    LCD_Write_COM(com);
    LCD_Write_DATA(DH, DL);
}

void TFT::LCD_Write_COM_DATA(char com,int dat)
{
     LCD_Write_COM(com);
     LCD_Write_DATA(dat>>8,dat);
}

void TFT::LCD_Write_BUS(char VH,char VL)
{
	PIOC->PIO_ODSR = ((PIOC->PIO_ODSR&(~0x000FF3FC)) | ((((uint32_t)VL)<<2) | (((uint32_t)VH)<<12)));
	pulse_low(P_WR, B_WR);
	/*
	REG_PIOA_CODR=0x0000C080;
	REG_PIOC_CODR=0x0000003E;
	REG_PIOD_CODR=0x0000064F;
	REG_PIOA_SODR=((VH & 0x06)<<13) | ((VL & 0x40)<<1);
	(VH & 0x01) ? REG_PIOB_SODR = 0x4000000 : REG_PIOB_CODR = 0x4000000;
	REG_PIOC_SODR=((VL & 0x01)<<5) | ((VL & 0x02)<<3) | ((VL & 0x04)<<1) | ((VL & 0x08)>>1) | ((VL & 0x10)>>3);
	REG_PIOD_SODR=((VH & 0x78)>>3) | ((VH & 0x80)>>1) | ((VL & 0x20)<<5) | ((VL & 0x80)<<2);
	pulse_low(P_WR, B_WR);
	*/
}
