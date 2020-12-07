#pragma once

#include "iostream"

#include "../Sequence.hpp"
#include "../dictionary/Dictionary.hpp"

template<class TElement, class TSplitter>
class Histogram {
private:
    Sequence<TElement>* elements;
    Dictionary<TSplitter, int>* histogram;

public:
    Histogram(Sequence<TElement> &elements, Dictionary<TSplitter, int> &dict) {
        this->elements = new ArraySequence<TElement>(elements);
        this->histogram = new Dictionary<TSplitter, int>(dict);
    }

public:
    Dictionary<TSplitter, int> getDevision() {
        return this->histogram;
    }

    Sequence<TElement> getElements() {
        return this->elements;
    }

    std::string joinDevision(std::string separator = ", ") {
        return this->histogram->Join(separator);
    }
};

