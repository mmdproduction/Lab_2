#pragma once
#include<exception>

template<typename T>
class LinkedList{
    private:

    struct Node{
        T data;
        Node* next;
        Node(T value): data(value), next(nullptr) {}
    };

    size_t size;

    Node* head;
    Node* tail;

    public:

    LinkedList();
    LinkedList(T* items, int count);
    LinkedList(const LinkedList<T>& list);

    T getFirst();
    T getLast();
    T get(int index);

    LinkedList<T>* getSubList(int startIndex, int endIndex);

    size_t getLength();

    void append(T item);
    void prepend(T item);

    void insertAt(T item, int index);

    LinkedList<T>* concat(LinkedList<T>& list);

};

#include"LinkedList.tpp"