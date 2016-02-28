#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

class SaveFile
{
public:
	//Constructor 
	SaveFile(char* s);
	//Deconstuctor (just calls free())
	~SaveFile();

	//Deallocates all the stuff that should be deallocated
	void free();

	//Writes text to file
	void write(char* write, int type);

	void close();

	char* read();

private:
	char *filepath;
	std::fstream myfile;
	
	enum Open
	{
		READ,
		OVERWRITE,
		APPEND
	};

	/*
	0: Unclaimed
	1: Triangle
	2: Square
	3: Pentagon
	*/
};