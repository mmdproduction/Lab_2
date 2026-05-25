
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
T& ArraySequence<T>::operator[](int index){
    return (*array)[index];
}

template<typename T>
template<typename U>
std::unique_ptr<Sequence<U>> Sequence<T>::map(std::function<U(const T&)> mapper) const{
    return std::make_unique<MapSequenceView<U, T>>(*this, mapper);
}
template<typename T>
std::unique_ptr<Sequence<T>> Sequence<T>::where(std::function<bool(const T&)> filter) const{
    return std::make_unique<FilterSequenceView<T>>(*this, filter);
}

template<typename T>
std::unique_ptr<Sequence<T>> Sequence<T>::concat(Sequence<T>& other) const {
        return std::make_unique<ConcatSequenceView<T>>(*this, other);
    }

template<typename T>
std::unique_ptr<Sequence<T>> Sequence<T>::operator+(Sequence<T>& other) const {
        return std::make_unique<ConcatSequenceView<T>>(*this, other);
    }

template<typename T>
std::unique_ptr<Sequence<T>> Sequence<T>::getSubSequence(size_t startIndex, size_t endIndex) const {
        return std::make_unique<SubSequenceView<T>>(*this, startIndex, endIndex);
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