#ifndef MYLIB_SYSTEM_CONTAINER_VECTOR
#define MYLIB_SYSTEM_CONTAINER_VECTOR


#include "MyLib/System/Container/common.h"
#include "MyLib/System/Container/Array.h"


namespace MyLib { namespace System { namespace Container {


template<typename Element, typename Impl>
class Vector : public Impl {
public:
    bool UnshiftFront(const Element &value) { /* TODO */ }
    void ShiftFront() { /*TODO*/ }
    Element& GetFront() { /* TODO */ }
    const Element& GetFront() const { /* TODO */ }

    bool PushBack(const Element& value) { /* TODO */ }
    void PopBack() { /* TODO */ }
    Element& GetBack() { /* TODO */ }
    const Element& GetBack() const { /* TODO */ }

    bool InsertAfter(const ConstIterator& iterator, const Element &value) { /* TODO */ }
    bool RemoveAfter(const ConstIterator& iterator) { /* TODO */ }

    // Iterators

    class Iterator { /* TODO */ };
    class ConstIterator { /* TODO */ };
};


template<typename Element, typename Allocator>
class SinlgeLinkedVectorImpl { /* TODO */ };


template<typename Element>
class HeapSinlgeLinkedVector : public Vector<Element, SinlgeLinkedVectorImpl<Element, HeapAllocator<Element> > > { };


} } } // namespace MyLib::System::Container


#endif // defined MYLIB_SYSTEM_CONTAINER_VECTOR
