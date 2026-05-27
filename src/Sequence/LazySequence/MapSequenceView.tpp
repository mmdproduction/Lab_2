template<typename TargetType, typename SourceType>
MapSequenceView<TargetType, SourceType>::MapSequenceView(const Sequence<SourceType>& src, std::function<TargetType(const SourceType&)> mapFunc)
        : source(src), mapper(mapFunc) {}

template<typename TargetType, typename SourceType>
IEnumerator<TargetType>* MapSequenceView<TargetType, SourceType>::getEnumerator() const {
        return new MapEnumerator<TargetType, SourceType>(source.getEnumerator(), mapper);
    }

template<typename TargetType, typename SourceType>
TargetType MapSequenceView<TargetType, SourceType>::getFirst() const {
        auto enumPtr = getEnumerator();
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<TargetType>::endIterator();
        if (iterator == end) {
            delete enumPtr;
            throw EmptySequence();
        }
        TargetType result = *iterator;
        delete enumPtr;
        return result;
    }




template<typename TargetType, typename SourceType>
TargetType MapSequenceView<TargetType, SourceType>::getLast() const {
        TargetType result;
        
        auto enumPtr = getEnumerator();
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<TargetType>::endIterator();

        if (iterator == end) throw EmptySequence();

        while(++iterator != end){
            result = *iterator;
        }
        
        delete enumPtr;
        return result;
    }

template<typename TargetType, typename SourceType>
TargetType MapSequenceView<TargetType, SourceType>::get(size_t index) const {
        auto enumPtr = new IndexEnumerator<TargetType>(getEnumerator(), index);
        auto iterator = Iterator(enumPtr, false);
        auto end = Iterator<TargetType>::endIterator();

        if (iterator == end) {
            delete enumPtr;
            throw IndexOutOfRange();
        }

        TargetType result = *iterator;
        delete enumPtr;
        return result;
    }

template<typename TargetType, typename SourceType>
size_t MapSequenceView<TargetType, SourceType>::getLength() const {
        return source.getLength();
    }