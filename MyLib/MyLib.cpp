// MyLib.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../googletest/include/gtest/gtest.h"


bool DummyFunc()
{
	return true;
}

TEST(novy, Dummy)
{
	ASSERT_EQ(true, DummyFunc());
} 

__declspec(dllexport) int MainTestRun(int argc, _TCHAR* argv[])
{

	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}