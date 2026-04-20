template<typename T>
Iterator<T>::Iterator(IEnumerator<T>* enumPtr, bool end = false): enumerator(enumPtr), isEnd(end){
    if(!isEnd && enumerator){
        if(!enumerator->moveNext()){
            isEnd = true;
        }
    }
}

template<typename T>
T& Iterator<T>::operator*() const{
    return enumerator->current();
}

template<typename T>
Iterator& Iterator<T>::operator++(){
    if(enumerator && !enumerator->moveNext()){
        isEnd = true;
    }
    return *this;
}

template<typename T>
bool Iterator<T>::operator!=(const EnumeratorIterator& other) const {

        if (isEnd && other.isEnd) return false;
        if (isEnd || other.isEnd) return true;

        return true;
    }