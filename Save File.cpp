#include <stdio.h>
#include <string>
#include "Save File.h"
#include <iostream>
#include <fstream>

SaveFile::SaveFile(char* s)
{
	filepath = s;
}

SaveFile::~SaveFile()
{
	//Deallocate
	free();
}

void SaveFile::free()
{
	if (filepath != NULL)
	{
		filepath = NULL;
	}
	if (myfile.is_open)
	{
		myfile.close();
	}
	
}

void SaveFile::write(char* write, int type)
{
	switch (type)
	{
	case OVERWRITE:
		myfile.open(filepath, std::ios::out | std::ios::trunc );
		break;
	case APPEND:
		myfile.open(filepath, std::ios::out | std::ios::app);
		break;
	default:
		return;
	}

	myfile << write << "\n";

	myfile.close();

}

char* SaveFile::read()
{
	myfile.open(filepath, std::ios::in);
	
	std::string line;

	char* file_str;

	myfile >> file_str;

	myfile.close;

	return file_str;
}

void SaveFile::close()
{
	myfile.close();
}