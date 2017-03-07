#include "Vector.h"

using namespace MyLib::System::Container;

template <typename Element, typename Allocator>
Element& GranulatedVectorImpl<Element, Allocator>::GetAt(Index ix)
{
Index iPanel;

    iPanel = FindPanel(ix);
        
    return m_container[iPanel]->m_data[ix - m_container[iPanel]->first + 1];
}

template <typename Element, typename Allocator>
void GranulatedVectorImpl<Element, Allocator>::SetAt(Index ix, Element value)
{
Index iPanel;    
    
    iPanel = FindPanel(ix);
    
    m_container[iPanel]->m_data[ix - m_container[iPanel]->first + 1] = value;
        
    return ex;
}

template <typename Element, typename Allocator>
void GranulatedVectorImpl<Element, Allocator>::FindPanel(Index ix)
{
    // Find with help of approximation the appropriate element. At first the proper panel has to be found.
}

template <typename Element, typename Allocator>
Index GranulatedVectorImpl<Element, Allocator>::GetSize()
{
    return m_lastIndex + 1;
}

template <typename Element, typename Allocator>
Index GranulatedVectorImpl<Element, Allocator>::InsertAt(Index ix, Element value)
{
Index s;

    switch (ix) {
        case 0: size = m_container.GetSize();
            if (m_lastItem - m_container[size - 1]->first < m_granulation) m_container[size - 1]->SetAt(ix, value);
            else {
                    AddPanel(-1);
                    m_container[s]->SetAt(ix, value);
                 }
        case -1: if (m_lastItem)

        default: 
    };
}

