
#ifndef FILE_H
#define FILE_H




class FileSystem {

private :

	 	char cFileName;
		char cFileType;
		char cFOutSream;
		char cFstream;
		char cFSetting;


		

public :

	void create_File(const char* cFileName, const char* cFileType);
	void close_File();
	void read_File(const char* cFileName);
	void write_File(const char* cFOutSream,const char* cFileName, const char* cFSetting);

	//FileSystem* create_pFileSystem();

	// IFile clear
	// IFile store io path

};



#endif