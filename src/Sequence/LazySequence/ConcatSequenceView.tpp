template<typename T>
ConcatSequenceView<T>::ConcatSequenceView(const Sequence<T>& firstSrc, const Sequence<T>& secondSrc)
    : first(firstSrc), second(secondSrc) {}

template<typename T>
IEnumerator<T>* ConcatSequenceView<T>::getEnumerator() const {
    return new ConcatEnumerator(first.getEnumerator(), second.getEnumerator());
}

template<typename T>
T ConcatSequenceView<T>::getFirst() const { return first.getFirst();
    }

template<typename T>
T ConcatSequenceView<T>::getLast() const { return second.getLast();}

template<typename T>
T ConcatSequenceView<T>::get(size_t index) const {
        auto enumPtr = new IndexEnumerator<T>(getEnumerator(), index);
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<T>::endIterator();

        if (iterator == end) {
            delete enumPtr;
            throw std::out_of_range("Index out of range");
        }

        T result = *iterator;
        delete enumPtr;
        return result;
    }

template<typename T>
size_t ConcatSequenceView<T>::getLength() const{
    return first.getLength() + second.getLength();
}


template<typename T>
Sequence<T>* ConcatSequenceView<T>::getSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < startIndex) throw std::out_of_range("Invalid range"); //TODO custom exception
    size_t lenFirst = first.getLength();
    size_t concatLen = lenFirst + second.getLength();

    if (endIndex >= static_cast<int>(concatLen)) {
        throw std::out_of_range("End index out of range");
    }

    if (endIndex < static_cast<int>(lenFirst)) {
        return first.getSubsequence(startIndex, endIndex);
    }

    if (startIndex >= static_cast<int>(lenFirst)) {
        return second.getSubsequence(startIndex - lenFirst, endIndex - lenFirst);
    }

    Sequence<T>* leftPart = first.getSubsequence(startIndex, lenFirst - 1);
    Sequence<T>* rightPart = second.getSubsequence(0, endIndex - lenFirst);

    return new ConcatSequenceView<T>(*leftPart, *rightPart);
    }

