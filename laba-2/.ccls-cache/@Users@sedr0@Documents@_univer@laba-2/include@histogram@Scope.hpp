#pragma once

#include "string"

#include "../Exception.hpp"

template<class T>
class Scope {
private:
    T min;
    T max;


public:
    Scope() {}

    Scope (T value) {
        this->min = value;
        this->max = value;
    }

    Scope(T min, T max) {
        if (min > max) {
            throw Exception("Wrong scope");
        }

        this->min = min;
        this->max = max;
    }

    ~Scope() {}

    bool operator==(Scope<T> &other) {
        return min == other.min && max == other.max;
    }

    bool operator!=(Scope<T> &other) {
        return !(*this == other);
    }

    bool operator<(Scope<T> &other) {
        return min < other.min && other.max < max;
    }

    bool operator>(Scope<T> &other) {
        return min > other.min || other.max > min;
    }

    friend std::ostream& operator<<(std::ostream &os, Scope<T> &scope) {
        os <<
            scope.min;

        if (scope.min < scope.max) {
            os <<
                " - " <<
                scope.max;
        }

        return os;
    }
};
