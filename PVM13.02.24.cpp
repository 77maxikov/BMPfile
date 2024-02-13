#include <iostream>
#include <fstream>
//#define DEBUG

unsigned char* create_bmp(unsigned int weight, unsigned int height)
{
	std::fstream hex;
	hex.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	if (!hex.is_open())
	{
		std::cout << "error3" << std::endl;
		return nullptr;
	}
	long int rowSize=((weight+31)/32)*4;
	long int bodySize = rowSize * height;
	long int fileSize = bodySize  + 62;
	unsigned char* bmpPtr = new unsigned char[fileSize];
	for (size_t i = 0; i < 62; ++i)
	{
		hex >> bmpPtr[i];
	}
	hex.close();
	for (size_t i = 62; i < fileSize; ++i)
	{
		bmpPtr[i] = 0;
	}
	int tmp;

	bmpPtr[18] = weight >> 12;
	tmp = weight << 4;
	bmpPtr[19] = tmp >> 12;
	tmp = weight << 8;
	bmpPtr[20] = tmp >> 12;
	tmp = weight << 12;
	bmpPtr[21] = tmp >> 12;

	bmpPtr[22] = height >> 12;
	tmp = height << 4;
	bmpPtr[23] = tmp >> 12;
	tmp = height << 8;
	bmpPtr[24] = tmp >> 12;
	tmp = height << 12;
	bmpPtr[25] = tmp >> 12;

	bmpPtr[2] = fileSize >> 12;
	tmp = fileSize << 4;
	bmpPtr[3] = tmp >> 12;
	tmp = fileSize << 8;
	bmpPtr[4] = tmp >> 12;
	tmp = fileSize << 12;
	bmpPtr[5] = tmp >> 12;

	bmpPtr[34] = bodySize >> 12;
	tmp = bodySize << 4;
	bmpPtr[35] = tmp >> 12;
	tmp = bodySize << 8;
	bmpPtr[36] = tmp >> 12;
	tmp = bodySize << 12;
	bmpPtr[37] = tmp >> 12;

	return bmpPtr;
}

void write_bmp(const char* nameFile, unsigned char* bmp_ptr)
{
	std::fstream file;
	file.open(nameFile, std::ios_base::out | std::ios_base::binary);
	int fileSize=(bmp_ptr[2]<<12)|(bmp_ptr[3]<<8)|(bmp_ptr[4]<<4)|(bmp_ptr[5]);
	file.write((char*)bmp_ptr, fileSize);
	file.close();
}

int main()
{
	std::cout << "Hi. I'm working"<<std::endl;
#ifdef DEBUG
	std::fstream file1;
	file1.open("Number1_1152x648.bmp",std::ios_base::in|std::ios_base::binary);
	if (!file1.is_open())
	{
		std::cout << "file1 isn't open. error1" << std::endl;
		std::system("pause");
		return 1;
	}
	file1.seekg(10,std::ios_base::beg);
	int nomber1=0;
	file1.read((char*)(&nomber1), 4);
	std::cout << sizeof(nomber1) << std::endl;
	std::cout << nomber1 << std::endl;
	file1.seekg(0, std::ios_base::beg);
	char* hexFile = new char[nomber1];
	file1.read(hexFile, nomber1);
	file1.close();

	file1.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	file1.write(hexFile, nomber1);
	file1.close();

	delete[] hexFile;

	file1.open("Number1_1152x648.bmp", std::ios_base::in | std::ios_base::binary);
	int w;
	int h;
	file1.seekg(18, std::ios_base::beg);
	file1.read((char*)(&w), 4);
	file1.seekg(22, std::ios_base::beg);
	file1.read((char*)(&h), 4);
	std::cout << w << std::endl;//144
	std::cout << h << std::endl;//93312
	file1.seekg(34, std::ios_base::beg);
	int imageSize;
	file1.read((char*)(&imageSize), 4);
	std::cout << imageSize << std::endl;
	file1.close();

	file1.open("template.bmp", std::ios_base::out | std::ios_base::binary);
	unsigned int n = 0;
	file1.seekp(2, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.seekp(18, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.seekp(22, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.seekp(34, std::ios_base::beg);
	file1.write((char*)(&n), 4);
	file1.close();

	forBmp a;
	std::cout << sizeof(a) << std::endl;
#endif // DEBUG
	write_bmp("Hi.bmp", create_bmp(40, 40));
	std::system("pause");
    return 0;
}

