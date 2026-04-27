template<typename T>
IndexEnumerator<T>::IndexEnumerator(IEnumerator<T>* src, size_t index)
        : source(src), targetIndex(index), currentIndex(0), isValid(false), found(false) {}

template<typename T>
bool IndexEnumerator<T>::moveNext(){
    if (found) {
            isValid = false;
            return false;
        }

    while (source->moveNext())
    {
        if(currentIndex == targetIndex){
            currentValue = source->current();
        }
        ++currentIndex;
    }
    isValid = false;
    return false;
}

template<typename T>
T IndexEnumerator<T>::current(){
    if (!isValid) InvalidEnumerator();
    return currentValue;
}

template<typename T>
void IndexEnumerator<T>::reset(){
    source->reset();
    isValid = false;
    currentIndex = 0;
    found = false;
}
