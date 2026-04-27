template<typename T>
FilterSequenceView<T>::FilterSequenceView(const Sequence<T>& src, std::function<T(const T&)> filtFunc)
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
            throw std::runtime_error("Sequence is empty"); //TODO custom exeption
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

        if (iterator == end) throw std::runtime_error("Sequence is empty"); //TODO custom exeption

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


template<typename T>
FilterSequenceView<T>* FilterSequenceView<T>::getSubsequence(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < startIndex) throw IndexOutOfRange();
        
        auto subSource = source.getSubsequence(startIndex, endIndex);
        auto result = new FilterSequenceView<T>(*subSource, filter);
        delete subSource;
        return result;

    }
