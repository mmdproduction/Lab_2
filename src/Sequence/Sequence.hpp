#pragma once
#include"../LinkedList/LinkedList.hpp"
#include"../DynamicArray/DynamicArray.hpp"
#include"../IEnumerator/Iterator.hpp"

template <typename T>
class Sequence: public IEnumerable<T>{
    public:
    virtual ~Sequence() = default;
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(size_t index) = 0;
    virtual size_t getSize() = 0;
    virtual void append(T value) = 0;
    virtual void prepend(T value) = 0;
    virtual Sequence<T>* getSubsequence(int startIndex, int endIndex) = 0;
    virtual Sequence<T>* concat(Sequence<T>& list) = 0;
    virtual T operator[](int index) = 0;

    Iterator<T>* begin();
    Iterator<T>* end();

    IEnumerator<T> getEnumerator() override;

};


template<typename T>
class SequenceArray : public Sequence<T>{
    private:

    DynamicArray<T>* array;
    size_t capacity;
    size_t size;

    public:

    SequenceArray();
    SequenceArray(T* item, int count);
    SequenceArray(const SequenceArray<T>& other);
    ~SequenceArray();

    T getFirst() override;
    T getLast() override;
    T get(size_t index) override;
    T operator[](int index) override;

    size_t getSize() override;
    void append(T value) override;
    void prepend(T value) override;
    SequenceArray<T>* getSubsequence(int startIndex, int endIndex) override;
    Sequence<T>* concat(Sequence<T>& list) override;
};

template<typename T>
class SequenceList : public Sequence<T>{
    private:

    LinkedList<T>* list;

    public:

    SequenceList();
    SequenceList(T* item, int count);
    SequenceList(const SequenceList<T>& other);
    ~SequenceList();

    T getFirst() override;
    T getLast() override;
    T get(size_t index) override;
    T operator[](int index) override;
    size_t getSize() override;
    void append(T value) override;
    void prepend(T value) override;
    SequenceList<T>* getSubsequence(int startIndex, int endIndex) override;
    Sequence<T>* concat(Sequence<T>& list) override;
};

#include"Sequence.tpp"