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
    LinkedList(T* items, int count);
    LinkedList(const LinkedList<T>& list);
    LinkedList(const std::initializer_list<T>& list);
    ~LinkedList();

    T& getFirst() const;
    T& getLast() const;
    T& get(int index) const;
    T& operator[](int index) const;
    LinkedList<T>& operator=(const LinkedList<T>& other);
    
    LinkedList<T>* getSubList(int startIndex, int endIndex);

    size_t getLength() const;

    void append(const T& item);
    void prepend(const T& item);

    void popAt(size_t index);

    void insertAt(const  T& item, int index);
    void set(T& item, size_t index);

    LinkedList<T>* concat(LinkedList<T>& list);

};

#include"LinkedList.tpp"