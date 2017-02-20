#include "stdafx.h"
#include "gtest.h"

#include "Array.h"

using ArrayPtr = MyLib::System::Container::Array < int, MyLib::System::Container::SimpleArrayImpl < int, MyLib::System::Memory::HeapAllocator<int> > >;

TEST(ArrayTest, CreationAndDisposal)
{
	ArrayPtr *ap;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	delete ap;
}

TEST(ArrayTest, Size)
{
	ArrayPtr *ap;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));

	ASSERT_EQ(true, ap->SetSize(10)); 
	ASSERT_EQ(10, ap->GetSize());

	ASSERT_EQ(false, ap->SetSize(-1));
	ASSERT_EQ(10, ap->GetSize());

	ASSERT_EQ(true, ap->SetSize(0));
	ASSERT_EQ(0, ap->GetSize());

	ASSERT_EQ(true, ap->SetSize(80000));
	ASSERT_EQ(80000, ap->GetSize());

	delete ap;
}

TEST(ArrayTest, Elementaccess)
{
	ArrayPtr *ap;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	ArrayPtr &ar = *ap;

	ASSERT_EQ(true, ap->SetSize(1000));

	ap->SetAt(0, 111);
	ASSERT_EQ(111, ap->GetAt(0));
	ASSERT_EQ(111, ar[0]);

	ar.SetAt(0, -5);
	ASSERT_EQ(-5, ap->GetAt(0));
	ASSERT_EQ(-5, ar[0]);

	ar.SetAt(500, 111);
	ASSERT_EQ(111, ap->GetAt(500));
	ASSERT_EQ(111, ar[500]);

	delete ap;
}

TEST(ArrayTest, Assignment)
{
	ArrayPtr *ap1, *ap2;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap1 = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap2 = new ArrayPtr()));

	ArrayPtr &ar1 = *ap1;
	ArrayPtr &ar2 = *ap2;

	ASSERT_EQ(true, ap1->SetSize(1000));
	ASSERT_EQ(true, ap2->SetSize(1000));

	ap1->SetAt(0, -5);
	ap1->SetAt(111, -5);
	ap1->SetAt(222, -5);

	ar1 = ar1;
	ASSERT_EQ(ap1, ap1);

	ar1 = ar2; 
	ASSERT_NE(ap1, ap2);
	
	ASSERT_EQ(ap1->GetAt(0), ap1->GetAt(0));
	ASSERT_EQ(ap1->GetAt(0), -5);

	ASSERT_EQ(ap1->GetAt(111), ap2->GetAt(111));
	ASSERT_EQ(ap1->GetAt(111), -5);

	ASSERT_EQ(ap1->GetAt(222), ap2->GetAt(222));
	ASSERT_EQ(ap2->GetAt(222), -5);

	delete ap1;
	delete ap2;
}

