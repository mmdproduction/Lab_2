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
            throw std::runtime_error("Sequence is empty"); //TODO custom exeption
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

        if (iterator == end) throw std::runtime_error("Sequence is empty"); //TODO custom exeption

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
            throw std::out_of_range("Index out of range");
        }

        TargetType result = *iterator;
        delete enumPtr;
        return result;
    }

template<typename TargetType, typename SourceType>
size_t MapSequenceView<TargetType, SourceType>::getLength() const {
        return source.getLength();
    }

template<typename TargetType, typename SourceType>
MapSequenceView<TargetType, SourceType>*  MapSequenceView<TargetType, SourceType>::getSubsequence(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < startIndex) throw std::out_of_range("Invalid range");
        
        auto subSource = source.getSubsequence(startIndex, endIndex);
        auto result = new MapSequenceView<TargetType, SourceType>(*subSource, mapper);
        delete subSource;
        return result;

    }

template<typename TargetType, typename SourceType>
Sequence<TargetType>*  MapSequenceView<TargetType, SourceType>::concat(Sequence<TargetType>& other) const {
    //     return new ConcatSequence<TargetType>(*this, other);
    }
