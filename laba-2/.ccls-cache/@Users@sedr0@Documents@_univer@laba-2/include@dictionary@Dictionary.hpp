#pragma once

#include <iostream>
#include <functional>

#include "./IDictionary.hpp"
#include "./Pair.hpp"

#include "../binary-search-tree/BinarySearchTree.hpp"

template<class TKey, class TValue>
class Dictionary : public IDictionary<TKey, TValue> {
public:
    BinarySearchTree<Pair<TKey, TValue>>* data;

public:
    Dictionary();
    Dictionary(Dictionary<TKey, TValue> &dict);
    ~Dictionary();

    virtual int GetCount() const override;

    virtual TValue Get(const TKey& key) const override;
    virtual void Set(const TKey& key, const TValue& value) const override;
    virtual bool ContainsKey(const TKey& key) const override;
    virtual void Add(const TKey& key, const TValue& value) const override;
    virtual void Remove(const TKey& key) const override;
    virtual std::string Join(const std::string separator = ", ") const override;
};

template<class TKey, class TValue>
Dictionary<TKey, TValue>::Dictionary() {
    data = new BinarySearchTree<Pair<TKey, TValue>>();
}

template<class TKey, class TValue>
Dictionary<TKey, TValue>::Dictionary(Dictionary<TKey, TValue> &dict) {
    data = new BinarySearchTree<Pair<TKey, TValue>>(*dict.data);
}

template<class TKey, class TValue>
Dictionary<TKey, TValue>::~Dictionary() {
    delete data;
}

template<class TKey, class TValue>
int Dictionary<TKey, TValue>::GetCount() const {
    return data->GetCount();
}

template<class TKey, class TValue>
TValue Dictionary<TKey, TValue>::Get(const TKey& key) const {
    auto emptyValue = TValue();
    auto newPair = Pair<TKey, TValue>(key, emptyValue);

    auto foundPair = data->Get(newPair);

    return foundPair.Value();
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::Set(const TKey& key, const TValue& newValue) const {
    auto newPair = Pair<TKey, TValue>(key, newValue);

    data->Set(newPair);
}

template<class TKey, class TValue>
bool Dictionary<TKey, TValue>::ContainsKey(const TKey& key) const {
    auto newPair = Pair<TKey, TValue>(key);

    return data->Contains(newPair);
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::Add(const TKey& key, const TValue& value) const{
    auto newPair = Pair<TKey, TValue>(key, value);

    if (ContainsKey(key)) {
        throw new Exception("This key is existing in dictionary");
    }

    data->Add(newPair);
}

template<class TKey, class TValue>
void Dictionary<TKey, TValue>::Remove(const TKey& key) const {
    auto emptyValue = TValue();
    auto newPair = Pair<TKey, TValue>(key, emptyValue);

    data->Remove(newPair);
}

template<class TKey, class TValue>
std::string Dictionary<TKey, TValue>::Join(const std::string separator) const {
    return data->Join(separator);
}
