template<typename T>
FilterEnumerator<T>::FilterEnumerator(IEnumerator<T>* src, std::function<bool(const T&)> filterFunc)
        : source(src), filter(filterFunc), isValid(false) {}

template<typename T>
bool FilterEnumerator<T>::moveNext(){
    while (source->moveNext())
    {
        if(filter(source->current())){

            currentValue = source->current();
            isValid = true;
            return true;

        }
    }
    isValid = false;
    return false;
}

template<typename T>
T FilterEnumerator<T>::current(){
    if (!isValid) throw InvalidEnumerator()
    return currentValue;
}

template<typename T>
void FilterEnumerator<T>::reset(){
    source->reset();
    isValid = false;
}

