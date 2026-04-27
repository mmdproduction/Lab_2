
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
template<typename T>
Sequence<T>* Sequence<T>::where(std::function<bool(const T&)> filter) const{
    return new FilterSequenceView<T>(*this, filter);
}

template<typename T>
Sequence<T>* Sequence<T>::concat(Sequence<T>& other) const {
        return new ConcatSequenceView<T>(*this, other);
    }

template<typename T>
Sequence<T>* Sequence<T>::getSubSequence(size_t startIndex, size_t endIndex) const {
        return new SubSequenceView<T>(*this, startIndex, endIndex);
    }

template<typename T>
template<typename U, typename F>    
U Sequence<T>::reduce(F&& reducer, U initial) const{
    U result = initial;
    auto enumPtr = getEnumerator();
    while (enumPtr->moveNext()) {
        result = reducer(result, enumPtr->current());
    }
    delete enumPtr;
    return result;
}