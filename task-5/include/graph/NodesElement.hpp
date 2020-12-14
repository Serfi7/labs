#pragma once

template<class TArc>
class NodesElement {
private:
    int from;
    int to;
    TArc weight;

public:
    NodesElement(int from, int to, TArc weight)
        : from(from),
          to(to),
          weight(weight)
    {}

    int From() {
        return from;
    }

    int To() {
        return to;
    }

    TArc Weight() {
        return weight;
    }
};

