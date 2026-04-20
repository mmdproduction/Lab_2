
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
Sequence<T>* SequenceList<T>::concat(Sequence<T>& other) {

    SequenceList<T>* result = new SequenceList<T>();

    size_t currentSize = list->GetSize();
    for (size_t i = 0; i < currentSize; ++i) {
        result->append(list->Get(i));
    }

    size_t otherSize = other.getSize();
    for (size_t i = 0; i < otherSize; ++i) {
        result->append(other.get(i));
    }

    return result;
}


template<typename T>
SequenceArray<T>::SequenceArray() : array(new DynamicArray<T>()), capacity(0), size(0) {}

template<typename T>
SequenceArray<T>::SequenceArray(T* item, int count) : capacity(count), size(count) {
    array = new DynamicArray<T>(count);
    for (int i = 0; i < count; ++i) {
        array->set(i ,item[i]);
    }
}

template<typename T>
SequenceArray<T>::SequenceArray(const SequenceArray<T>& other) {
    array = new DynamicArray<T>(other.array);
    capacity = other.capacity;
    size = other.size;
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
    return size;
}

template <typename T>
void SequenceArray<T>::append(T value){
    if(capacity < size + 1){
        capacity *= 2;
        array->resize(capacity);
    }
    array->set(array->size, value);
    size++;
}

template <typename T>
void SequenceArray<T>::prepend(T value){
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
SequenceArray<T>* SequenceArray<T>::getSubsequence(int startIndex, int endIndex) override {
    if (startIndex < 0 || endIndex >= array->getSize() || startIndex > endIndex) {
        throw std::out_of_range("Invalid subsequence range");
    }
    SequenceArray<T>* result = new SequenceArray();
    for (int i = startIndex; i <= endIndex; ++i) {
        result->append(array->get(i));
    }
    return result;
}

template<typename T>
Sequence<T>* SequenceArray<T>::concat(Sequence<T>& other) {
    
    SequenceArray<T>* result = new SequenceArray<T>();

    
    for (size_t i = 0; i < array->size; ++i) {
        result->append(array->get(i));
    }

    
    size_t otherSize = other.getSize();
    for (size_t i = 0; i < otherSize; ++i) {
        result->append(other.get(i));
    }

    return result;
}


template<typename T>
SequenceArray<T>::~SequenceArray() { delete array; }

template<typename T>
SequenceList<T>::~SequenceList() { delete list; }


template<typename T>
Sequence<T>::begin(){
    auto enumPtr = getEnumerator();
    return Iterator<T>(enumPtr);
}

template<typename T>
Sequence<T>::end(){
    return Iterator(nullptr, true);
}

template<typename T>
Sequence<T>::getEnumerator(){
    return SequenceEnumerator(this);
}

template<typename T>
SequenceList<T>::operator[](int index){
    return *list[index];
}

template<typename T>
SequenceArray<T>::operator[](int index){
    return *array[index];
}