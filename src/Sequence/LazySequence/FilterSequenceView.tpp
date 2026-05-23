template<typename T>
FilterSequenceView<T>::FilterSequenceView(const Sequence<T>& src, std::function<bool(const T&)> filtFunc)
    : source(src), filter(filtFunc) {}

template<typename T>
IEnumerator<T>* FilterSequenceView<T>::getEnumerator() const {
    return new FilterEnumerator(source.getEnumerator(), filter);
}

template<typename T>
T FilterSequenceView<T>::getFirst() const {
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
T FilterSequenceView<T>::getLast() const {
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
T FilterSequenceView<T>::get(size_t index) const {
        auto enumPtr = new IndexEnumerator<T>(getEnumerator(), index);
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<T>::endIterator();

        if (iterator == end) {
            delete enumPtr;
            throw IndexOutOfRange(index);
        }

        T result = *iterator;
        delete enumPtr;
        return result;
    }

template<typename T>
size_t FilterSequenceView<T>::getLength() const{
    size_t count = 0;
    auto enumPtr = getEnumerator();
    while(enumPtr->moveNext()){
        ++count;
    }
    delete enumPtr;
    return count;
}