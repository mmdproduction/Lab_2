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
    array = new DynamicArray<T>(*(other.array));
    capacity = other.capacity;
    size = other.size;
}
template<typename T>
ArraySequence<T>::ArraySequence(const std::initializer_list<T>& list): capacity(list.size()), size(list.size()) {
    array = new DynamicArray<T>(list);
}

template <typename T>
T ArraySequence<T>::getFirst() const{
    return array->get(0);
}

template <typename T>
T ArraySequence<T>::getLast() const{
    return array->get(size - 1);
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
    if(capacity <= size){
        capacity = (capacity == 0) ? 1 : capacity * 2;
        array->resize(capacity);
    }
    for(size_t i = size; i > 0; --i){
        array->set(i, array->get(i - 1));
    }
    array->set(0, value);
    size++;
}

template<typename T>
ArraySequence<T>::~ArraySequence() { delete array; }