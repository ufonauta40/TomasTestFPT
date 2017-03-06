#include "stdafx.h"
#include "gtest.h"

#include "Vector.h"

namespace MyLib { namespace Test { namespace System { namespace Container {


using namespace MyLib::System::Container;

typedef GranulatedVector<int>::ConstIterator GranVectorCIter;
typedef GranulatedVector<int>::Iterator GranVectorIter;


//Test Vector class construction
TEST(VectorTest, Creation)
{
    GranulatedVector<int> v;
    EXPECT_EQ(v.GetSize(), 0);
}

//While Inserting and deleting elements check the size of the Vector
TEST(VectorTest, Size)
{
    GranulatedVector<int> v;
    GranVectorCIter cIter(static_cast<GranVectorCIter>(v.Begin()));

    EXPECT_EQ(true, v.PushBack(10));
    EXPECT_EQ(1, v.GetSize());

    for (int i=0; i < 5000; i++)
    EXPECT_EQ(true, v.PushBack(111));

    for (int i=0; i < 5000; i++)
    EXPECT_EQ(true, v.UnShiftFront(111));


    EXPECT_EQ(10001, v.GetSize()) << "Should be 10001 elements stored";

    ++cIter;

    v.InsertAfter(cIter, 100);

    ++cIter;

    v.InsertAfter(cIter, 100);
    v.InsertAfter(cIter, 100);
    v.InsertAfter(cIter, 100);
    v.InsertAfter(cIter, 100);
    v.InsertAfter(cIter, 100);

    EXPECT_EQ(10007, v.GetSize()) << "Should be 10007 elements stored";

    v.PopBack();

    EXPECT_EQ(10006, v.GetSize()) << "Should be 10006 elements stored";

    for (int i=0; i<100; i++)
        v.PopBack();

    EXPECT_EQ(9906, v.GetSize()) << "Should be 9906 elements stored";

    for (int i = 0; i<1000; i++)
        v.RemoveAt(v.End());

    EXPECT_EQ(8906, v.GetSize()) << "Should be 8906 elements stored";

    EXPECT_EQ(v.UnShiftFront(111), true) << "Add a value to the vector front";
    EXPECT_EQ(v.UnShiftFront(111), true) << "Add a value to the vector front";
    EXPECT_EQ(v.UnShiftFront(111), true) << "Add a value to the vector front";

    EXPECT_EQ(8909, v.GetSize()) << "Should be 8906 elements stored";


    for (int i = 0; i<8909; i++)
        v.ShiftFront();

    EXPECT_EQ(0, v.GetSize()) << "Should be an empty vector";
}

//Try to access elements of the Vector by function or with parentheses
TEST(VectorTest, ElementAccess)
{
    GranulatedVector<int> v;
    
    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(v.PushBack(0), true);
        EXPECT_EQ(v.UnShiftFront(0), true);
    }

    v.SetAt(0, 111);
    EXPECT_EQ(111, v.GetAt(0));
    EXPECT_EQ(111, v[0]);

    v.SetAt(0, -5);
    EXPECT_EQ(-5, v.GetAt(0));
    EXPECT_EQ(-5, v[0]);

    v[0] = -5;
    EXPECT_EQ(-5, v.GetAt(0));
    EXPECT_EQ(-5, v[0]);
    EXPECT_EQ(v.GetAt(0), v.GetFront());

    v[1] = -6;

    v.ShiftFront();
    EXPECT_EQ(-6, v.GetFront());

    v.SetAt(500, 111);
    EXPECT_EQ(111, v.GetAt(500));
    EXPECT_EQ(111, v[500]);

    v[500] = 20;
    EXPECT_EQ(20, v.GetAt(500));
    EXPECT_EQ(20, v[500]);

    v.SetAt(40, 500);
    EXPECT_EQ(500, v.GetAt(40));

    v[41] = 501;
    EXPECT_EQ(500, v.GetAt(40));
    EXPECT_EQ(501, v.GetAt(41));
    v[42] = 502;
    EXPECT_EQ(502, v.GetAt(42));
}


//Assign the whole Vector to another variable
TEST(VectorTest, Assignment)
{
    GranulatedVector<int> v1, v2;

    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(v1.PushBack(0), true);
        EXPECT_EQ(v2.PushBack(0), true);
        EXPECT_EQ(v1.UnShiftFront(0), true);
        EXPECT_EQ(v2.UnShiftFront(0), true);
    }

    v1.SetAt(0, -5);
    v1.SetAt(111, -5);
    v1.SetAt(222, -5);

    v1 = v1;
    EXPECT_EQ(&v1, &v1);

    v2 = v1;
    EXPECT_NE(&v1, &v2);

    EXPECT_EQ(v1.GetAt(0), v2.GetAt(0));
    EXPECT_EQ(v1.GetAt(0), -5);

    EXPECT_EQ(v1.GetAt(111), v2.GetAt(111));
    EXPECT_EQ(v1.GetAt(111), -5);

    EXPECT_EQ(v1.GetAt(222), v2.GetAt(222));
    EXPECT_EQ(v2.GetAt(222), -5);
}

//////////////////////////////////////////////////////////////////////////////////
///// Iterator testing
//////////////////////////////////////////////////////////////////////////////////


typedef GranulatedVector<int>::Iterator GranVecIntIter;
typedef GranulatedVector<int>::ConstIterator GranVecIntCIter;


//Test Iterator class construction
TEST(VectorTest, IteratorInit)
{
    GranulatedVector<int> v;
    GranVecIntIter i;
    GranVecIntIter i2(v.Begin());
    GranVecIntCIter i3(v.Begin());

    //    GranulatedVector<int>::Iterator i3(v); -> Error, should not compile anymore

    EXPECT_EQ(i2, v.End());
    EXPECT_EQ(i2, v.Begin());

    EXPECT_EQ(i3, static_cast<GranVecIntCIter>(v.Begin()));
    EXPECT_EQ(i3, static_cast<GranVecIntCIter>(v.End()));

}


// Call the Reset() function which should initialize the Iterator to the parameter 
// Vector class and set iteration pointer to first or last item.
TEST(VectorTest, IteratorReset)
{
    GranulatedVector<int> v1, v2;
    GranVecIntIter i;
    GranVecIntCIter ci;

    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(v1.PushBack(0), true);
        EXPECT_EQ(v1.UnShiftFront(0), true);
    }

    i.Reset(&v1);
    ci.Reset(&v1);

    v1.SetAt(0, 111);
    v1.SetAt(1, 112);
    ++i;
    ++ci;

    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(v2.PushBack(0), true);
        EXPECT_EQ(v2.UnShiftFront(0), true);
    }

    v2.SetAt(0, 222);

    i.Reset(&v2);
    ci.Reset(&v2);

    EXPECT_EQ(*i, v2.GetAt(0));
    EXPECT_EQ(*ci, v2.GetAt(0));
}

// Test the ++operator which provides forward traversing through the Vector
TEST(VectorTest, IteratorAdvance)
{
    GranulatedVector<int> v;
    GranVecIntIter i;
    GranVecIntCIter ci;

    for (int i = 0; i < 1000; i++) {
        EXPECT_EQ(v.PushBack(0), true);
        EXPECT_EQ(v.UnShiftFront(0), true);
    }

    i.Reset(&v);
    ci.Reset(&v);

    v.SetAt(0, 111);
    v.SetAt(1, 222);

    EXPECT_EQ(111, *i);
    EXPECT_EQ(111, *ci);

    ++i;
    ++ci;

    EXPECT_EQ(222, *i) << "Advance iterator by one and check value";
    EXPECT_EQ(222, *ci) << "Advance constant iterator by one and check value";
}

// Test the bounds of the Vector by traversing through it with an Iterator
// Also test value assigning with an Iterator (*i = ..)
TEST(VectorTest, IteratorVectorBoundTest)
{
    GranulatedVector<int> v;
    GranVecIntIter i;
    GranVecIntCIter ci;
    int c = 0;

    for (int i = 0; i < 1000; i++){
        EXPECT_EQ(v.PushBack(0), true);
        EXPECT_EQ(v.UnShiftFront(0), true);
    }

    i.Reset(&v);
    ci.Reset(&v);

    while (i != v.End()) {
        *i = c;
        c++;
        ++i;
    }

    c = 0;

    while (ci != static_cast<GranVecIntCIter> (v.End())) {
        EXPECT_EQ(*ci, c);
        ++ci;
        c++;
    }
}






}}}}