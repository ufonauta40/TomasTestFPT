// MyLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "gtest.h"
#include "System/Container/Array.h"


#include "MyLib.h"

__declspec(dllexport) bool DummyFunc()
{
	return true;
}

ArrayPtr * Test::ArrayInit(ArrayPtr * ap)
{
	ap = new ArrayPtr();
	return ap;
}

void ArrayDispose(ArrayPtr * ap)
{
	delete[] ap;
}

bool ArraySetSize(int size, ArrayPtr* ap)
{
	return ap->SetSize(size);
}

int ArrayGetSize(ArrayPtr *ap)
{
	return ap->GetSize();
}

int ArrayGetValue(Test::ACCESS_TYPE at, int index, ArrayPtr* ap)
{	
	switch (at)
	{
		case BY_FUNC: return ap->GetAt(index); 
		case LIKE_VECTOR: return ap[index];
	}
}

void ArraySetValue(ACCESS_TYPE at, int index, int value, ArrayPtr*ap)
{
	switch (at)
	{
		case BY_FUNC: ap->SetAt(index, value); break;
		case LIKE_VECTOR: ap[index] = value;
	}
}

void ArrayAssign(ArrayPtr *ap1, ArrayPtr *ap2)
{
	ap1 = ap2;
}