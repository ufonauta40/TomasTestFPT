


using ArrayPtr = MyLib::System::Container::Array < int, MyLib::System::Container::SimpleArrayImpl < int, MyLib::System::Memory::HeapAllocator<int> > >;

namespace Test {

    ArrayPtr * ArrayInit(ArrayPtr *ap);
    ArrayPtr * ArrayDispose(ArrayPtr *ap); //???

    bool ArraySetSize(int size, ArrayPtr *ap);
    int  ArrayGetSize(ArrayPtr *ap);


    enum ACCESS_TYPE {
        BY_FUNC,
        LIKE_VECTOR
    };

    int ArrayGetValue(enum ACCESS_TYPE, int index, ArrayPtr *ap);
    void ArraySetValue(enum ACCESS_TYPE, int index, int value, ArrayPtr *ap);


    void ArrayAssign(ArrayPtr *ap1, ArrayPtr *ap2);

}
