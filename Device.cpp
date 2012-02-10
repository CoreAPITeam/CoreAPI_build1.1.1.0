#include "Device.h"
#include <Windows.h>
#include <fstream>
#include "CSTYPES.h"
#include "CCEScenemanager.h"
#include <iostream>
#include <string>

using namespace cdev;
using namespace std;
using namespace CCESceneManager;

#define csERROR	cout<<"Shader Error"<<endl;exit(1);

Device::Device(/*167,66*/short iScreenx,short iScreeny,const char* cConsoleTitle,bool bShowCursor)
{
	HANDLE hConsoleOutput;
    COORD coord;
    CONSOLE_SCREEN_BUFFER_INFO  ConsoleInfo;
    HWND console = GetConsoleWindow();

    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
    coord.X = iScreenx;
    coord.Y = iScreeny;
    SetConsoleScreenBufferSize(hConsoleOutput, coord);

    MoveWindow(console, 20, 20, 1200, 600, TRUE);

	SetConsoleTitleA(cConsoleTitle);

	static HANDLE		hOut;
	static BOOL		firstTime = TRUE;
	CONSOLE_CURSOR_INFO 	cursorInfo;

	if( firstTime )
	{

		hOut		= GetStdHandle( STD_OUTPUT_HANDLE );
		firstTime	= FALSE;

	}

	cursorInfo.dwSize	= 10;
	cursorInfo.bVisible 	= bShowCursor;

	SetConsoleCursorInfo( hOut,
                              &cursorInfo );

}

void Device::show_cursor(bool bShowCursor)
{
	static HANDLE		hOut;
	static BOOL		firstTime = TRUE;
	CONSOLE_CURSOR_INFO 	cursorInfo;

	if( firstTime )
	{

		hOut		= GetStdHandle( STD_OUTPUT_HANDLE );
		firstTime	= FALSE;

	}

	cursorInfo.dwSize	= 10;
	cursorInfo.bVisible 	= bShowCursor;

	SetConsoleCursorInfo( hOut,
                              &cursorInfo );
} 

void csDevice::loadCSFromFile(const char* csFilename , float fcsVer)
{
	ifstream cs_input_data(csFilename);
	if(!cs_input_data){csERROR}
	FLOAT4 shader_VERSION;
		string space;
			FLOAT4 shader_STUCKDEF;
				FLOAT4 torken;
					FLOAT4 shader_CS_PTR;
						FLOAT4 shader_colordef;
							FLOAT4 shader_color_output;

	getline(cs_input_data,shader_VERSION);
	getline(cs_input_data,space);
	getline(cs_input_data,shader_STUCKDEF);
	getline(cs_input_data,torken);
	getline(cs_input_data,space);
	getline(cs_input_data,shader_CS_PTR);
	getline(cs_input_data,shader_CS_PTR);
		getline(cs_input_data,shader_colordef);
		getline(cs_input_data,shader_colordef);
	getline(cs_input_data,shader_color_output);
		getline(cs_input_data,torken);
		getline(cs_input_data,space);
	getline(cs_input_data,shader_CS_PTR);


cout << shader_color_output;

}

void Device::freeDevice(Device* MyDevice){ 
	delete MyDevice;
}


