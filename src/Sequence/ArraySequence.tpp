template<typename T>
ArraySequence<T>::ArraySequence() : array(new DynamicArray<T>()), capacity(0), size(0) {}

template<typename T>
ArraySequence<T>::ArraySequence(T* item, int count) : capacity(count), size(count) {
    array = new DynamicArray<T>(count);
    for (int i = 0; i < count; ++i) {
        array->set(i ,item[i]);
    }
}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) {
    array = new DynamicArray<T>(other.array);
    capacity = other.capacity;
    size = other.size;
}

template <typename T>
T ArraySequence<T>::getFirst() const{
    return array->get(0);
}

template <typename T>
T ArraySequence<T>::getLast() const{
    return array->get(array->getSize() - 1);
}

template <typename T>
T ArraySequence<T>::get(size_t index) const{
    return array->get(index);
}

template <typename T>
size_t ArraySequence<T>::getLength() const{
    return size;
}

template <typename T>
void ArraySequence<T>::append(T value){
    if(capacity < size + 1){
        capacity = (capacity == 0) ? 1 : capacity * 2;
        array->resize(capacity);
    }
    array->set(size, value);
    size++;
}

template <typename T>
void ArraySequence<T>::prepend(T value){
    if(capacity < size + 1){
        capacity *= 2;
        array->resize(capacity);
    }
    for(size_t i = size; i > 0; --i){
        array->set(i, array->get(i - 1));
    }
    array->set(0, value);
}

template<typename T>
ArraySequence<T>* ArraySequence<T>::getSubsequence(int startIndex, int endIndex){
    if (startIndex < 0 || endIndex >= array->getSize() || startIndex > endIndex) {
        throw std::out_of_range("Invalid subsequence range");
    }
    ArraySequence<T>* result = new ArraySequence();
    for (int i = startIndex; i <= endIndex; ++i) {
        result->append(array->get(i));
    }
    return result;
}

template<typename T>
Sequence<T>* ArraySequence<T>::concat(Sequence<T>& other) {
    
    ArraySequence<T>* result = new ArraySequence<T>();

    
    for (size_t i = 0; i < size; ++i) {
        result->append(array->get(i));
    }

    
    size_t otherSize = other.getLength();
    for (size_t i = 0; i < otherSize; ++i) {
        result->append(other.get(i));
    }

    return result;
}

template<typename T>
ArraySequence<T>::~ArraySequence() { delete array; }