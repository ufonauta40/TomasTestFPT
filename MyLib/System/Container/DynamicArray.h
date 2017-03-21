//#pragma once

#include "Array.h"

namespace MyLib {  namespace System {  namespace Container {

template<typename Element, typename Impl>
class DynamicArray : public Array<Element, Impl>
{
public:
    DynamicArray() : Array() {};

    bool InsertElement(Index ix, Element& value) { Impl::Insert(ix, value); }
    void RemoveAt(Index ix) { Impl::Delete(ix); }
};


template<typename Element, typename Allocator>
class DynamicArrayImpl : SimpleArrayImpl<Element, Allocator>
{
    DynamicArrayImpl() : SimpleArrayImpl() {};
    
    bool Insert(Index ix, Element& value);
    void Delete(Index ix);
    bool CopyRange(Array<Element, SimpleArrayImpl<Element, Allocator>>& fromArray, Index to, Index from, Index toFrom);
};

template<typename Element>
class HeapDynamicArray : public DynamicArray<Element, DynamicArrayImpl<Element, MyLib::System::Memory::HeapAllocator<Element> > > { };

} } } // namespace MyLib::System::Container