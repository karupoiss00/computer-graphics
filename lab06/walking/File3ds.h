#pragma once
#include <lib3ds.h>

class CFile3ds

{
public:
	CFile3ds(Lib3dsFile* pFile)
		: m_pFile(pFile)
	{

	}

	~CFile3ds()
	{
		if (m_pFile)

		{
			lib3ds_file_free(m_pFile);
		}
	}

private:
	CFile3ds(CFile3ds const&) = delete;
	CFile3ds& operator=(CFile3ds const&) = delete;

	Lib3dsFile* m_pFile;
};