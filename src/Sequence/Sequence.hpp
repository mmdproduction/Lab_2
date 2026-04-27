#pragma once
#include<stdexcept>
#include <cstdint>
#include <functional>
#include"LinkedList.hpp"
#include"DynamicArray.hpp"
#include"Iterator.hpp"


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
    Sequence<T>* getSubSequence(size_t startIndex, size_t endIndex) const;
    virtual T operator[](int index) = 0;

    template<typename U>
    Sequence<U>* map(std::function<U(const T&)> mapper) const;
    Sequence<T>* where(std::function<bool(const T&)> filter) const;
    Sequence<T>* concat(Sequence<T>& list) const;

    template<typename U, typename F>
    U reduce(F&& reducer, U initial) const;
    //TODO map-reduce

    Iterator<T> begin();
    Iterator<T> end();

    IEnumerator<T>* getEnumerator() const override;

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
    ArraySequence(const std::initializer_list<T>& list);
    ~ArraySequence();

    T getFirst() const override;
    T getLast() const override;
    T get(size_t index) const override;
    T operator[](int index) override;

    size_t getLength() const override;
    void append(T value) override;
    void prepend(T value) override;
};

template<typename T>
class ListSequence : public Sequence<T>{
    private:

    LinkedList<T>* list;

    public:

    ListSequence();
    ListSequence(T* item, int count);
    ListSequence(const ListSequence<T>& other);
    ListSequence(const std::initializer_list<T>& list);
    ~ListSequence();

    T getFirst() const override;
    T getLast() const override;
    T get(size_t index) const override;
    T operator[](int index) override;
    size_t getLength() const override;
    void append(T value) override;
    void prepend(T value) override;
};
#include"SequenceView.hpp"

#include"Sequence.tpp"
#include"ListSequence.tpp"
#include"ArraySequence.tpp"