
template<typename T>
ListSequence<T>::ListSequence() : list(new LinkedList<T>()) {}

template<typename T>
ListSequence<T>::ListSequence(T* item, int count) {
    list = new LinkedList<T>();
    for (int i = 0; i < count; ++i) {
        list->append(item[i]);
    }
}

template <typename T>
T ListSequence<T>::getFirst() const{
    return list->getFirst();
}

template <typename T>
T ListSequence<T>::getLast() const{
    return list->getLast();
}

template <typename T>
T ListSequence<T>::get(size_t index) const{
    return list->get(index);
}

template <typename T>
size_t ListSequence<T>::getLength() const{
    return list->getLength();
}

template <typename T>
void ListSequence<T>::append(T value){
    list->append(value);
}

template <typename T>
void ListSequence<T>::prepend(T value){
    list->prepend(value);
}

template<typename T>
ListSequence<T>* ListSequence<T>::getSubsequence(int startIndex, int endIndex){
    if (startIndex < 0 || endIndex >= list->getLength() || startIndex > endIndex) {
        throw std::out_of_range("Invalid subsequence range");
    }
    ListSequence<T>* result = new ListSequence<T>();
    for (int i = startIndex; i <= endIndex; ++i) {
        result->append(list->get(i));
    }
    return result;
}

template<typename T>
Sequence<T>* ListSequence<T>::concat(Sequence<T>& other) {

    ListSequence<T>* result = new ListSequence<T>();

    size_t currentSize = list->getLength();
    for (size_t i = 0; i < currentSize; ++i) {
        result->append(list->get(i));
    }

    size_t otherSize = other.getLength();
    for (size_t i = 0; i < otherSize; ++i) {
        result->append(other.get(i));
    }

    return result;
}


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

template<typename T>
ListSequence<T>::~ListSequence() { delete list; }


template<typename T>
Iterator<T> Sequence<T>::begin(){
    auto enumPtr = getEnumerator();
    return Iterator<T>(enumPtr);
}

template<typename T>
Iterator<T> Sequence<T>::end(){
    return Iterator<T>::endIterator();
}

template<typename T>
IEnumerator<T>* Sequence<T>::getEnumerator(){
    return new SequenceEnumerator<T>(this);
}

template<typename T>
T ListSequence<T>::operator[](int index){
    return (*list)[index];
}

template<typename T>
T ArraySequence<T>::operator[](int index){
    return (*array)[index];
}