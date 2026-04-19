#pragma once
#include<exception>

template<typename T>
class DynamicArray{
    private:
    T* data;
    size_t size;

    public:

    DynamicArray();
    explicit DynamicArray(size_t size);
    DynamicArray(const DynamicArray& other);

    DynamicArray& operator=(const DynamicArray& other);

    ~DynamicArray();

    void set(size_t index, T value);

    T get(size_t index);
    T operator[](size_t index);
    size_t getSize() const;
    
    void resize(size_t newSize);


};

#include"DynamicArray.tpp"

