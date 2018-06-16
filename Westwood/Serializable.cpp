#include "Serializable.h"

void CSerializable::OpenFileForRead(const char * a_filePath)
{
	m_inFileHandle.open(a_filePath, std::ifstream::binary);
}

void CSerializable::CloseReadFile()
{
	m_inFileHandle.close();
}

void CSerializable::OpenFileForWrite(const char * a_filePath)
{
	m_outFileHandle.open(a_filePath, std::ofstream::binary);
}

void CSerializable::CloseWriteFile()
{
	m_outFileHandle.close();
}
