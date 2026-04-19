

template<typename T>
DynamicArray<T>::DynamicArray() : data(nullptr), size(0) {}

template<typename T>
DynamicArray<T>::DynamicArray(size_t initial_size) : size(initial_size) {
    data = new T[size];
}


template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : size(other.size) {
    data = new T[size];
    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

template<typename T>
DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<typename T>
void DynamicArray<T>::set(size_t index, T value){
    if(index < 0 || index >= size){
        throw std::out_of_range("Index out of range");
    }
    data[index] = value;
}

template<typename T>
T& DynamicArray<T>::get(size_t index) {
    if (index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}



template<typename T>
T DynamicArray<T>::operator[](size_t index){
    return data[index];
}



template<typename T>
size_t DynamicArray<T>::getSize() const{
    return size;
}

template<typename T>
void DynamicArray<T>::resize(size_t newSize){
    if(newSize == size){
        return;
    }
    T* newData = new T[newSize];
    if(newSize > size){
        for(size_t i = 0; i < size; ++i){
            newData[i] = data[i];
        }
    }
    else{
        for(size_t i = 0; i < newSize; ++i){
            newData[i] = data[i];
        }
    }

    T* delData = data;
    data = newData;
    delete[] delData;
}