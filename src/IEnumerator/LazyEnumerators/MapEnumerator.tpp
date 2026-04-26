template<typename TargetType, typename SourceType>
MapEnumerator<TargetType, SourceType>::MapEnumerator(IEnumerator<SourceType>* src, std::function<TargetType(const SourceType&)> mapFunc)
        : source(src), mapper(mapFunc), isValid(false) {}

template<typename TargetType, typename SourceType>
bool MapEnumerator<TargetType, SourceType>::moveNext(){
    if(source->moveNext()){
        currentValue = mapper(source->current());
        isValid = true;
        return true;
    }
    isValid = false;
    return false;
}
template<typename TargetType, typename SourceType>
TargetType MapEnumerator<TargetType, SourceType>::current() {
        if (!isValid) throw std::runtime_error("Enumerator invalid"); //TODO custom exeption
        return currentValue;
    }

template<typename TargetType, typename SourceType>
void MapEnumerator<TargetType, SourceType>::reset(){
        source->reset();
        isValid = false;
}