#ifndef TIMELOADER_H
#define TIMELOADER_H




class Loader{

private :
	unsigned int iPosX;
	unsigned int iPosY;
	unsigned int iTime_per_repeat;
	unsigned int iPercent;

public :

	void create_TimeLoader(int iPosX ,int iPosY, int iTime_per_repeat, int iPercent);
};



#endif