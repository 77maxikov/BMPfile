#pragma once
#ifndef BMP_FILES_PVM
#define BMP_FILES_PVM

#include <iostream>

class BMPfile
{
	unsigned char* bmpPtr;
	unsigned *m_height;
	unsigned *m_width;
	
	static const size_t HEADER_SIZE = 62;
public:
	BMPfile(unsigned int weight = 1000, unsigned int height = 1000);
	BMPfile(const char* namefile);
	~BMPfile();
	void saveBmp(const char* nameFile="print.bmp");
	void setPixel(unsigned int positionM, unsigned int positionN, bool size) const;
	unsigned int getWidth()const;
	unsigned int getHeight()const;
	bool getPixel(unsigned int positionM, unsigned int positionN) const;
};

#endif