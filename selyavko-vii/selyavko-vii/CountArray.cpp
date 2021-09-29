#include "stdafx.h" 
#include "CountArray.h"

void CCountArray::SetArray(int value)
{
	criticalSection.Lock();
	for (int x = 0; x<10; ++x)
		array[x] = value;
	criticalSection.Unlock();
}
void CCountArray::GetArray(int dstArray[10])
{
	criticalSection.Lock();
	for (int x = 0; x<10; ++x)
		dstArray[x] = array[x];
	criticalSection.Unlock();
}
