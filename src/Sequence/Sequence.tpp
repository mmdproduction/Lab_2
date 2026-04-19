
template<typename T>
SequenceList<T>::SequenceList() : list(new LinkedList<T>()) {}

template<typename T>
SequenceList<T>::SequenceList(T* item, int count) {
    list = new LinkedList<T>();
    for (int i = 0; i < count; ++i) {
        list->append(item[i]);
    }
}

template <typename T>
T SequenceList<T>::getFirst(){
    return list->getFirst();
}

template <typename T>
T SequenceList<T>::getLast(){
    return list->getLast();
}

template <typename T>
T SequenceList<T>::get(size_t index){
    return list->get(index);
}

template <typename T>
size_t SequenceList<T>::getSize(){
    return list->getLength();
}

template <typename T>
void SequenceList<T>::append(T value){
    list->append(value);
}

template <typename T>
void SequenceList<T>::prepend(T value){
    list->prepend(value);
}

template<typename T>
SequenceList<T>* SequenceList<T>::getSubsequence(int startIndex, int endIndex){
    if (startIndex < 0 || endIndex >= list->getLength() || startIndex > endIndex) {
        throw std::out_of_range("Invalid subsequence range");
    }
    SequenceList<T> result;
    for (int i = startIndex; i <= endIndex; ++i) {
        result.append(list->get(i));
    }
    return result;
}


template<typename T>
SequenceArray<T>::SequenceArray() : array(new DynamicArray<T>()), capacity(0) {}

template<typename T>
SequenceArray<T>::SequenceArray(T* item, int count) : capacity(count) {
    array = new DynamicArray<T>(count);
    for (int i = 0; i < count; ++i) {
        array->set(i ,item[i]);
    }
}

template<typename T>
SequenceArray<T>::SequenceArray(const SequenceArray<T>& other) {
    array = new DynamicArray<T>(*other.array);
    capacity = other.capacity;
}

template <typename T>
T SequenceArray<T>::getFirst(){
    return array->get(0);
}

template <typename T>
T SequenceArray<T>::getLast(){
    return array->get(array->getSize() - 1);
}

template <typename T>
T SequenceArray<T>::get(size_t index){
    return array->get(index);
}

template <typename T>
size_t SequenceArray<T>::getSize(){
    return array->getSize();
}

template <typename T>
void SequenceArray<T>::append(T value){
    if(capacity < array->size + 1){
        capacity *= 2;
        array->resize(capacity);
    }
    array->set(array->size, value);
    array->size++;
}

template <typename T>
void SequenceArray<T>::prepend(T value){
    if(capacity < array->size + 1){
        capacity *= 2;
        array->resize(capacity);
    }
    for(size_t i = size; i > 0; ++i){
        array->set(i, array->get(i - 1));
    }
    array->set(0, value);
}

template<typename T>
SequenceArray<T>* SequenceArray<T>::getSubsequence(int startIndex, int endIndex) override {
    if (startIndex < 0 || endIndex >= array->getSize() || startIndex > endIndex) {
        throw std::out_of_range("Invalid subsequence range");
    }
    SequenceArray<T> result = new SequenceArray();
    for (int i = startIndex; i <= endIndex; ++i) {
        result->append(array->get(i))
    }
    return result;
}



template<typename T>
SequenceArray<T>::~SequenceArray() { delete array; }

template<typename T>
SequenceArray<T>::~SequenceList() { delete list; }
