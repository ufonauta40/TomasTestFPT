// MyLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "gtest.h"


__declspec(dllexport) bool DummyFunc()
{
	return true;
}
