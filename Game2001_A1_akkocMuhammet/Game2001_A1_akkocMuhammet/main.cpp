#include <iostream>
#include "Array.hpp"
#include "OrderedArray.hpp"
#include "UnorderedArray.hpp"

template<typename A>
void Print(const char* name, const A& a) {
    std::cout << name << " [size=" << a.Size() << ", cap=" << a.Capacity() << "]: ";
    for (size_t i = 0; i < a.Size(); ++i) std::cout << a[i] << " ";
    std::cout << "\n";
}

int main() {
    UnorderedArray<int> ua;
    for (int i = 0; i < 10; ++i) ua.Push(i % 4);
    Print("Unordered", ua);

    OrderedArray<int> oaNoDup(false);         
    int nums[] = { 7,3,9,3,5,1,5,2 };
    for (int v : nums) oaNoDup.Push(v);
    Print("OrderedNoDup", oaNoDup);

    OrderedArray<int> oaDup(true);           
    for (int v : nums) oaDup.Push(v);
    Print("OrderedDup", oaDup);

    OrderedArray<int> grow(false);
    for (int i = 0; i < 20; ++i) { grow.Push(i); if (i == 0 || i == 1 || i == 3 || i == 7 || i == 15) std::cout << "cap=" << grow.Capacity() << "\n"; }
    return 0;
}
