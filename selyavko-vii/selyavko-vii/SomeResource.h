#pragma once

#include "afxmt.h"
class CSomeResource {
private:
	CSemaphore* semaphore;
public:
	CSomeResource();
	~CSomeResource();
	void UseResource();
};
