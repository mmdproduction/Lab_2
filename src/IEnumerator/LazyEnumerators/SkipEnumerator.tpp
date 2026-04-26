template<typename T>
SkipEnumerator<T>::SkipEnumerator(IEnumerator<T>* src, size_t skipCount, size_t takeCount)
        : source(src), skip(skipCount), take(takeCount), currentIndex(0), isValid(false) {}

template<typename T>
bool SkipEnumerator<T>::moveNext(){

    while (currentIndex < skip && source->moveNext())
    {
        ++currentIndex;
    }

    if(currentIndex >= skip && currentIndex < skip + take && source->moveNext()){
        ++currentIndex;
        isValid = true;
        return true;
    }

    isValid = false;
    return false;
}

template<typename T>
T SkipEnumerator<T>::current(){
    if (!isValid) throw std::runtime_error("Enumerator invalid"); //TODO custom exeption
    return source->current();
}

template<typename T>
void SkipEnumerator<T>::reset(){
    source->reset();
    isValid = false;
    currentIndex = 0;
}
