#pragma once
#include"Exception.hpp"

template<typename T>
class DynamicArray{
    private:
    T* data;
    size_t size;

    public:

    DynamicArray();
    explicit DynamicArray(size_t size);
    explicit DynamicArray(const DynamicArray& other);
    explicit DynamicArray(T* array, size_t count);
    DynamicArray(const std::initializer_list<T>& list);

    DynamicArray& operator=(const DynamicArray& other);

    ~DynamicArray();

    void set(size_t index, T value);

    T get(size_t index);
    T operator[](size_t index);
    size_t getSize() const;
    
    void resize(size_t newSize);


};

#include"DynamicArray.tpp"

