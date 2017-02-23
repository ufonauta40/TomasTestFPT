#ifndef MYLIB_SYSTEM_CONTAINER_ARRAY
#define MYLIB_SYSTEM_CONTAINER_ARRAY


#include "common.h"
#include "../Memory/Allocator.h"


namespace MyLib { namespace System { namespace Container {


template<typename Element, typename Impl>
class Array : public Impl {
public:
    // Types

    typedef Array<Element, Impl> ArrayType;

    // Interface

    Array() {}
    Array(const ArrayType &from) { Impl::CopyFrom(from); }

    ArrayType& operator=(const ArrayType &from) {
        if (static_cast<const ArrayType*>(this) != static_cast<const ArrayType*>(&from)) {
            Impl::CopyFrom(from);
        }
        return *this;
    }

    Element& GetAt(Index ix) { return Impl::GetAt(ix); }
    const Element& GetAt(Index ix) const { return Impl::GetAt(ix); }

    void SetAt(Index ix, const Element &value) { Impl::SetAt(ix, value); }

    Element& operator[](Index ix) { return Impl::GetAt(ix); }
    const Element& operator[](Index ix) const { return Impl::GetAt(ix); }    

    Index GetSize() const { return Impl::GetSize(); }

    bool SetSize(Index newSize) {
        if (newSize != GetSize()) {
            return Impl::SetSize(newSize);
        }
        return true;
    }

    // Iterators

    template<typename ArrayTypePtr, typename ElementType>
    class IteratorBase {
    public:
        IteratorBase(ArrayTypePtr container, Index ix) : m_container(container), m_ix(ix), m_size(container->GetSize()) { }
        IteratorBase(const IteratorBase& from) : m_container(from.m_container), m_ix(from.m_ix), m_size(from.m_size) { }

        bool operator++() { return m_ix < m_size ? ++m_ix, true : false; }
        ElementType& operator*() const { return m_container->GetAt(m_ix); }

//////////////////////////////////////////////////////////////
 //       template<typename Right>
 //       bool operator==(const Right& right) const { return m_ix == right.GetIndex(); } 
//
// 1. Compile Error - "GetIndex() member not found"
// 2. Functionality wrong - Should also check if it is referencing the same Array object

        bool operator==(const IteratorBase& right) const { return m_ix == right.GetIndex(); }

//////////////////////////////////////////////////////////////

		template<typename Right>
        bool operator!=(const Right& right) const { return !(*this == right); }

        void Reset(ArrayTypePtr container) {
            m_ix = 0;
            m_size = container->GetSize(); 
            m_container = container;
        }

        const ArrayType* GetContainer() const { return m_container; }

        Index GetIndex() const { return m_ix; }

    private:
        IteratorBase& operator=(const IteratorBase &from) { return *this; } // copying iterators not allowed

    protected:
        ArrayTypePtr m_container;
        Index m_ix;
        Index m_size;
    };

    class Iterator : public IteratorBase<ArrayType*, Element> {
        typedef IteratorBase<ArrayType*, Element> Base;
    public:
        Iterator(ArrayType* container, Index ix = 0) : Base(container, ix) { }
    };

    class ConstIterator : public IteratorBase<const ArrayType*, const Element> {
        typedef IteratorBase<const ArrayType*, const Element> Base;
    public:
        ConstIterator(const ArrayType* container, Index ix = 0) : Base(container, ix) { }
        ConstIterator(const Iterator& from) : Base(from.GetContainer(), from.GetIndex()) {}
    };

    ConstIterator Begin() const { return ConstIterator(this); }
    Iterator Begin() { return Iterator(this); }

    ConstIterator End() const { return ConstIterator(this, GetSize()); }
    Iterator End() { return Iterator(this, GetSize()); }
};


template<typename Element, typename Allocator>
class SimpleArrayImpl {
public:
    // Interface
 
    SimpleArrayImpl() : m_contents(0), m_size(0) {}

    bool CopyFrom(const SimpleArrayImpl &from) {
        if (m_size != from.m_size) {
            Element* contents = Allocator::Allocate(m_size);
            if (contents == 0) {
                return false;
            }
            Allocator::Deallocate(m_contents);
            m_contents = contents;
            m_size = from.m_size;
        }
        for (Index ix = 0; ix < m_size; ix++) {
            m_contents[ix] = from.m_contents[ix];
        }
        return true;
    }

    Element& GetAt(Index ix) { return m_contents[ix]; }
    const Element& GetAt(Index ix) const { return m_contents[ix]; }

    void SetAt(Index ix, const Element &value) {
        m_contents[ix] = value;
    }

    Index GetSize() const { return m_size; }

    bool SetSize(Index newSize) {
        if (Allocator::Reallocate(&m_contents, m_size, /*=>*/newSize)) {
            m_size = newSize;
            return true;
        }
        return false;
    }

private:
    // Attributes
    Element* m_contents;
    Index m_size;
};


template<typename Element>
class HeapSimpleArray : public Array<Element, SimpleArrayImpl<Element, MyLib::System::Memory::HeapAllocator<Element> > > { };


} } } // namespace MyLib::System::Container


#endif // defined MYLIB_SYSTEM_CONTAINER_ARRAY
