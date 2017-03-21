#ifndef MYLIB_SYSTEM_CONTAINER_VECTOR
#define MYLIB_SYSTEM_CONTAINER_VECTOR


#include "common.h"
#include "DynamicArray.h"
#include "../Memory/Allocator.h"



namespace MyLib { namespace System { namespace Container {


template<typename Element, typename Impl>
class Vector : public Impl {
public:
    // Types

    typedef Vector<Element, Impl> VectorType;

    Vector(const VectorType& from) { Impl::CopyFrom(from); }
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

    bool UnShiftFront(const Element &value) {return Impl::InsertAfter(0, value); }
    void ShiftFront() { Impl::RemoveAt(0); }
    Element& GetFront() { return Impl::GetAt(0); }
    const Element& GetFront() const { return Impl::GetAt(0); }

    bool PushBack(const Element& value) { return Impl::InsertAfter(GetSize() > 0 ? GetSize() - 1 : 0, value); }
    void PopBack() { Impl::RemoveAt(GetSize() > 0 ? GetSize() - 1 : 0); }
    Element& GetBack() { return Impl::GetAt(GetSize() > 0 ? GetSize() - 1 : 0); }
    const Element& GetBack() const { return Impl::GetAt(GetSize() > 0 ? GetSize() - 1 : 0); }


    // Iterators /////////////////////////////////////////////////////////////////////////////////////////////

    template<typename VectorTypePtr, typename ElementType>
    class IteratorBase {
    public:
        IteratorBase(const VectorTypePtr container, const Index ix) : m_container(container), m_ix(ix), m_size(container == NULL ? 0 : container->GetSize()) { }
        IteratorBase(const IteratorBase& from) : m_container(from.m_container), m_ix(from.m_ix), m_size(from.m_size) { }

        bool operator++() { return m_ix < m_size ? ++m_ix, true : false; }
        ElementType& operator*() const { return m_container->GetAt(m_ix); }

        bool operator==(const IteratorBase& right) const { return m_ix == right.GetIndex() && m_container == right.m_container; }

        template<typename Right>
        bool operator!=(const Right& right) const { return !(*this == right); }

        void Reset(VectorTypePtr container, bool toEnd = false) {
            m_ix = toEnd ? container->GetSize() : 0;
            m_size = container->GetSize();
            m_container = container;
        }

        const VectorType* GetContainer() const { return m_container; }

        Index GetIndex() const { return m_ix; }

    private:
        IteratorBase& operator=(const IteratorBase &from) { return *this; } // copying iterators not allowed

    protected:
        VectorTypePtr m_container;
        Index m_ix;
        Index m_size;
    };


    class Iterator : public IteratorBase<VectorType*, Element> {
        typedef IteratorBase<const VectorType*, const Element> Base;
    public:
        Iterator() : Base(NULL, 0) { }
        Iterator(const Iterator& from) : Base(from.GetContainer(), from.GetIndex()) {}
    };

    class ConstIterator : public IteratorBase<const VectorType*, const Element> {
        typedef IteratorBase<const VectorType*, const Element> Base;
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

    bool InsertAfter(const ConstIterator& iterator, const Element &value) {return Impl::InsertAfter(iterator.GetIndex(), value); }
    bool RemoveAt(const ConstIterator& iterator) { Impl::RemoveAt(iterator.GetIndex()); }

};


template<typename Element, typename Allocator>
class SingleLinkedVectorImpl { };


/* The GranulatedVectorImpl algorithm works the following way: 
 
The whole Vector is cut into Panels of the length of granulation.
The first element on every panel knows where he is in the Vector.
If an element is accessed, the appropriate panel has to be found first. This is done by the following 
approximation formula:  

       last panel index 
       ----------------------   * ix
       last element index                     

After the approximation the search continues panel by panel (forward or backward) until the proper one is found.
If a new element is inserted the proper panel has to be found first as described above. If there is room on the panel 
the element is inserted and the other elements are shifted properly. If not, a new panel is created and inserted beyond 
the one where the new elements index points to. The new element is inserted on the panel which was there before the 
insertion and all the elements from beyond are moved to the new panel. The deletion of a element is the inverse 
operation to insertion.

*/

template<typename Element, typename Allocator>
class GranulatedVectorImpl {

public:
   
    class Panel {
        HeapSimpleArray <Element> m_data;
        Index first;
    };
   
    GranulatedVectorImpl() : m_lastPanel(0), m_lastIndex(0), m_granulation(10) {}

    Element& GetAt(Index ix); // done
    void SetAt(Index ix, Element& value); // done

    Index GetSize(); // done

    bool InsertAfter(Index ix, Element& value); //done
   
private:

    HeapDynamicArray < Panel* > m_container;
    Index m_lastIndex;
    Index m_lastPanel;
    Index m_granulation;

    Index FindPanel(Index ix);
    Index FindElementIndexInPanel(Index ix, Index ixPanel);

};

template<typename Element>
class HeapSingleLinkedVector : public Vector<Element, SingleLinkedVectorImpl<Element, MyLib::System::Memory::HeapAllocator<Element> > > { };

template<typename Element>
class GranulatedVector : public Vector<Element, GranulatedVectorImpl<Element, MyLib::System::Memory::HeapAllocator<Element> > > { };


} } } // namespace MyLib::System::Container


#endif // defined MYLIB_SYSTEM_CONTAINER_VECTOR


