#pragma once
#include"Exception.hpp"
#include<iostream>

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
    explicit LinkedList(T* items, int count);
    explicit LinkedList(const LinkedList<T>& list);
    explicit LinkedList(const std::initializer_list<T>& list);
    ~LinkedList();

    T getFirst();
    T getLast();
    T get(int index);
    T operator[](int index);

    LinkedList<T>* getSubList(int startIndex, int endIndex);

    size_t getLength();

    void append(T item);
    void prepend(T item);

    void insertAt(T item, int index);

    LinkedList<T>* concat(LinkedList<T>& list);

};

#include"LinkedList.tpp"