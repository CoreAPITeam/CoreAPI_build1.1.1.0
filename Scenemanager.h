/*************************************************************************
/* This headerfile is a part of the Console Core(copyright) Engine
/* It was written by 7xCore.
/* Please do not delete this copyright info.
/* This file and the whole Console Core Engie is free to use and to edit.
/* Feel free to send me any add-ons or suggestions
/* Thanks */



#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <stdio.h>
#include <tchar.h>
#include <cstdlib>
#include <dos.h>
//




#pragma once

#define COLOR_BLACK		0x0
#define COLOR_DARKBLUE	0x1
#define COLOR_DARKGREEN 0x2
#define COLOR_DARKTURK	0x3
#define COLOR_DARKRED	0x4
#define COLOR_LILA		0x5
#define COLOR_BROWN		0x6
#define COLOR_GREY		0x7
#define COLOR_DARKGREY	0x8
#define COLOR_BLUE		0x9
#define COLOR_GREEN		0xA
#define COLOR_TURK		0xB
#define COLOR_RED		0xC
#define COLOR_PINK		0xD
#define COLOR_YELLOW	0xE
#define COLOR_WHITE		0xF

enum TEXT_ALIGN {ALIGN_LEFT,ALIGN_CENTER,ALIGN_RIGHT,TITLE};

struct MenuItem
{
	const char *Caption;
	TEXT_ALIGN text_align;
	byte color;
};


class SceneManager{

private:
	HANDLE hConsole;
	byte FontColor;
	byte BGColor;
	HANDLE hStdInput,hStdOutput,hEvent;                         //WAIT_ABANDONED   = 128
	INPUT_RECORD ir[128];                                       //WAIT_OBJECT_0    = 0
	DWORD nRead;                                                //WAIT_TIMEOUT     = 258
	COORD xy;
	UINT i;

public:

	SceneManager(void);
	~SceneManager(void);
	TEXT_ALIGN text_align;
	SMALL_RECT GetRect();
	COORD CursorPos;
	void SetFontColor(byte Color);
	void SetBGColor(byte Color);
	void SaveCursorPos(void);
	void GotoCursorPos(COORD coord);
	void Fill(byte Color,bool OnlyVisible);
	void Write(char *Text);
	void WriteLn(char *Text);
	void DrawWin(int wx, int wy, int ww, int wh,byte wBorderColor,int wnItems,MenuItem* Items);
	void DrawCenterWin(int wy, int ww, int wh,byte wBorderColor,int wnItems,MenuItem *Items);
	void SceneManager::DrawLine(char CHAR,byte color,int len);
	void DrawCenterBox(int y, int w, int h,byte BorderColor,int nItems,MenuItem *Items);
	void DrawBox(int x, int y, int w, int h,byte BorderColor,int nItems,MenuItem* Items);

	void DrawCustomWindow(const char* Char, int cx, int cy, int cw, int ch,byte cBorderColor,int cnItems,MenuItem* Items);
	void DrawCustomCenterWindow(const char* Char,int cy, int cw, int ch,byte cBorderColor,int cnItems,MenuItem *Items);

	void Create_MouseButtonArea(int y_begin , int y_end, int x_begin, int x_end ,byte BGColor);

	void Draw_unexpected_error_msg();
	void Draw_costum_error_msg(const char* errortext);
	void Draw_costum_warning_msg(const char* warningtext);
	void Draw_costum_info_msg(const char* infotext);
	void free_SceneManager(SceneManager* MySceneManager);
};

