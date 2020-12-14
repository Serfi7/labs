#pragma once

#include <string>

template<class TKey, class TValue>
class IDictionary
{
    public:
        virtual int GetCount() const = 0;

        virtual TValue Get(const TKey& key) const = 0;
        virtual void Set(const TKey& key, const TValue& value) const = 0;
        virtual bool ContainsKey(const TKey& key) const = 0;
        virtual void Add(const TKey& key, const TValue& value) = 0;
        virtual void Remove(const TKey& key) = 0;
        virtual std::string Join(const std::string separator = ", ") const = 0;
};

