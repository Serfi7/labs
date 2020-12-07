#pragma once

#include <iostream>
#include <string>

template<class TKey, class TValue>
class Pair {
private:
    TKey* key;
    TValue* value;

public:
    Pair(const Pair<TKey, TValue>& pair);
    Pair(const TKey& key, const TValue& value);
    Pair(const TKey& key);
    ~Pair();

    TKey Key() const {
        return *key;
    }
    TValue Value() const {
        return *value;
    }

    bool operator=(Pair& other) const;

    bool operator==(Pair& other) const;
    bool operator!=(Pair& other) const;

    bool operator<(Pair& other) const;
    bool operator>(Pair& other) const;

    friend std::ostream& operator<<(std::ostream &os, Pair &pair) {
        os <<
            "Key: " <<
            pair.Key() <<
            ", Value: " <<
            pair.Value();

        return os;
    }
};

template<class TKey, class TValue>
Pair<TKey, TValue>::Pair(const Pair<TKey, TValue>& pair) {
    this->key = new TKey(pair.Key());
    this->value = new TValue(pair.Value());
}

template<class TKey, class TValue>
Pair<TKey, TValue>::Pair(const TKey& key, const TValue& value) {
    this->key = new TKey(key);
    this->value = new TValue(value);
}

template<class TKey, class TValue>
Pair<TKey, TValue>::Pair(const TKey& key) {
    this->key = static_cast<TKey*>(operator new[](sizeof(TKey)));

    *this->key = key;
    this->value = nullptr;
}

template<class TKey, class TValue>
Pair<TKey, TValue>::~Pair() {
    delete key;
    delete value;
}

template<class TKey, class TValue>
bool Pair<TKey, TValue>::operator=(Pair& other) const  {
    return new Pair<TKey, TValue>(other);
}

template<class TKey, class TValue>
bool Pair<TKey, TValue>::operator==(Pair& other) const  {
    return *this->key == *other->key;
}

template<class TKey, class TValue>
bool Pair<TKey, TValue>::operator!=(Pair& other) const  {
    return !(*this == other);
}

template<class TKey, class TValue>
bool Pair<TKey, TValue>::operator<(Pair<TKey, TValue>& other) const  {
    return *this->key < *other.key;
}

template<class TKey, class TValue>
bool Pair<TKey, TValue>::operator>(Pair& other) const  {
    return *this->key > *other.key;
}

