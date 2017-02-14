// MyLibTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../googletest/include/gtest/gtest.h"


extern int MainTestRun(int argc, _TCHAR* argv[]);

__declspec(dllimport) bool DummyFunc();


int _tmain(int argc, _TCHAR* argv[])
{
	return MainTestRun(argc, argv);
}

