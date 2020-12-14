#pragma once

#include "iostream"

#include "./Histogram.hpp"
#include "../Sequence.hpp"
#include "../dictionary/Dictionary.hpp"
#include "../dictionary/DictionaryHash.hpp"

template<class TElement, class TSplitter>
class HistogramBuilder {
public:
    HistogramBuilder() {}
    ~HistogramBuilder() {}

    Histogram<TElement, TSplitter>* HashDictionaryFromSequence(
            Sequence<TElement>* elements,
            Sequence<TSplitter>* range,
            std::function<TSplitter (const TElement&)> splitter
        ) {
        auto dict = new DictionaryHash<TSplitter, int>(range->GetLength());

        int rangeLength = range->GetLength();
        for (int i = 0; i < rangeLength; i++) {
            auto rangeElement = range->Get(i);


            dict->Add(rangeElement, 0);
        }

        int sequenceLength = elements->GetLength();
        for (int i = 0; i < sequenceLength; i++) {
            auto element = elements->Get(i);

            auto splitterValue = splitter(element);

            if (dict->ContainsKey(splitterValue)) {
                dict->Set(splitterValue, dict->Get(splitterValue) + 1);
            }
        }

        return new Histogram<TElement, TSplitter>(*dict);
    }

    Histogram<TElement, TSplitter>* FromSequence(
            Sequence<TElement>* elements,
            Sequence<TSplitter>* range,
            std::function<TSplitter (const TElement&)> splitter
        ) {
        auto dict = new Dictionary<TSplitter, int>();

        int rangeLength = range->GetLength();
        for (int i = 0; i < rangeLength; i++) {
            auto rangeElement = range->Get(i);

            dict->Add(rangeElement, 0);
        }

        int sequenceLength = elements->GetLength();
        for (int i = 0; i < sequenceLength; i++) {
            auto element = elements->Get(i);

            auto splitterValue = splitter(element);

            if (dict->ContainsKey(splitterValue)) {
                dict->Set(splitterValue, dict->Get(splitterValue) + 1);
            }
        }

        return new Histogram<TElement, TSplitter>(*dict);
    }
};

