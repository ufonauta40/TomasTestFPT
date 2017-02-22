#include "stdafx.h"
#include "gtest.h"

#include "Array.h"

using ArrayPtr = MyLib::System::Container::Array < int, MyLib::System::Container::SimpleArrayImpl < int, MyLib::System::Memory::HeapAllocator<int> > >;


//Test Array class construction
TEST(ArrayTest, CreationAndDisposal)
{
	ArrayPtr *ap;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	delete ap;
}


//Set and check sizes of an Array to various lengths
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

//Try to access elements of the Array by function or with parentheses
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


//Assign the whole Array to another variable
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

///// Iterator testing

//Test Iterator class construction
TEST(ArrayTest, IteratorInit)
{
	ArrayPtr *ap;
	ArrayPtr::Iterator* ip;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip = new ArrayPtr::Iterator(ap))); 
	
	delete ip;
	delete ap;
}

// Call the Reset() function which should initialize the Iterator to the parameter 
// Array class and set iteration pointer to first item.
TEST(ArrayTest, IteratorReset)
{
	ArrayPtr *ap1, *ap2;
	ArrayPtr::Iterator* ip;

	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap1 = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip = new ArrayPtr::Iterator(ap1)));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap2 = new ArrayPtr()));

	ap1->SetAt(0, 111);
	ap1->SetAt(1, 112);
	++(*ip);
	
	ap2->SetAt(0, 222);

	ip->Reset(ap2); 

	ASSERT_EQ(**ip, ap2->GetAt(0));

	delete ip;
	delete ap1;
	delete ap2;
}

// Test the ++operator which provides forward traversing through the Array
TEST(ArrayTest, IteratorAdvance)
{
	ArrayPtr *ap;
	ArrayPtr::Iterator* ip;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip = new ArrayPtr::Iterator(ap)));

	ASSERT_EQ(true, ap->SetSize(1000));
	
	ap->SetAt(0, 111);
	ap->SetAt(1, 222);

	ASSERT_EQ(111, **ip);

	++(*ip);  // Advance iterator by one

	ASSERT_EQ(222, **ip); // and check value

	delete ip;
	delete ap;
}

// Testing the equality '==' operator which compares Iterator pointing.
// The result is true if both are pointing to the same object inside the Array
TEST(ArrayTest, IteratorEqual)
{
	ArrayPtr *ap, *ap2;
	ArrayPtr::Iterator* ip, *ip2;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip = new ArrayPtr::Iterator(ap)));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip2 = new ArrayPtr::Iterator(ap)));

	ASSERT_EQ(true, ap->SetSize(1000));

	ap->SetAt(0, 111);
	ap->SetAt(1, 222);

	ASSERT_EQ(true, *ip == *ip2);   // ip[1] = ip2[1] ?
	++(*ip);
	ASSERT_EQ(false, *ip == *ip2);  // ip[1] = ip[2] ?
	++(*ip2);
	ASSERT_EQ(true, *ip == *ip2); // ip[2] = ip[2] ?
	ip->Reset(ap);
	ASSERT_EQ(false, *ip == *ip2); // After reset: ip[1] = ip[2] ?
	ip2->Reset(ap);
	ASSERT_EQ(true, *ip == *ip2);  // After reset: ip[1] = ip[1] ?

	delete ip2;

	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap2 = new ArrayPtr()));
	
	ip2 = new ArrayPtr::Iterator(ap2);
	ASSERT_EQ(true, ap2->SetSize(1000));

	ASSERT_EQ(false, *ip == *ip2); // Whether 2 iterators pointing to different objects but to the same index are equal

	delete ip2;
	delete ip;
	delete ap;
	delete ap2;
}

// Testing the inequality '!=' operator which compares Iterator pointing.
// The result is true if both are pointing to different objects inside the Array 
TEST(ArrayTest, IteratorNotEqual)
{
	ArrayPtr *ap, *ap2;
	ArrayPtr::Iterator* ip, *ip2;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip = new ArrayPtr::Iterator(ap)));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip2 = new ArrayPtr::Iterator(ap)));

	ASSERT_EQ(true, ap->SetSize(1000));

	ap->SetAt(0, 111);
	ap->SetAt(1, 222);

	ASSERT_EQ(false, *ip != *ip2);   // ip[1] != ip2[1] ?
	++(*ip);
	ASSERT_EQ(true, *ip != *ip2);  // ip[1] != ip[2] ?
	++(*ip2);
	ASSERT_EQ(false, *ip != *ip2); // ip[2] != ip[2] ?
	ip->Reset(ap);
	ASSERT_EQ(true, *ip != *ip2); // After reset: ip[1] != ip[2] ?
	ip2->Reset(ap);
	ASSERT_EQ(false, *ip != *ip2);  // After reset: ip[1] != ip[1] ?

	delete ip2;

	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap2 = new ArrayPtr()));

	ip2 = new ArrayPtr::Iterator(ap2);

	ASSERT_EQ(true, *ip != *ip2); // Whether 2 iterators pointing to different objects but to the same index are unequal 

	delete ip2;
	delete ip;
	delete ap;
	delete ap2;
}

// Testing the GetContainer() function which should return the Array object to whom the Iterator is set to.
TEST(ArrayTest, IteratorGetContainer)
{
	ArrayPtr *ap;
	ArrayPtr::Iterator* ip;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip = new ArrayPtr::Iterator(ap)));

	ASSERT_EQ(ip->GetContainer(), ap);  // Container of the Iterator must match function return value

	delete ip;
	delete ap;
}

// Testing the GetIndex() function which should return the index of the object where the Iterator is 
// pointing to in the Array
TEST(ArrayTest, IteratorGetIndex)
{
	ArrayPtr *ap;
	ArrayPtr::Iterator* ip;
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ap = new ArrayPtr()));
	ASSERT_NE(NULL, reinterpret_cast<uintptr_t> (ip = new ArrayPtr::Iterator(ap)));

	ASSERT_EQ(true, ap->SetSize(1000)); 
	
	ASSERT_EQ(ip->GetIndex(), 0);  // Checking initialization value
	++(*ip);
	ASSERT_EQ(ip->GetIndex(), 1);   // Traverse by one upward

	delete ip;
	delete ap;
}

