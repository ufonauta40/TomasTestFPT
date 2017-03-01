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

    for (int i=0; i < 10000; i++)
    EXPECT_EQ(true, v.PushBack(111));

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

    EXPECT_EQ(v.UnshiftFront(111), true) << "Add a value to the vector front";
    EXPECT_EQ(v.UnshiftFront(111), true) << "Add a value to the vector front";
    EXPECT_EQ(v.UnshiftFront(111), true) << "Add a value to the vector front";

    EXPECT_EQ(8909, v.GetSize()) << "Should be 8906 elements stored";


    for (int i = 0; i<8909; i++)
        v.ShiftFront();

    EXPECT_EQ(0, v.GetSize()) << "Should be an empty vector";
}

//Try to access elements of the Vector by function or with parentheses
TEST(ArrayTest, ElementAccess)
{
    GranulatedVector<int> v;
    
    for (int i=0; i < 1000; i++)
        v.PushBack(0);

    v.SetAt(0, 111);
    EXPECT_EQ(111, v.GetAt(0));
    EXPECT_EQ(111, v[0]);

    v.SetAt(0, -5);
    EXPECT_EQ(-5, v.GetAt(0));
    EXPECT_EQ(-5, v[0]);

    v[0] = -5;
    EXPECT_EQ(-5, v.GetAt(0));
    EXPECT_EQ(-5, v[0]);

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



}}}}