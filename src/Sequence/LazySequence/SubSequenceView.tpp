template<typename T>
SubSequenceView<T>::SubSequenceView(const Sequence<T>& src, size_t sIndex, size_t eIndex): source(src), startIndex(sIndex), endIndex(eIndex){}

template<typename T>
IEnumerator<T>* SubSequenceView<T>::getEnumerator() const{
    return new SkipEnumerator(source.getEnumerator(), startIndex, endIndex - startIndex + 1);
}

template<typename T>
T SubSequenceView<T>::getFirst() const{
    auto enumPtr = getEnumerator();
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<T>::endIterator();
        if (iterator == end) {
            delete enumPtr;
            throw EmptySequence();
        }
        T result = *iterator;
        delete enumPtr;
        return result;
}

template<typename T>
T SubSequenceView<T>::getLast() const{
        T result;
        
        auto enumPtr = getEnumerator();
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<T>::endIterator();

        if (iterator == end) throw EmptySequence();

        while(++iterator != end){
            result = *iterator;
        }
        
        delete enumPtr;
        return result;
}


template<typename T>
T SubSequenceView<T>::get(size_t index) const {
    auto enumPtr = new IndexEnumerator<T>(getEnumerator(), index);
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<T>::endIterator();

        if (iterator == end) {
            delete enumPtr;
            throw IndexOutOfRange();
        }

        T result = *iterator;
        delete enumPtr;
        return result;
}

template<typename T>
size_t SubSequenceView<T>::getLength() const { return endIndex - startIndex + 1; }