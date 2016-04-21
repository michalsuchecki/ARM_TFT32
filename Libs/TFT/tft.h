#ifndef LIBS_TFT_TFT_H_
#define LIBS_TFT_TFT_H_

#include "Arduino.h"

// Rozdzielczosc
#define RESX 320
#define RESY 240

#define RS 38
#define WR 39
#define CS 40
#define RST 41

// -----------------------------

#define LEFT 0
#define RIGHT 9999
#define CENTER 9998

#define RX (RESX-1)
#define RY (RESY-1)
#define SCREEN_SIZE (RESX*RESY)

#define cbi(reg, bitmask) *reg &= ~bitmask
#define sbi(reg, bitmask) *reg |= bitmask

#define pulse_high(reg, bitmask) sbi(reg, bitmask); cbi(reg, bitmask);
#define pulse_low(reg, bitmask) cbi(reg, bitmask); sbi(reg, bitmask);

#define swap(type, i, j) {type t = i; i = j; j = t;}

#define regtype volatile uint32_t
#define regsize uint32_t

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

// Class

class TFT
{
public:
	TFT(void);
	void Init();
public:
	void DrawPixel(int x, int y);
	void SetPixel(word color);

	void DrawRect(int x, int y, int xl, int yl);
	void FillRect(int x, int y, int xl, int yl);

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
private:
	void SetDirectionRegisters();
	void FastFill16(int ch, int cl, long pix);

	void LCD_Write_COM(char VL);
	void LCD_Write_BUS(char VH,char VL);
	void LCD_Write_DATA(char VL);
	void LCD_Write_DATA(char VH,char VL);
	void LCD_Write_COM_DATA(char com,char DH, char DL);
	void LCD_Write_COM_DATA(char com,int dat);
private:
	regtype	*P_RS, *P_WR, *P_CS, *P_RST;
	regsize	B_RS, B_WR, B_CS, B_RST;
	byte fch, fcl, bch, bcl;
};

#endif
