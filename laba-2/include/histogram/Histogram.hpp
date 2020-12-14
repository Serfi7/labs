#pragma once

#include "iostream"

#include "../Sequence.hpp"
#include "../dictionary/Dictionary.hpp"
#include "../dictionary/DictionaryHash.hpp"

template<class TElement, class TSplitter>
class Histogram {
private:
    Sequence<TElement>* elements;
    IDictionary<TSplitter, int>* histogram;

public:
    Histogram(Dictionary<TSplitter, int> &dict) {
        this->histogram = new Dictionary<TSplitter, int>(dict);
    }

    Histogram(DictionaryHash<TSplitter, int> &dict) {
        this->histogram = new DictionaryHash<TSplitter, int>(dict);
    }

public:
    Dictionary<TSplitter, int> getDevision() {
        return this->histogram;
    }

    std::string joinDevision(std::string separator = ", ") {
        return this->histogram->Join(separator);
    }
};

