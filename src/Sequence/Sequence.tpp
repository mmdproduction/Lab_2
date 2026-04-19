
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
    return list->getSize();
}

template <typename T>
void SequenceList<T>::append(T value){
    return list->append(value);
}

template <typename T>
void SequenceList<T>::prepend(T value){
    return list->prepend(value);
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
    return array->append(value);
}

template <typename T>
void SequenceArray<T>::prepend(T value){
    return array->prepend(value);
}