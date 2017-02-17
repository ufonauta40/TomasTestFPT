// MyLibTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gtest.h"


extern bool DummyFunc();


TEST(novy, Dummy)
{
	ASSERT_EQ(true, DummyFunc());
}

TEST(ArrayTest, creationanddisposal)
{
	ArrayPtr *ap;
	ASSERT_NE(NULL, ArrayInit(ap));
	ASSERT_EQ(NULL, ArrayDispose(ap));
}

TEST(ArrayTest, size)
{
	ArrayPtr *ap;
	ASSERT_NE(NULL, ArrayInit(ap));

	ASSERT_EQ(true, ArraySetSize(10, ap));
	ASSERT_EQ(10, ArrayGetSize(ap));

	ASSERT_EQ(false, ArraySetSize(-1, ap));
	ASSERT_EQ(10, ArrayGetSize(ap));

	ASSERT_EQ(true, ArraySetSize(0, ap));
	ASSERT_EQ(10, ArrayGetSize(ap));

	ASSERT_EQ(true, ArraySetSize(80000, ap));
	ASSERT_EQ(80000, ArrayGetSize(ap));

	ASSERT_EQ(NULL, ArrayDispose(ap));
}

TEST(ArrayTest, elementaccess)
{
	ArrayPtr *ap;
	ASSERT_NE(NULL, ArrayInit(ap));
	ASSERT_EQ(true, ArraySetSize(1000, ap));

	ArraySetValue(BY_FUNC, 0, 111, ap);
	ASSERT_EQ(111, ArrayGetValue(BY_FUNC, 0, ap));
	ASSERT_EQ(111, ArrayGetValue(LIKE_VECTOR, 0, ap));

	ArraySetValue(BY_FUNC, 0, -5, ap);
	ASSERT_EQ(-5, ArrayGetValue(BY_FUNC, 0, ap));
	ASSERT_EQ(-5, ArrayGetValue(LIKE_VECTOR, 0, ap));

	ArraySetValue(LIKE_VECTOR, 500, 111, ap);
	ASSERT_EQ(111, ArrayGetValue(BY_FUNC, 500, ap));
	ASSERT_EQ(111, ArrayGetValue(LIKE_VECTOR, 500, ap));

	ASSERT_EQ(NULL, ArrayDispose(ap));
}

TEST(ArrayTest, assignment)
{
	ArrayPtr *ap1, *ap2;
	ASSERT_NE(NULL, ArrayInit(ap1));
	ASSERT_NE(NULL, ArrayInit(ap2));
	ASSERT_EQ(true, ArraySetSize(1000, ap1));
	ASSERT_EQ(true, ArraySetSize(1000, ap2));

	ArraySetValue(BY_FUNC, 0, -5, ap1);
	ArraySetValue(BY_FUNC, 111, -5, ap1);
	ArraySetValue(BY_FUNC, 222, -5, ap1);

////////////////////////
	ArrayAssign(ap1, ap1);
	ASSERT_EQ(ap1, ap1);

/////////////////////////
	ArrayAssign(ap1, ap2);
	ASSERT_EQ(ArrayGetValue(BY_FUNC, 0, ap1), ArrayGetValue(BY_FUNC, 0, ap2));
	ASSERT_EQ(ArrayGetValue(BY_FUNC, 0, ap1), -5);

	ASSERT_EQ(ArrayGetValue(BY_FUNC, 111, ap1), ArrayGetValue(BY_FUNC, 111, ap2));
	ASSERT_EQ(ArrayGetValue(BY_FUNC, 111, ap1), -5);

	ASSERT_EQ(ArrayGetValue(BY_FUNC, 222, ap1), ArrayGetValue(BY_FUNC, 222, ap2));
	ASSERT_EQ(ArrayGetValue(BY_FUNC, 222, ap1), -5);
	
	ASSERT_EQ(NULL, ArrayDispose(ap1));
	ASSERT_EQ(NULL, ArrayDispose(ap2));
}



int _tmain(int argc, _TCHAR* argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}

