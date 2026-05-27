#pragma once
#include"Exception.hpp"

template<typename T>
class DynamicArray{
    private:
    T* data;
    size_t size;

    public:

    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(const DynamicArray& other);
    DynamicArray(T* array, size_t count);
    DynamicArray(const std::initializer_list<T>& list);

    DynamicArray& operator=(const DynamicArray& other);

    ~DynamicArray();

    void set(size_t index, const T& value);

    T get(size_t index) const;
    T operator[](size_t index) const;
    size_t getSize() const;
    
    void resize(size_t newSize);
    void clear();


};

#include"DynamicArray.tpp"

