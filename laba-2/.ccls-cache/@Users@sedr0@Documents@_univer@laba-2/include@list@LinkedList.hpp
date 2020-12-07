#pragma once

#include "../Exception.hpp"
#include "Node.hpp"

template<class T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList(T* items, const int size) {
        if (size < 1) {
            throw new Exception;
        }

        Node<T>* current = new Node<T>(items[0]);
        this->head = current;

        for (int i = 1; i < size; i++) {
            Node<T>* el = new Node<T>(items[i]);
            current->next = el;
            current = el;
        }

        this->tail = current;
    }

    LinkedList() {
        this->head = NULL;
        this->tail = NULL;
    }

    LinkedList(const LinkedList<T> &list) {
        if (!list.head) {
            this->head = NULL;
            this->tail = NULL;
        }

        Node<T>* sourceNode = list.head;
        Node<T>* current = new Node<T>(*sourceNode->value);
        this->head = current;

        sourceNode = sourceNode->next;
        while (sourceNode) {
            Node<T>* el = new Node<T>(*sourceNode->value);
            current->next = el;
            current = current->next;

            sourceNode = sourceNode->next;
        }

        this->tail = current;
    }

public:
    void SetHead(Node<T>* head) {
        this->head = head;
    }

    void SetTail(Node<T>* tail) {
        this->tail = tail;
    }

    Node<T>* Head() const {
        return head;
    }

    Node<T>* Tail() const {
        return tail;
    }

    T GetFirst() const {
        if (!head) {
            throw new Exception;
        }

        return *this->head->value;
    }

    T GetLast() const {
        if (!tail) {
            throw new Exception;
        }

        return *this->tail->value;
    }

    T Get(int index) {
        int current_idx = 0;

        Node<T>* current = this->head;
        while (current) {
            if (index == current_idx) {
                return *current->value;
            }

            current = current->next;
            current_idx++;
        }

        throw new Exception;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) {
        int length = this->GetLength();
        if (startIndex > endIndex
            || startIndex < 0
            || startIndex >= length
            || endIndex > length) {
            throw new Exception;
        }

        Node<T>* current = this->head;
        int current_idx = 0;
        while (current && current_idx != startIndex) {
            current = current->next;
            current_idx++;
        }

        LinkedList<T>* subList = new LinkedList<T>();

        while (current_idx < endIndex) {
            subList->Append(*current->value);
            current = current->next;

            current_idx++;
        }

        return subList;
    }

    int GetLength() {
        int length = 0;

        Node<T>* current = this->head;
        while (current) {
            length++;

            current = current->next;
        }

        return length;
    }

public:
    void Prepend(T item) {
        Node<T>* node = new Node<T>(item);

        if (!head) {
            this->head = node;
            this->tail = node;

            return;
        }

        node->next = this->head;
        this->head = node;
    }

    void Append(T item) {
        Node<T>* node = new Node<T>(item);

        if (!head) {
            this->head = node;
            this->tail = node;

            return;
        }

        this->tail->next = node;
        this->tail = node;
    }

    void InsertAt(T item, int index) {
        if (index < 0) {
            throw new Exception;
        }

        if (index == 0) {
            this->Prepend(item);

            return;
        }

        int prev_idx = 0;
        Node<T>* prevNode = this->head;
        while (prevNode && prev_idx != index - 1) {
            prevNode = prevNode->next;
            prev_idx++;
        }

        if (!prevNode) {
            throw new Exception;
        }

        if (!prevNode->next) {
            this->Append(item);
            return;
        }

        Node<T>* newNode = new Node<T>(item);
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }

    void Set(T item, int index) {
        if (index < 0) {
            throw new Exception;
        }

        if (!head) {
            throw new Exception;
        }

        if (index == 0) {
            Node<T>* newNode = new Node<T>(item);
            newNode->next = this->head->next;
            this->head = newNode;

            return;
        }

        int prev_idx = 0;
        Node<T>* prevNode = this->head;
        while (prevNode && prev_idx != index - 1) {
            prevNode = prevNode->next;
            prev_idx++;
        }

        if (!prevNode) {
            throw new Exception;
        }

        if (!prevNode->next) {
            this->Append(item);
            return;
        }

        Node<T>* newNode = new Node<T>(item);

        if (!prevNode->next->next) {
            prevNode->next = newNode;
            this->tail = newNode;
        }

        newNode->next = prevNode->next->next;
        prevNode->next = newNode;
    }

    void RemoveAt(const int index) {
        if (!head) {
            throw new Exception;
        }

        if (index == 0) {
            this->head = this->head->next;

            if (!head) {
                this->tail = this->head;
            }

            return;
        }

        int prev_idx = 0;
        Node<T>* prevNode = this->head;

        while (prevNode && prev_idx != index - 1) {
            prevNode = prevNode->next;
            prev_idx++;
        }

        if (!prevNode || !prevNode->next) {
            throw new Exception;
        }

        if (prevNode->next != this->tail) {
            prevNode->next = prevNode->next->next;

            return;
        }

        prevNode->next = NULL;
        this->tail = prevNode;
    }

    void Remove(T value) {
        if (!head) {
            return;
        }

        if (*this->head->value == value) {
            if (this->head->next) {
                this->head = this->head->next;

                return;
            }

            this->head = this->tail = NULL;
            return;
        }

        Node<T>* prevNode = this->head;

        while (prevNode->next) {
            if (*prevNode->next->value != value) {
                prevNode = prevNode->next;

                continue;
            }

            if (prevNode->next == this->tail) {
                prevNode->next = NULL;
                this->tail = prevNode;

                return;
            }

            prevNode->next = prevNode->next->next;
            prevNode = prevNode->next;
            return;
        }
    }

    void RemoveAll(T value) {
        if (!head) {
            return;
        }

        Node<T>* prevNode = this->head;

        while (prevNode->next) {
            if (*prevNode->next->value != value) {
                prevNode = prevNode->next;

                continue;
            }

            if (prevNode->next == this->tail) {
                prevNode->next = NULL;
                this->tail = prevNode;

                break;
            }

            prevNode->next = prevNode->next->next;
            prevNode = prevNode->next;
        }

        if (*this->head->value == value) {
            if (this->head->next) {
                this->head = this->head->next;

                return;
            }

            this->head = this->tail = NULL;
        }
    }

    LinkedList<T>* Concat(LinkedList<T> *list) {
        LinkedList<T>* concatedList = new LinkedList<T>(*this);

        Node<T>* current = list->head;
        while (current) {
            concatedList->Append(*current->value);
            current = current->next;
        }

        return concatedList;
    }
};
