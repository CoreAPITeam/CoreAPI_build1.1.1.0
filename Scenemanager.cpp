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

#include "SceneManager.h"



SceneManager::SceneManager(void)
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	text_align = ALIGN_LEFT;
}

SceneManager::~SceneManager(void)
{
}

SMALL_RECT SceneManager::GetRect()
{
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole,&info);
	return info.srWindow;
}

void SceneManager::free_SceneManager(SceneManager* MySceneManager){ delete MySceneManager;}

void SceneManager::SaveCursorPos(void)
{
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole,&info);
	CursorPos = info.dwCursorPosition;
}

void SceneManager::GotoCursorPos(COORD coord)
{
	SetConsoleCursorPosition(hConsole,coord);
}

void SceneManager::SetFontColor(byte Color)
{
	FontColor = Color;
}

void SceneManager::SetBGColor(byte Color)
{
	BGColor = Color*0x10;
}

void SceneManager::Write(char *Text)
{
	SetConsoleTextAttribute(hConsole,FontColor | BGColor);
	printf("%s",Text);
}

void SceneManager::WriteLn(char *Text)
{
	SetConsoleTextAttribute(hConsole,FontColor | BGColor);

	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hConsole,&info);

	if (text_align == ALIGN_CENTER)
	{
		info.dwCursorPosition.X = (info.srWindow.Left+info.srWindow.Right/2)-(strlen(Text)/2);
		SetConsoleCursorPosition(hConsole,info.dwCursorPosition);
		printf("%s\n",Text);
	}
	else if (text_align == ALIGN_RIGHT)
	{
		info.dwCursorPosition.X = (info.srWindow.Left+info.srWindow.Right)-(strlen(Text));
		SetConsoleCursorPosition(hConsole,info.dwCursorPosition);
		printf("%s\n",Text);
	}
	else
		printf("%s\n",Text);
}

void SceneManager::Fill(byte Color,bool OnlyVisible)
{
	SetConsoleTextAttribute(hConsole,Color*0x10);
	SMALL_RECT rect = GetRect();
	if (OnlyVisible)
	{
		for (int y = 0;y<(rect.Bottom+rect.Top)+1;y++)
			for (int x = 0;x<(rect.Left+rect.Right)+1;x++)
				printf(" ");
	}
	COORD coord = {0,0};
	SetConsoleCursorPosition(hConsole,coord);
	SetConsoleTextAttribute(hConsole,BGColor);
}

void SceneManager::DrawLine(char CHAR,byte color,int len)
{
	SetConsoleTextAttribute(hConsole,BGColor|color);
	for (int i = 0;i<len;i++)
		printf("%c",CHAR);		
}

void SceneManager::DrawCenterBox(int y, int w, int h,byte BorderColor,int nItems,MenuItem *Items)
{
	SMALL_RECT rect = GetRect();
	int x = ((rect.Left+rect.Right)/2)-w/2;
	DrawBox(x,y,w,h,BorderColor,nItems,Items);
}

void SceneManager::DrawBox(int x, int y, int w, int h,byte BorderColor,int nItems,MenuItem* Items)
{
	char corner[4] = {201,187,200,188};
	char line[2] = {205,186};
	COORD coord = {x,y};
	SetConsoleCursorPosition(hConsole,coord);
	//Kasten dravvn
	SetConsoleTextAttribute(hConsole,BGColor|BorderColor);
	printf("%c",corner[0]);
	DrawLine(line[0],BorderColor,w-2);
	printf("%c\n",corner[1]);
	for (int i = 0;i<h;i++)
	{
		coord.X = x;
		coord.Y = y+1+i;
		SetConsoleCursorPosition(hConsole,coord);
		printf("%c",line[1]);
		DrawLine(' ',BorderColor,w-2);
		printf("%c\n",line[1]);
	}
	coord.X = x;
	coord.Y = y+h+1;
	SetConsoleCursorPosition(hConsole,coord);
	printf("%c",corner[2]);
	DrawLine(line[0],BorderColor,w-2);
	printf("%c\n",corner[3]);
	for (int i = 0;i<(nItems-1);i++)
	{
		SetConsoleTextAttribute(hConsole,BGColor | Items[i].color);

		if (Items[i].text_align == ALIGN_CENTER)
		{
			coord.X = (x+(w/2))-(strlen(Items[i].Caption)/2);
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == ALIGN_RIGHT)
		{
			coord.X = (x+w-1)-(strlen(Items[i].Caption));
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == TITLE)
		{
			coord.X = x+2;
			coord.Y = y+0+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
		else
		{
			coord.X = x+1;
			coord.Y = y+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
	}

}

void SceneManager::DrawWin(int wx, int wy, int ww, int wh,byte wBorderColor,int wnItems,MenuItem* Items)
{
	char s = {219};
	
	COORD coord = {wx,wy};
	SetConsoleCursorPosition(hConsole,coord);
	//Kasten dravvn
	SetConsoleTextAttribute(hConsole,BGColor|wBorderColor);
	printf("%c",s);
	DrawLine(s,wBorderColor,ww-2);
	printf("%c\n",s);
	for (int i = 0;i<wh;i++)
	{
		coord.X = wx;
		coord.Y = wy+1+i;
		SetConsoleCursorPosition(hConsole,coord);
		printf("%c",s);
		DrawLine(' ',wBorderColor,ww-2);
		printf("%c\n",s);
	}
	coord.X = wx;
	coord.Y = wy+wh+1;
	SetConsoleCursorPosition(hConsole,coord);
	printf("%c",s);
	DrawLine(s,wBorderColor,ww-2);
	printf("%c\n",s);
	for (int i = 0;i<(wnItems-1);i++)
	{
		SetConsoleTextAttribute(hConsole,BGColor | Items[i].color);

		if (Items[i].text_align == ALIGN_CENTER)
		{
			coord.X = (wx+(ww/2))-(strlen(Items[i].Caption)/2);
			coord.Y = wy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == ALIGN_RIGHT)
		{
			coord.X = (wx+ww-1)-(strlen(Items[i].Caption));
			coord.Y = wy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == TITLE)
		{
			coord.X = wx+2;
			coord.Y = wy+0+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
		else
		{
			coord.X = wx+1;
			coord.Y = wy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
	}
}

void SceneManager::DrawCenterWin(int wy, int ww, int wh,byte wBorderColor,int wnItems,MenuItem *Items)
{
	SMALL_RECT rect = GetRect();
	int x = ((rect.Left+rect.Right)/2)-ww/2;
	DrawWin(x,wy,ww,wh,wBorderColor,wnItems,Items);
}

void SceneManager::DrawCustomWindow(const char* Char, int cx, int cy, int cw, int ch,byte cBorderColor,int cnItems,MenuItem* Items)
{
	//char corner[4] = {201,187,200,188};
	//char line[2] = {205,186};
	//Char[0];
	COORD coord = {cx,cy};
	SetConsoleCursorPosition(hConsole,coord);
	//Kasten dravvn
	SetConsoleTextAttribute(hConsole,BGColor|cBorderColor);
	printf("%c",Char[0]);
	DrawLine(Char[0],cBorderColor,cw-2);
	printf("%c\n",Char[0]);
	for (int i = 0;i<ch;i++)
	{
		coord.X = cx;
		coord.Y = cy+1+i;
		SetConsoleCursorPosition(hConsole,coord);
		printf("%c",Char[0]);
		DrawLine(' ',cBorderColor,cw-2);
		printf("%c\n",Char[0]);
	}
	coord.X = cx;
	coord.Y = cy+ch+1;
	SetConsoleCursorPosition(hConsole,coord);
	printf("%c",Char[0]);
	DrawLine(Char[0],cBorderColor,cw-2);
	printf("%c\n",Char[0]);
	for (int i = 0;i<(cnItems-1);i++)
	{
		SetConsoleTextAttribute(hConsole,BGColor | Items[i].color);

		if (Items[i].text_align == ALIGN_CENTER)
		{
			coord.X = (cx+(cw/2))-(strlen(Items[i].Caption)/2);
			coord.Y = cy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == ALIGN_RIGHT)
		{
			coord.X = (cx+cw-1)-(strlen(Items[i].Caption));
			coord.Y = cy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);
		}
		else if (Items[i].text_align == TITLE)
		{
			coord.X = cx+2;
			coord.Y = cy+0+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
		else
		{
			coord.X = cx+1;
			coord.Y = cy+1+i;
			SetConsoleCursorPosition(hConsole,coord);
			printf("%s",Items[i].Caption);		
		}
	}

}

void SceneManager::DrawCustomCenterWindow(const char* Char, int cy, int cw, int ch,byte cBorderColor,int cnItems,MenuItem *Items)
{
	SMALL_RECT rect = GetRect();
	int x = ((rect.Left+rect.Right)/2)-cw/2;
	DrawCustomWindow(Char,x,cy,cw,ch,cBorderColor,cnItems,Items);
}

void SceneManager::Create_MouseButtonArea(int y_begin , int y_end, int x_begin, int x_end , byte BGColor){

y_begin=-1;
//y_end-1;
x_begin=-1;
//x_end-1;
 hStdInput=GetStdHandle(STD_INPUT_HANDLE);
 hStdOutput=GetStdHandle(STD_OUTPUT_HANDLE);
 FlushConsoleInputBuffer(hStdInput);
 hEvent=CreateEvent(NULL,FALSE,FALSE,NULL);                  //Event is created non-signaled (3rd param).
 HANDLE handles[2] = {hEvent, hStdInput};                    //Program loops monitoring two handles.  The
 while(WaitForMultipleObjects(2,handles,FALSE,INFINITE))     //1st handle ( handles(0) ) is an event which
 {                                                           //is initially set to non-signaled.  The 2nd
  ReadConsoleInput(hStdInput,ir,128,&nRead);                 //handle monitored by WaitForMultipleObjects()
  for(i=0;i<nRead;i++)                                       //is the standard input handle set up to
  {                                                          //allow access to mouse/keyboard input.  As
      switch(ir[i].EventType)                                //long as neither handle is in a signaled
      {                                                      //state, WaitForMultipleObjects() will block
                                   //set to FALSE, the function will return if
       case MOUSE_EVENT:     
		   if(
			ir[i].Event.MouseEvent.dwButtonState & 0x06 &&
			ir[i].Event.MouseEvent.dwMousePosition.X > x_begin &&
			ir[i].Event.MouseEvent.dwMousePosition.X < x_end &&
			ir[i].Event.MouseEvent.dwMousePosition.Y > y_begin &&
			ir[i].Event.MouseEvent.dwMousePosition.Y < y_end
			)
		   
		   {
			  std::cout << "clicked";
		   }

      }
  }
 }


}

void SceneManager::Draw_unexpected_error_msg()
{
	SceneManager* error_msg = new SceneManager();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Error !";
	m[0].color=COLOR_RED;
	m[0].text_align=TITLE;
	std::cout << "\a";
	m[1].Caption="Unhandled expection oscured";
	m[1].color=COLOR_WHITE;
	m[1].text_align=TITLE;

	error_msg->SetBGColor(COLOR_BLUE);
	error_msg->DrawCenterBox(8,30,5,COLOR_GREY,3,m);
	error_msg->free_SceneManager(error_msg);
}

void SceneManager::Draw_costum_error_msg(const char* errortext)
{
	SceneManager* costum_error_msg = new SceneManager();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Error ~";
	m[0].color=COLOR_RED;
	m[0].text_align=TITLE;
	std::cout << "\a";
	m[1].Caption=errortext;
	m[1].color=COLOR_WHITE;
	m[1].text_align=TITLE;

	costum_error_msg->SetBGColor(COLOR_BLUE);
	costum_error_msg->DrawCenterBox(8,30,5,COLOR_GREY,3,m);
	costum_error_msg->free_SceneManager(costum_error_msg);
}

void SceneManager::Draw_costum_warning_msg(const char* warningtext)
{
	SceneManager* costum_warning_msg = new SceneManager();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Warning !!";
	m[0].color=COLOR_RED;
	m[0].text_align=TITLE;
	std::cout << "\a";
	m[1].Caption=warningtext;
	m[1].color=COLOR_WHITE;
	m[1].text_align=TITLE;

	costum_warning_msg->SetBGColor(COLOR_BLUE);
	costum_warning_msg->DrawCenterBox(8,30,5,COLOR_GREY,3,m);
	costum_warning_msg->free_SceneManager(costum_warning_msg);
}

void SceneManager::Draw_costum_info_msg(const char* infotext)
{
	SceneManager* costum_info_msg = new SceneManager();
	MenuItem* m = new MenuItem[3];

	m[0].Caption="Info ?";
	m[0].color=COLOR_RED;
	m[0].text_align=TITLE;
	std::cout << "\a";
	m[1].Caption=infotext;
	m[1].color=COLOR_WHITE;
	m[1].text_align=TITLE;

	costum_info_msg->SetBGColor(COLOR_BLUE);
	costum_info_msg->DrawCenterBox(8,30,5,COLOR_GREY,3,m);
	costum_info_msg->free_SceneManager(costum_info_msg);
}