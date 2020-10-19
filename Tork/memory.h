#pragma once
#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "dllmain.h"

void memory_nop(void* ptr, int size);

class CMetaData
{
public:
	static uint64_t begin();
	static uint64_t end();
	static DWORD size();
	static void init();
private:
	static uint64_t m_begin;
	static uint64_t m_end;
	static DWORD m_size;
};

/*
//CPatternResult
*/
class CPatternResult
{
public:
	CPatternResult(void* pVoid);
	CPatternResult(void* pVoid, void* pBegin, void* pEnd);
	~CPatternResult();

	template <typename rT>
	rT* get(int offset = 0, std::string name = "")
	{
		rT* ret = nullptr;
		if (m_pVoid != nullptr)
		{
			ret = reinterpret_cast<rT*>(reinterpret_cast<char*>(m_pVoid) + offset);
		}
		else 
		{
			console::consoleLog("SIGNATURE", name.c_str());
		}

		return ret;
	}

	template <typename rT>
	rT* get_rel(const int offset = 0)
	{
		rT* result = nullptr;
		char* ptr = get<char>(offset);

		if (ptr != nullptr)
		{

			int32_t rel = *(int32_t*)ptr;
			result = reinterpret_cast<rT*>(ptr + rel + sizeof rel);
		}
		return result;
	}

	template <typename rT>
	rT* section_begin()
	{
		return reinterpret_cast<rT*>(m_pBegin);
	}

	template <typename rT>
	rT* section_end()
	{
		return reinterpret_cast<rT*>(m_pEnd);
	}

protected:
	void* m_pVoid = nullptr;
	void* m_pBegin = nullptr;
	void* m_pEnd = nullptr;
};

/*
//CPattern
*/

typedef std::vector<CPatternResult> vec_result;

class CPattern
{
public:
	CPattern(const char szByte[], const char szMask[]);
	~CPattern();

	CPattern& find(int i = 0, uint64_t startAddress = 0); //scans for i patterns
	CPattern& virtual_find(int i = 0, uint64_t startAddress = 0);
	CPatternResult get(int i); //returns result i

protected:
	char* m_szByte;
	char* m_szMask;
	bool m_bSet;
	vec_result m_result;

	bool match(int i = 0, uint64_t startAddress = 0, bool virt = false);
	static bool byte_compare(const BYTE* pData, const BYTE* btMask, const char* szMask);
	uint64_t find_pattern(uint64_t i64Address, uint64_t end, BYTE* btMask, char* szMask);
	uint64_t virtual_find_pattern(uint64_t address, BYTE* btMask, char* szMask);
};

#endif
