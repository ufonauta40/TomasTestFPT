#include "stdafx.h"

#include "DynamicArray.h"

using namespace MyLib::System::Container;

template<typename Element, typename Allocator>
bool DynamicArrayImpl<Element, Allocator>::Insert(Index ix, Element& value)
{
Array a_temp(this);

    if (!SetSize(GetSize() + 1))  return false;
    if (!CopyRange(pA, 0, 0, ix))  return false;
    SetVal(ix, value);
    if (!CopyRange(pA, ix + 1, ix, GetSize() - ix)) return false;

return true;
}

template<typename Element, typename Allocator>
void DynamicArrayImpl<Element, Allocator>::Delete(Index ix)
{
Array a_temp(this);

    if (!SetSize(GetSize() - 1)) return false;
    if (!CopyRange(a_temp, 0, 0, ix)) return false;
    if (!CopyRange(a_temp, ix + 1, ix, GetSize() - ix)) return false;

   return true;
}

template<typename Element, typename Allocator>
bool DynamicArrayImpl<Element, Allocator>::CopyRange(Array<Element, SimpleArrayImpl<Element, Allocator>>& fromArray, Index to, Index from, Index toFrom)
{
    for (Index i = from, Index j = to; i < toFrom; i++, j++)
        m_container[j] = fromArray[i];
    
return true;
}