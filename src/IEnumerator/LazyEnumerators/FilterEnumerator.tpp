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
            return false;

        }
    }
    isValid = false;
    return false;
}

template<typename T>
T FilterEnumerator<T>::current(){
    if (!isValid) throw std::runtime_error("Enumerator invalid");
    return currentValue;
}

template<typename T>
void FilterEnumerator<T>::reset(){
    source->reset();
    isValid = false;
}

