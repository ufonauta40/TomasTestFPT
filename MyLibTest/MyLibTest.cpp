// MyLibTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest.h"


extern bool DummyFunc();


TEST(novy, Dummy)
{
	ASSERT_EQ(true, DummyFunc());
}



int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

