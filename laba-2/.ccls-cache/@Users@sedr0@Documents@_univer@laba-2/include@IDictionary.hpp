#pragma once

template<class TKey, class TValue>
class IDictionary
{
    public:
        virtual int GetCount() const = 0;
        virtual int GetCapacity() const = 0;

        TValue Get(const TKey& key) const = 0;
        bool ContainsKey(const TKey& key) const = 0;
        void Add(const TKey& key, const TValue& value) const = 0;
        void Remove(const TKey& key) const = 0;
};

