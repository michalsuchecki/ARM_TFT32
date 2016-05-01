#ifndef LIBS_TFT_TFT_H_
#define LIBS_TFT_TFT_H_

#include "common.h"



// STRUCT

struct sfont
{
	const byte* font;
	uint8_t x_size;
	uint8_t y_size;
	uint8_t offset;
	uint8_t numchars;
};

// CLASS

class TFT
{
public:
	TFT(void);
	void Init();
public:
	void DrawPixel(int x, int y);
	void SetPixel(word color);
	void SetPixel(uint8_t ph, uint8_t pl);

	void DrawRect(int x, int y, int xl, int yl);
	void FillRect(int x, int y, int xl, int yl);

	void DrawLine(int x, int y, int x2, int y2);
	void DrawHorizontalLine(int x, int y, int l);
	void DrawVerticalLine(int x, int y, int l);

	void SetColor(byte r, byte g, byte b);
	void SetColor(word color);

	void SetBackColor(byte r, byte g, byte b);
	void SetBackColor(uint32_t color);

	void SetXY(word x1, word y1, word x2, word y2);
	void ClearXY();
	void ClearScreen();

	int	GetDisplayXSize();
	int	GetDisplayYSize();

	static word RGBtoWORD(uint8_t r, uint8_t g, uint8_t b);
	static word RGBtoWORD(color c);
	static color WORDToRGB(word Color);

	// Font
	void PrintText(char* string, int x=0, int y=0, bool transparent = true);
	void PrintChar(char c, int x=0, int y=0, bool transparent = true);
	void SetFont(const byte* newFont);
	uint8_t GetFontSizeX();
	uint8_t GetFontSizeY();
private:
	void SetDirectionRegisters();
	void FastFill16(int ch, int cl, long pix);
	// Commands
	void LCD_Write_COM(char VL);
	void LCD_Write_BUS(char VH,char VL);
	void LCD_Write_DATA(char VL);
	void LCD_Write_DATA(char VH,char VL);
	void LCD_Write_COM_DATA(char com,char DH, char DL);
	void LCD_Write_COM_DATA(char com,int dat);
private:
	sfont Font;
	regtype	*P_RS, *P_WR, *P_CS, *P_RST;
	regsize	B_RS, B_WR, B_CS, B_RST;
	byte fch, fcl, bch, bcl;
};

#endif
