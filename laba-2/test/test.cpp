#include "./array/DynamicArray.test.hpp"

#include "./array/ArraySequence.test.hpp"

#include "./Sorter.hpp"

//#include "./BinaryTreeSearch.test.hpp"

#include "./Dictionary.test.hpp"

int main () {
    // std::cout << "Testing DynamicArray<T>" << std::endl;
    // new DynamicArrayTest();
    // std::cout << std::endl;

    // std::cout << "Testing ArraySequence<T>" << std::endl;
    // new ArraySequenceTest();
    // std::cout << std::endl;

    // std::cout << "Testing Sorter<T>" << std::endl;
    // new SorterTest();

    //std::cout << "Testing BinarySearchTree<T>" << std::endl;
    //new BinarySearchTreeTest();

    std::cout << "Testing Dictionary<TKey, TValue>" << std::endl;
    new DictionaryTest();

    return 0;
};
