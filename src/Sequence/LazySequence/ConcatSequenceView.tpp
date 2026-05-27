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
            throw IndexOutOfRange();
        }

        T result = *iterator;
        delete enumPtr;
        return result;
    }

template<typename T>
size_t ConcatSequenceView<T>::getLength() const{
    return first.getLength() + second.getLength();
}


