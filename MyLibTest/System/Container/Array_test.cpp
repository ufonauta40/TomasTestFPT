#include "stdafx.h"
#include "gtest.h"

#include "Array.h"


namespace MyLib { namespace Test { namespace System { namespace Container {


using namespace MyLib::System::Container;

//Test Array class construction
TEST(ArrayTest, CreationAndDisposal)
{
    HeapSimpleArray<int> a;
    EXPECT_EQ(a.GetSize(), 0);
}


//Set and check sizes of an Array to various lengths
TEST(ArrayTest, Size)
{
    HeapSimpleArray<int> a;

    EXPECT_EQ(true, a.SetSize(10));
    EXPECT_EQ(10, a.GetSize());

    EXPECT_EQ(false, a.SetSize(-1));
    EXPECT_EQ(10, a.GetSize());

    EXPECT_EQ(true, a.SetSize(0));
    EXPECT_EQ(0, a.GetSize());

    EXPECT_EQ(true, a.SetSize(80000));
    EXPECT_EQ(80000, a.GetSize());

}

//Try to access elements of the Array by function or with parentheses
TEST(ArrayTest, ElementAccess)
{
    HeapSimpleArray<int> a;

    EXPECT_EQ(true, a.SetSize(1000));

    a.SetAt(0, 111);
    EXPECT_EQ(111, a.GetAt(0));
    EXPECT_EQ(111, a[0]);

    a.SetAt(0, -5);
    EXPECT_EQ(-5, a.GetAt(0));
    EXPECT_EQ(-5, a[0]);

    a[0] = -5;
    EXPECT_EQ(-5, a.GetAt(0));
    EXPECT_EQ(-5, a[0]);

    a.SetAt(500, 111);
    EXPECT_EQ(111, a.GetAt(500));
    EXPECT_EQ(111, a[500]);

    a[500] = 20;
    EXPECT_EQ(20, a.GetAt(500));
    EXPECT_EQ(20, a[500]);

    a.SetAt(40, 500);
    EXPECT_EQ(500, a.GetAt(40));
    a[41] = 501;
    EXPECT_EQ(500, a.GetAt(40));
    EXPECT_EQ(501, a.GetAt(41));
    a[42] = 502;
    EXPECT_EQ(502, a.GetAt(42));
}


//Assign the whole Array to another variable
TEST(ArrayTest, Assignment)
{
    HeapSimpleArray<int> a1, a2;

    EXPECT_EQ(true, a1.SetSize(1000));
    EXPECT_EQ(true, a2.SetSize(1000));

    a1.SetAt(0, -5);
    a1.SetAt(111, -5);
    a1.SetAt(222, -5);

    a1 = a1;
    EXPECT_EQ(&a1, &a1);

    a1 = a2; 
    EXPECT_NE(&a1, &a2);
    
    EXPECT_EQ(a1.GetAt(0), a1.GetAt(0));
    EXPECT_EQ(a1.GetAt(0), -5);

    EXPECT_EQ(a1.GetAt(111), a2.GetAt(111));
    EXPECT_EQ(a1.GetAt(111), -5);

    EXPECT_EQ(a1.GetAt(222), a2.GetAt(222));
    EXPECT_EQ(a2.GetAt(222), -5);
}

///// Iterator testing

//Test Iterator class construction
TEST(ArrayTest, IteratorInit)
{
    HeapSimpleArray<int> a;
    HeapSimpleArray<int>::Iterator i(&a);
}

// Call the Reset() function which should initialize the Iterator to the parameter 
// Array class and set iteration pointer to first item.
TEST(ArrayTest, IteratorReset)
{
    HeapSimpleArray<int> a1, a2;
    HeapSimpleArray<int>::Iterator i(&a1);

    a1.SetAt(0, 111);
    a1.SetAt(1, 112);
    ++i;
    
    a2.SetAt(0, 222);

    i.Reset(&a2); 

    EXPECT_EQ(*i, a2.GetAt(0));
}

// Test the ++operator which provides forward traversing through the Array
TEST(ArrayTest, IteratorAdvance)
{
    HeapSimpleArray<int> a;
    HeapSimpleArray<int>::Iterator i(&a);

    EXPECT_EQ(true, a.SetSize(1000));
    
    a.SetAt(0, 111);
    a.SetAt(1, 222);

    EXPECT_EQ(111, *i);

    ++i; 

    EXPECT_EQ(222, *i) << "Advance iterator by one and check value";
}

// Testing the equality '==' operator which compares Iterator pointing.
// The result is true if both are pointing to the same object inside the Array
TEST(ArrayTest, IteratorEqual)
{
    HeapSimpleArray<int> a, a2;
    HeapSimpleArray<int>::Iterator i(&a), i2(&a2);

    EXPECT_EQ(true, a.SetSize(1000));

    a.SetAt(0, 111);
    a.SetAt(1, 222);

    EXPECT_EQ(true, i == i2) << "i[1] = i[1]";
    ++i;
    EXPECT_EQ(false, i == i2) << "i[1] = i[2]";
    ++i2;
    EXPECT_EQ(true, i == i2) << "i[2] = i[2]";
    i.Reset(&a);
    EXPECT_EQ(false, i == i2) << "After reset: i[1] = i[2]";
    i2.Reset(&a);
    EXPECT_EQ(true, i == i2) << "After reset: i[1] = i[1]";

    EXPECT_EQ(true, a2.SetSize(1000));

    i2.Reset(&a2);
    EXPECT_EQ(false, i == i2) << "Whether 2 iterators pointing to different objects but to the same index are equal";

}

// Testing the inequality '!=' operator which compares Iterator pointing.
// The result is true if both are pointing to different objects inside the Array 
TEST(ArrayTest, IteratorNotEqual)
{
    HeapSimpleArray<int> a, a2;
    HeapSimpleArray<int>::Iterator i(&a), i2(&a);

    EXPECT_EQ(true, a.SetSize(1000));

    a.SetAt(0, 111);
    a.SetAt(1, 222);

    EXPECT_EQ(false, i != i2) << "i[1] != i2[1]";
    ++(i);
    EXPECT_EQ(true, i != i2) << "ip[1] != ip[2]";
    ++(i2);
    EXPECT_EQ(false, i != i2) << "i[2] != i[2]";
    i.Reset(&a);
    EXPECT_EQ(true, i != i2) << "After reset: i[1] != i[2]";
    i2.Reset(&a);
    EXPECT_EQ(false, i != i2)  << "After reset: ip[1] != ip[1]";

    EXPECT_EQ(true, a2.SetSize(1000));

    i2.Reset(&a2);
    EXPECT_EQ(true, i != i2) << "Whether 2 iterators pointing to different objects but to the same index are unequal";

}

// Testing the GetContainer() function which should return the Array object to whom the Iterator is set to.
TEST(ArrayTest, IteratorGetContainer)
{
    HeapSimpleArray<int> a;
    HeapSimpleArray<int>::Iterator i(&a);

    EXPECT_EQ(i.GetContainer(), &a) << "Container of the Iterator must match function return value";

}

// Testing the GetIndex() function which should return the index of the object where the Iterator is 
// pointing to in the Array
TEST(ArrayTest, IteratorGetIndex)
{
    HeapSimpleArray<int> a;
    HeapSimpleArray<int>::Iterator i(&a);

    EXPECT_EQ(true, a.SetSize(1000)); 
    
    EXPECT_EQ(i.GetIndex(), 0) << "Checking initialization value";
    ++i;
    EXPECT_EQ(i.GetIndex(), 1) << "Traverse by one upward";
}

} } } } // namespace MyLib::Test::System::Container