// MyLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../googletest/include/gtest/gtest.h"


__declspec(dllexport) bool DummyFunc()
{
	return true;
}
