#ifndef MYLIB_SYSTEM_CONTAINER_VECTOR
#define MYLIB_SYSTEM_CONTAINER_VECTOR


#include "common.h"
#include "Array.h"


namespace MyLib { namespace System { namespace Container {


template<typename Element, typename Impl>
class Vector : public Impl {
public:
    // Types

    typedef Vector<Element, Impl> VectorType;

    Vector(const VectorType& v) { Impl::CopyFrom(from); }
    Vector() {}
    
    VectorType& operator=(const VectorType &from) {
        if (static_cast<const VectorType*>(this) != static_cast<const VectorType*>(&from)) {
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

    bool UnshiftFront(const Element &value) { /* TODO */ }
    void ShiftFront() { /*TODO*/ }
    Element& GetFront() { /* TODO */ }
    const Element& GetFront() const { /* TODO */ }

    bool PushBack(const Element& value) { /* TODO */ }
    void PopBack() { /* TODO */ }
    Element& GetBack() { /* TODO */ }
    const Element& GetBack() const { /* TODO */ }

    bool InsertAfter(const ConstIterator& iterator, const Element &value) { /* TODO */ }
    bool RemoveAt(const ConstIterator& iterator) { /* TODO */ }


    // Iterators /////////////////////////////////////////////////////////////////////////////////////////////

    template<typename ArrayTypePtr, typename ElementType>
    class IteratorBase {
    public:
        IteratorBase(const ArrayTypePtr container, const Index ix) : m_container(container), m_ix(ix), m_size(container == NULL ? 0 : container->GetSize()) { }
        IteratorBase(const IteratorBase& from) : m_container(from.m_container), m_ix(from.m_ix), m_size(from.m_size) { }

        bool operator++() { return m_ix < m_size ? ++m_ix, true : false; }
        ElementType& operator*() const { return m_container->GetAt(m_ix); }

        bool operator==(const IteratorBase& right) const { return m_ix == right.GetIndex() && m_container == right.m_container; }

        template<typename Right>
        bool operator!=(const Right& right) const { return !(*this == right); }

        void Reset(ArrayTypePtr container, bool toEnd = false) {
            m_ix = toEnd ? container->GetSize() : 0;
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
        typedef IteratorBase<const ArrayType*, const Element> Base;
    public:
        Iterator() : Base(NULL, 0) { }
        Iterator(const Iterator& from) : Base(from.GetContainer(), from.GetIndex()) {}
    };

    class ConstIterator : public IteratorBase<const ArrayType*, const Element> {
        typedef IteratorBase<const ArrayType*, const Element> Base;
    public:
        ConstIterator() : Base(NULL, 0) { }
        ConstIterator(const Iterator& from) : Base(from.GetContainer(), from.GetIndex()) {}
    };

    // Iterators End ////////////////////////////////////////////////////////////////////////////////

    ConstIterator Begin() const {
        ConstIterator it;
        it.Reset(this);
        return it;
    }

    Iterator Begin() {
        Iterator it;
        it.Reset(this);
        return it;
    }

    ConstIterator End() const {
        ConstIterator it;
        it.Reset(this, true);
        return it;
    }

    Iterator End() {
        Iterator it;
        it.Reset(this, true);
        return it;
    }
};


template<typename Element, typename Allocator>
class SingleLinkedVectorImpl { };

template<typename Element, typename Allocator>
class GranulatedVectorImpl { 




};

template<typename Element>
class HeapSingleLinkedVector : public Vector<Element, SinlgeLinkedVectorImpl<Element, HeapAllocator<Element> > > { };

template<typename Element>
class GranulatedVector : public Vector<Element, GranulatedVectorImpl<Element, HeapAllocator<Element> > > { };


} } } // namespace MyLib::System::Container


#endif // defined MYLIB_SYSTEM_CONTAINER_VECTOR
