#include <Windows.h>
#include <fstream>
#include "CSTYPES.h"
#include <string>


using namespace std;
namespace cdev{

class Device
{
private :
	short iScreenx;
	short iScreeny;
	const char* cConsoleTitle;
	bool bShowCursor;
	const char* datapath;
	const char* accescode;

public :

	Device(short iScreenx, short iScreeny,const char* cConsoleTitle,bool bShowCursor);
	void show_cursor(bool bShowCursor);


	void freeDevice(Device* MyDevice);

	void StrCheckSysData(string datapath,const char* accescode);
};

class csDevice
{
private :

	const char csFilename;
	float fcsVer;

public :
	void loadCSFromFile(const char* csFilename, float fcsVer);
};

}