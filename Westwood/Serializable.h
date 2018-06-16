#pragma once
#include <fstream>

class CSerializable
{
public:
	virtual void OpenFromFile(const char* a_filePath) = 0;
	virtual void SaveToFile(const char* a_filePath) = 0;
protected:
	void OpenFileForRead(const char* a_filePath);
	void CloseReadFile();
	void OpenFileForWrite(const char* a_filePath);
	void CloseWriteFile();

	std::ifstream m_inFileHandle;
	std::ofstream m_outFileHandle;

};