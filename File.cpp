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



void FileSystem::create_File(const char* cFileName, const char* cFileType){


string sFN = cFileName;
string sFT = cFileType;
string sPDE = ".";
string sSTR = sFN+sPDE+sFT;


fstream IFileStream(sSTR.c_str(), ios::app | ios::out);

IFileStream.close();

}

void FileSystem::read_File(const char* cFileName){
	string line;
  ifstream IFile (cFileName);

  if (IFile.is_open())
  {
    while ( IFile.good() )
    {
      getline (IFile,line);
      cout << line << endl;
    }
    IFile.close();
  }

  else cout << "Unable to open file"; 

}

void FileSystem::close_File(){
	fstream IFileStream;

	
if (IFileStream.is_open())
  {
	 IFileStream.close(); }

	ifstream IFile;

if (IFile.is_open())
  {
  
	 IFile.close(); }
	
	//else { MessageBox(NULL, L"Es ist kein filestream offen!", L"Error", MB_OK); exit(1);}
}

void FileSystem::write_File(const char* cFOutStream, const char* cFileName, const char* cFSetting){

string sSTR = cFileName;

if(cFSetting == "normal"){

fstream File(sSTR.c_str(), ios::out);
 if (File.is_open()) {
 File << cFOutStream;
 }
 else {cout << "Unable to open file"; }

 File.close();
}


if (cFSetting == "add_at_end"){
fstream File(sSTR.c_str(), ios::app | ios::out);
 if (File.is_open()) {
 File << cFOutStream;
 }
 else {cout << "Unable to open file"; }

 File.close();
}


if (cFSetting == "delete_on_open"){
fstream File(sSTR.c_str(), ios::trunc | ios::out);

 if (File.is_open()) {
 File << cFOutStream;
 }
 else {cout << "Unable to open file"; }

 File.close();
}

}


/*FileSystem* create_pFileSystem(FileSystem* pCCEFile){
	return pCCEFile;
} */
