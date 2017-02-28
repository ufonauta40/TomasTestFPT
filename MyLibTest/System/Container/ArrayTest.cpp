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

    a2 = a1; 
    EXPECT_NE(&a1, &a2);
    
    EXPECT_EQ(a1.GetAt(0), a1.GetAt(0));
    EXPECT_EQ(a1.GetAt(0), -5);

    EXPECT_EQ(a1.GetAt(111), a2.GetAt(111));
    EXPECT_EQ(a1.GetAt(111), -5);

    EXPECT_EQ(a1.GetAt(222), a2.GetAt(222));
    EXPECT_EQ(a2.GetAt(222), -5);
}


//////////////////////////////////////////////////////////////////////////////////
///// Iterator testing
//////////////////////////////////////////////////////////////////////////////////


typedef HeapSimpleArray<int>::Iterator HeapIntIter;
typedef HeapSimpleArray<int>::ConstIterator HeapIntCIter;


//Test Iterator class construction
TEST(ArrayTest, IteratorInit)
{
    HeapSimpleArray<int> a;
    HeapIntIter i;
    HeapIntIter i2(a.Begin());
    HeapIntCIter i3(a.Begin());


//    HeapSimpleArray<int>::Iterator i3(a); -> Error, should not compile anymore

    EXPECT_EQ(i2, a.End());
    EXPECT_EQ(i2, a.Begin());

    EXPECT_EQ(i3, static_cast<HeapIntCIter>(a.Begin()));
    EXPECT_EQ(i3, static_cast<HeapIntCIter>(a.End()));

}

// Call the Reset() function which should initialize the Iterator to the parameter 
// Array class and set iteration pointer to first or last item.
TEST(ArrayTest, IteratorReset)
{
    HeapSimpleArray<int> a1, a2;
    HeapIntIter i;
    HeapIntCIter ci;

    a1.SetSize(1000);

    i.Reset(&a1);
    ci.Reset(&a1);

    a1.SetAt(0, 111);
    a1.SetAt(1, 112);
    ++i;
    ++ci;    
    
    a2.SetSize(1000);

    a2.SetAt(0, 222);
    
    i.Reset(&a2); 
    ci.Reset(&a2);

    EXPECT_EQ(*i, a2.GetAt(0));
    EXPECT_EQ(*ci, a2.GetAt(0));
}

// Test the ++operator which provides forward traversing through the Array
TEST(ArrayTest, IteratorAdvance)
{
    HeapSimpleArray<int> a;
    HeapIntIter i;
    HeapIntCIter ci;

    EXPECT_EQ(true, a.SetSize(1000));

    i.Reset(&a);
    ci.Reset(&a);

    a.SetAt(0, 111);
    a.SetAt(1, 222);

    EXPECT_EQ(111, *i);
    EXPECT_EQ(111, *ci);

    ++i; 
    ++ci;

    EXPECT_EQ(222, *i) << "Advance iterator by one and check value";
    EXPECT_EQ(222, *ci) << "Advance constant iterator by one and check value";
}

// Test the bounds of the Array by traversing through it with an Iterator
// Also test value assigning with an Iterator (*i = ..)
TEST(ArrayTest, IteratorArrayBoundTest)
{
    HeapSimpleArray<int> a;
    HeapIntIter i;
    HeapIntCIter ci;
    int c = 0;

    EXPECT_EQ(true, a.SetSize(1000));

    i.Reset(&a);
    ci.Reset(&a);

    while (i != a.End()) { 
        *i = c;
        c++;
        ++i;
    }

    c = 0;
    
    while (ci != static_cast<HeapIntCIter> (a.End())) {
        EXPECT_EQ(*ci, c);
        ++ci;
        c++;
    }
}



// Testing the equality '==' operator which compares Iterator pointing.
// The result is true if both are pointing to the same object inside the Array
TEST(ArrayTest, IteratorEqual)
{
    HeapSimpleArray<int> a, a2;
    HeapIntIter i, i2;
    HeapIntCIter ci, ci2;

    EXPECT_EQ(true, a.SetSize(1000));
    
    i.Reset(&a); i2.Reset(&a);
    ci.Reset(&a); ci2.Reset(&a);

    a.SetAt(0, 111);
    a.SetAt(1, 222);

    EXPECT_EQ(true, i == i2) << "i[1] = i2[1]";
    EXPECT_EQ(true, ci == ci2) << "constant i[1] = constant i2[1]";
    EXPECT_EQ(true, ci == static_cast<HeapIntCIter>(i)) << "i[1] = constant i[1]";

    ++i;
    ++ci;
   
    EXPECT_NE(true, i == i2) << "i[1] = i[2]";
    EXPECT_NE(true, ci == ci2) << "constant i[1] = constant i[2]";
    EXPECT_NE(true, ci == static_cast<HeapIntCIter>(i2)) << "i[1] = constant i[2]";

    ++i2;
    ++ci2;

    EXPECT_EQ(true, i == i2) << "i[2] = i[2]";
    EXPECT_EQ(true, ci == ci2) << "constant i[2] = constant i[2]";
    EXPECT_EQ(true, static_cast<HeapIntCIter>(i) == ci2) << "i[2] = constant i[2]";

    i.Reset(&a);
    ci.Reset(&a);

    EXPECT_NE(true, i == i2) << "After reset: i[1] = i[2]";
    EXPECT_NE(true, ci == ci2) << "After reset: constant i[1] = constant i[2]";

    i2.Reset(&a);
    ci2.Reset(&a);

    EXPECT_EQ(true, i == i2) << "After reset: i[1] = i[1]";
    EXPECT_EQ(true, ci == ci2) << "After reset: constant i[1] = constant i[1]";
    EXPECT_EQ(true, static_cast<HeapIntCIter>(i) == ci2) << "i[1] = constant i[1]";

    EXPECT_EQ(true, a2.SetSize(1000));
    a2.SetAt(0, a.GetAt(0));

    i2.Reset(&a2);
    ci2.Reset(&a2);

    EXPECT_NE(true, i == i2) << "Two iterators pointing to different objects but to the same index";
    EXPECT_NE(true, ci == ci2) << "Two constant iterators pointing to different objects but to the same index";

}

// Testing the inequality '!=' operator which compares Iterator pointing.
// The result is true if both are pointing to different objects inside the Array 
TEST(ArrayTest, IteratorNotEqual)
{
    HeapSimpleArray<int> a, a2;
    HeapIntIter i, i2;
    HeapIntCIter ci, ci2;

    EXPECT_EQ(true, a.SetSize(1000));

    i.Reset(&a); i2.Reset(&a);
    ci.Reset(&a); ci2.Reset(&a);

    a.SetAt(0, 111);
    a.SetAt(1, 222);

    EXPECT_EQ(false, i != i2) << "i[1] != i2[1]";
    EXPECT_EQ(false, ci != ci2) << "constant i[1] != constant i2[1]";
    EXPECT_EQ(false, ci != static_cast<HeapIntCIter>(i)) << "i[1] = constant i[1]";

    ++i;
    ++ci;    

    EXPECT_EQ(true, i != i2) << "i[1] != i2[2]";
    EXPECT_EQ(true, ci != ci2) << "constant i[1] != constant i2[2]";
    EXPECT_EQ(true, ci2 != static_cast<HeapIntCIter>(i)) << "i[2] = constant i[i]";


    ++i2;
    ++ci2;

    EXPECT_EQ(false, i != i2) << "i[2] != i2[2]";
    EXPECT_EQ(false, ci != ci2) << "constant i[1] != constant i2[2]";
    EXPECT_EQ(false, ci2 != static_cast<HeapIntCIter>(i)) << "constant i[2] != i[i]";

    i.Reset(&a);
    ci.Reset(&a);

    EXPECT_EQ(true, i != i2) << "After reset: i[1] != i2[2]";
    EXPECT_EQ(true, ci != ci2) << "After reset: constant i[1] != constant i2[2]";


    i2.Reset(&a);
    ci2.Reset(&a);

    EXPECT_EQ(false, i != i2)  << "After reset: i[1] != i2[1]";
    EXPECT_EQ(false, ci != ci2) << "After reset: constant i[1] != constant i2[1]";
    EXPECT_EQ(false, ci2 != static_cast<HeapIntCIter>(i)) << "constant i[2] != i[i]";


    EXPECT_EQ(true, a2.SetSize(1000));
    a2.SetAt(0, a.GetAt(0));

    i2.Reset(&a2);
    ci2.Reset(&a2);

    EXPECT_EQ(true, i != i2) << "Two iterators pointing to different objects but to the same index";
    EXPECT_EQ(true, ci != ci2) << "Two constant iterators pointing to different objects but to the same index";

}

// Testing the GetContainer() function which should return the Array object to whom the Iterator is set to.
TEST(ArrayTest, IteratorGetContainer)
{
    HeapSimpleArray<int> a;
    HeapIntIter i(a.Begin());
    HeapIntCIter ci(a.Begin());

    EXPECT_EQ(i.GetContainer(), &a) << "Container of the Iterator must match function return value";
    EXPECT_EQ(ci.GetContainer(), &a) << "Container of the Iterator must match function return value";

}

// Testing the GetIndex() function which should return the index of the object where the Iterator is 
// pointing to in the Array
TEST(ArrayTest, IteratorGetIndex)
{
    HeapSimpleArray<int> a;
    HeapIntIter i;
    HeapIntCIter ci;

    EXPECT_EQ(true, a.SetSize(1000)); 

    i.Reset(&a);
    ci.Reset(&a);

    EXPECT_EQ(i.GetIndex(), 0) << "Checking initialization value";
    EXPECT_EQ(ci.GetIndex(), 0) << "Checking initialization value";

    ++i;
    ++ci;

    EXPECT_EQ(i.GetIndex(), 1) << "Traverse by one upward";
    EXPECT_EQ(ci.GetIndex(), 1) << "Traverse by one upward";

}

} } } } // namespace MyLib::Test::System::Container