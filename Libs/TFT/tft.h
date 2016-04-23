#ifndef LIBS_TFT_TFT_H_
#define LIBS_TFT_TFT_H_

#include "common.h"

// Colors

#define VGA_BLACK		0x0000
#define VGA_WHITE		0xFFFF
#define VGA_RED			0xF800
#define VGA_GREEN		0x0400
#define VGA_BLUE		0x001F
#define VGA_SILVER		0xC618
#define VGA_GRAY		0x8410
#define VGA_MAROON		0x8000
#define VGA_YELLOW		0xFFE0
#define VGA_OLIVE		0x8400
#define VGA_LIME		0x07E0
#define VGA_AQUA		0x07FF
#define VGA_TEAL		0x0410
#define VGA_NAVY		0x0010
#define VGA_FUCHSIA		0xF81F
#define VGA_PURPLE		0x8010
#define VGA_TRANSPARENT	0xFFFFFFFF

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
