#include "stdafx.h"
#include "SomeResource.h"

CSomeResource::CSomeResource() {
	semaphore = new CSemaphore(2, 2);
}

CSomeResource::~CSomeResource() {
	delete semaphore;
}
void CSomeResource::UseResource() {
	CSingleLock singleLock(semaphore);
	singleLock.Lock();
	Sleep(5000);
}
