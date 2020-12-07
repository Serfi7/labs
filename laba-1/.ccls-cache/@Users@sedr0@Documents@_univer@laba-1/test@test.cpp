#include "./list/LinkedList.test.hpp"
#include "./array/DynamicArray.test.hpp"

#include "./list/LinkedListSequence.test.hpp"
#include "./array/ArraySequence.test.hpp"

#include "./Sorter.hpp"

int main () {
    // std::cout << "Testing LinkedList<T>" << std::endl;
    // new LinkedListTest();
    // std::cout << std::endl;

    // std::cout << "Testing DynamicArray<T>" << std::endl;
    // new DynamicArrayTest();
    // std::cout << std::endl;

    // std::cout << "Testing LinkedListSequence<T>" << std::endl;
    // new LinkedListSequenceTest();
    // std::cout << std::endl;

    // std::cout << "Testing ArraySequence<T>" << std::endl;
    // new ArraySequenceTest();
    // std::cout << std::endl;

    std::cout << "Testing Sorter<T>" << std::endl;
    new SorterTest();

    return 0;
};
