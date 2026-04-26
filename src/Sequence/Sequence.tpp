
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
IEnumerator<T>* Sequence<T>::getEnumerator() const{
    return new SequenceEnumerator<T>(this);
}

template<typename T>
T ArraySequence<T>::operator[](int index){
    return (*array)[index];
}

template<typename T>
template<typename U>
Sequence<U>* Sequence<T>::map(std::function<U(const T&)> mapper) const{
    return new MapSequenceView<U, T>(*this, mapper);
}