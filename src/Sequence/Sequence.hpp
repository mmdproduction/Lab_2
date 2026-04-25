#pragma once
#include<stdexcept>
#include <cstdint>
#include"../LinkedList/LinkedList.hpp"
#include"../DynamicArray/DynamicArray.hpp"
#include"../IEnumerator/Iterator.hpp"

template <typename T>
class Sequence: public IEnumerable<T>{
    public:
    virtual ~Sequence() = default;
    virtual T getFirst() const = 0;
    virtual T getLast() const = 0;
    virtual T get(size_t index) const = 0;
    virtual size_t getLength() const = 0;
    virtual void append(T value) = 0;
    virtual void prepend(T value) = 0;
    virtual Sequence<T>* getSubsequence(int startIndex, int endIndex) = 0;
    virtual Sequence<T>* concat(Sequence<T>& list) = 0;
    virtual T operator[](int index) = 0;

    Iterator<T> begin();
    Iterator<T> end();

    IEnumerator<T>* getEnumerator() override;

};




template<typename T>
class ArraySequence : public Sequence<T>{
    private:

    DynamicArray<T>* array;
    size_t capacity;
    size_t size;

    public:

    ArraySequence();
    ArraySequence(T* item, int count);
    ArraySequence(const ArraySequence<T>& other);
    ~ArraySequence();

    T getFirst() const override;
    T getLast() const override;
    T get(size_t index) const override;
    T operator[](int index) override;

    size_t getLength() const override;
    void append(T value) override;
    void prepend(T value) override;
    ArraySequence<T>* getSubsequence(int startIndex, int endIndex) override;
    Sequence<T>* concat(Sequence<T>& list) override;
};

template<typename T>
class ListSequence : public Sequence<T>{
    private:

    LinkedList<T>* list;

    public:

    ListSequence();
    ListSequence(T* item, int count);
    ListSequence(const ListSequence<T>& other);
    ~ListSequence();

    T getFirst() const override;
    T getLast() const override;
    T get(size_t index) const override;
    T operator[](int index) override;
    size_t getLength() const override;
    void append(T value) override;
    void prepend(T value) override;
    ListSequence<T>* getSubsequence(int startIndex, int endIndex) override;
    Sequence<T>* concat(Sequence<T>& list) override;
};

#include"Sequence.tpp"