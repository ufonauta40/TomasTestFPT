
#ifndef MYLIB_ALLOCATOR
#define MYLIB_ALLOCATOR


#include "common.h"


namespace MyLib { namespace System { namespace Memory {



            template<typename Element>
            class HeapAllocator {
            public:
                static Element* Allocate(size_t count) {
                    return new Element[count];
                }

                static void Deallocate(Element* elements) {
                    delete[] elements;
                }

                static bool Reallocate(Element** elementsPtr, size_t oldCount, size_t newCount) {
                    Element* elements = Allocate(newCount);
                    if (elements != 0) {
                        const size_t countToCopy = newCount <= oldCount ? newCount : oldCount;
                        for (size_t ix = 0; ix < countToCopy; ++ix) {
                            elements[ix] = (*elementsPtr)[ix];
                        }
                        Deallocate(*elementsPtr);
                        *elementsPtr = elements;
                        return true;
                    }
                    return false;
                }
            };


}}} // namespace MyLib:System:Memory


#endif
