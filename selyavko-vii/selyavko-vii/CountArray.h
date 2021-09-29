#pragma once
#include "afxmt.h"
class CCountArray
{
private:
	int array[10];
	CCriticalSection criticalSection;
public:
	CCountArray() {};
	~CCountArray() {};
	void SetArray(int value);
	void GetArray(int dstArray[10]);
};
