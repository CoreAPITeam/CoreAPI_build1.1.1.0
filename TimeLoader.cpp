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
#include "Device.h"
#include "File.h"
#include "TimeLoader.h"
#include "SceneManager.h"




void Loader::create_TimeLoader(	int iPosX,
									int iPosY,
									int iTime_per_repeat,
									int iPercent){

Device PC;

PC.set_ICursorPos2d(iPosX,iPosY);
int a;

for(a=1; a < iPercent; a++)
{
		
		 cout <<"[ " <<  a << "% ]" << endl;
		 PC.set_ICursorPos2d(iPosX,iPosY);
		 Sleep(iTime_per_repeat);
		 if( a == iPercent){break;}
} 	



}