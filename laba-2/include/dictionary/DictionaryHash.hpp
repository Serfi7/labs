#pragma once

#include <sstream>
#include <iostream>

#include "./IDictionary.hpp"
#include "./Pair.hpp"

#include "../Exception.hpp"

template<class TKey, class TValue>
class DictionaryHash : public IDictionary<TKey, TValue> {
private:
    struct Optional {
        Pair<TKey, TValue> pair;
        bool state;
        Optional(const Pair<TKey, TValue> pair)
            : pair(pair),
              state(true) {}
    };

    Optional** items;

    int capacity;
    int count;
    int countAll;

    int _getHash(TKey key, int capacity, int seed) const;
    int _getHash1(TKey key, int capacity) const;
    int _getHash2(TKey key, int capacity) const;

    void _rehash();

public:
    DictionaryHash(const int capacity);
    DictionaryHash(DictionaryHash<TKey, TValue> &dict);
    ~DictionaryHash();

    virtual int GetCount() const override;

    virtual TValue Get(const TKey& key) const override;
    virtual void Set(const TKey& key, const TValue& value) const override;
    virtual bool ContainsKey(const TKey& key) const override;
    virtual void Add(const TKey& key, const TValue& value) override;
    virtual void Remove(const TKey& key) override;
    virtual std::string Join(const std::string separator = ", ") const override;
};

template<class TKey, class TValue>
DictionaryHash<TKey, TValue>::DictionaryHash(const int capacity) {
    items = new Optional*[capacity];
    this->capacity = capacity;
    count = 0;
    countAll = 0;

    for (int i = 0; i < capacity; i++) {
        items[i] = nullptr;
    }
}

template<class TKey, class TValue>
DictionaryHash<TKey, TValue>::DictionaryHash(DictionaryHash<TKey, TValue>& dictionaryHash) {
    items = new Optional*[dictionaryHash.capacity];
    this->capacity = dictionaryHash.capacity;
    count = dictionaryHash.count;
    countAll = dictionaryHash.countAll;

    for (int i = 0; i < capacity; i++) {
        items[i] = new Optional(dictionaryHash.items[i]->pair);
    }
}

template<class TKey, class TValue>
int DictionaryHash<TKey, TValue>::_getHash(
        TKey key,
        int capacity,
        int seed
    ) const {
    int hashResult = 0;

    for (int i = 0; i != key.size(); i++) {
        //std::cout << i << " " << hashResult << std::endl;
        hashResult = (seed * hashResult + key[i]) % capacity;
    }

    hashResult = (hashResult * 2 + 1) % capacity;
    return hashResult;
}

template<class TKey, class TValue>
int DictionaryHash<TKey, TValue>::_getHash1(TKey key, int capacity) const {
    return _getHash(key, capacity, capacity - 1);
}

template<class TKey, class TValue>
int DictionaryHash<TKey, TValue>::_getHash2(TKey key, int capacity) const {
    return _getHash(key, capacity, capacity + 1);
}

template<class TKey, class TValue>
void DictionaryHash<TKey, TValue>::_rehash() {
    countAll = 0;
    count = 0;

    auto itemsNew = new Optional*[capacity];

    for (int i = 0; i < capacity; ++i) {
        itemsNew[i] = nullptr;
    }

    std::swap(items, itemsNew);

    for (int i = 0; i < this->capacity; ++i) {
        if (itemsNew[i] && itemsNew[i]->state) {
            auto item = itemsNew[i]->pair;

            Add(item.Key(), item.Value());
        }
    }
}

template<class TKey, class TValue>
int DictionaryHash<TKey, TValue>::GetCount() const {
    return count;
}

template<class TKey, class TValue>
TValue DictionaryHash<TKey, TValue>::Get(const TKey& key) const {
    int hash1 = _getHash1(key, this->capacity);
    int hash2 = _getHash2(key, this->capacity);
    int i = 0 ;

    while (items[hash1] != nullptr && i < capacity) {
        if (items[hash1]->state &&
            items[hash1]->pair.Key() == key
        ) {
            return items[hash1]->pair.Value();
        }

        hash1 = (hash1 + hash2) & this->capacity;
        ++i;
    }

    throw new Exception("No such key");
}

template<class TKey, class TValue>
void DictionaryHash<TKey, TValue>::Set(const TKey& key, const TValue& value) const {
    int hash1 = _getHash1(key, capacity);
    int hash2 = _getHash2(key, capacity);
    int i = 0;

    while (items[hash1] != nullptr && i < capacity) {
        if (items[hash1]->pair.Key() == key && items[hash1]->state) {
            items[hash1] = new Optional(Pair<TKey, TValue>(key, value));

            return;
        }

        hash1 = (hash1 + hash2) % capacity;
        ++i;
    }

    throw new Exception("No such key");
}

template<class TKey, class TValue>
bool DictionaryHash<TKey, TValue>::ContainsKey(const TKey& key) const {
    int hash1 = _getHash1(key, this->capacity);
    int hash2 = _getHash2(key, this->capacity);
    int i = 0 ;

    while (items[hash1] != nullptr && i < capacity) {
        if (items[hash1]->state &&
            items[hash1]->pair.Key() == key
        ) {
            return true;
        }

        hash1 = (hash1 + hash2) & this->capacity;
        ++i;
    }

    return false;
}

template<class TKey, class TValue>
void DictionaryHash<TKey, TValue>::Add(const TKey& key, const TValue& value) {
    if (countAll > 2 * count) {
        _rehash();
    }

    int hash1 = _getHash1(key, capacity);
    int hash2 = _getHash2(key, capacity);
    int i = 0;
    int firstDeleted = -1;

    while (items[hash1] && i < capacity) {
        if (ContainsKey(key)) {
            return;
        }

        if (!items[hash1]->state && firstDeleted == -1) {
            firstDeleted = hash1;
        }

        hash1 = (hash1 + hash2) % capacity;
        ++i;
    }

    if (firstDeleted == -1) {
        items[hash1] = new Optional(Pair<TKey, TValue>(key, value));
        this->countAll++;
    }
    else {
        items[firstDeleted]->pair = Pair<TKey, TValue>(key, value);
        items[firstDeleted]->state = true;
    }

    this->count++;
}

template<class TKey, class TValue>
void DictionaryHash<TKey, TValue>::Remove(const TKey& key) {
    int hash1 = _getHash1(key, capacity);
    int hash2 = _getHash2(key, capacity);
    int i = 0;

    while (items[hash1] != nullptr && i < capacity) {
        if (items[hash1]->pair.Key() == key && items[hash1]->state) {
            items[hash1]->state = false;
            this->count--;
            return;
        }

        hash1 = (hash1 + hash2) % capacity;
        ++i;
    }

    throw new Exception("No such key");
}

template<class TKey, class TValue>
std::string DictionaryHash<TKey, TValue>::Join(const std::string separator) const {
    std::stringstream out;

    for (int i = 0; i < capacity - 1; i++) {
        auto optional = items[i];

        if (optional && optional->state) {
            out << optional->pair << separator;
        }
    }

    auto lastOptional = items[capacity - 1];
    
    if (lastOptional && lastOptional->state) {
        out << lastOptional->pair;
    }

    return out.str();
}
