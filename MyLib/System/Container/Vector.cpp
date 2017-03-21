#include "stdafx.h"

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
void GranulatedVectorImpl<Element, Allocator>::SetAt(Index ix, Element& value)
{
Index iPanel;    
    
    iPanel = FindPanel(ix);
    
    m_container[iPanel]->m_data[ix - m_container[iPanel]->first + 1] = value;
    
    return ex;
}

template <typename Element, typename Allocator>
Index GranulatedVectorImpl<Element, Allocator>::FindPanel(Index ix)
{
Index ixApproxPanel;
    // Find with help of approximation the appropriate element. At first, the proper panel has to be found.
    // Has to be checked for boundary values ?!? m_lastIndex = -1, 0 etc.
    
    ixApproxPanel = ix * m_lastPanel / m_lastIndex;
    
    while (ix > m_container[approxPanel].first)
        ixApproxPanel++;

    while (ix >  m_container[approxPanel+1].first)
        ixApproxPanel--;
    
    return ixApproxPanel;
}


template <typename Element, typename Allocator>
Index GranulatedVectorImpl<Element, Allocator>::FindElementIndexInPanel(Index ix, Index ixPanel = -1)
{
// Find with help of approximation the appropriate element. At first, the proper panel has to be found.
    
    if (ixPanel == -1) ixPanel = FindPanel(ix);
    
    return (ix - m_container[ixPanel]->first);
}


template <typename Element, typename Allocator>
Index GranulatedVectorImpl<Element, Allocator>::GetSize()
{
    return m_lastIndex + 1;
}

enum INSERTION {
    begin = 0,
    end = -1
};


template <typename Element, typename Allocator>
bool GranulatedVectorImpl<Element, Allocator>::InsertAfter(Index ix, Element& value)
{
Index iPanel;
Index iOccupied;
Index iElementInPanel;
GranulatedVectorImpl<int, MyLib::System::Memory::HeapAllocator<int>>::Panel *pp = NULL;

    iPanel = FindPanel(ix);
    if (iPanel > 0 && iPanel < m_container.GetSize()) iElementInPanel = FindElementIndexInPanel(iPanel);
    else return false;

    if (iElementInPanel < 0 || iElementInPanel >= m_granulation) return false;

    if (iPanel < m_container.GetSize() - 1)
        iOccupied = m_container[iPanel + 1]->first - m_container[iPanel]->first;
    else 
        iOccupied = m_lastIndex - m_container[iPanel]->first;

    if (iOccupied < 1 || iOccupied > m_granulation) return false;

    // Detect whether there is room on the panel
    if (iOccupied < m_granulation)
    {
        for (Index i = iElementInPanel; i > 0; i--)
            m_container[iPanel]->m_data[i] = m_container[iPanel]->m_data[i-1];
    }
    else {
         // If not, a new panel has to be created. The remnants (panel[i..max]) on the current panel 
         // will be placed on the new panel
         // while the new element will be stored on the current panel.
    
        pp = new Panel();
        pp->first = ix + 1;
        m_lastPanel++;

        for (Index i = iElementInPanel; iElementInPanel < m_granulation; i++) {
            pp->m_data[i - iElementInPanel] = m_container[iPanel]->m_data[i];
        }

        m_container.Insert(iPanel, pp); // Insertion has to be implemented. ?!?
    }

    m_container[iPanel]->m_data[iElement] = value; // Set the value

    // Set the first indices in each panel from next to current till the end
    // If a new panel is added, it should be skipped.
   for (Index i = iPanel + 1 + (pp != NULL ? 1 : 0); i < m_container.GetSize() - 1; i++)
        m_container[i]->first+= 1;


return true;
}

