template<typename T>
ConcatEnumerator<T>::ConcatEnumerator(IEnumerator<T>* firstEnum, IEnumerator<T>* SecondEnum)
    : first(firstEnum), second(secondEnum), active(firstEnum), isValid(false) {}


template<typename T>
bool ConcatEnumerator<T>::moveNext(){
    if(active->moveNext()){
        currentValue = active->current();
        isValid = true;
        return true;
    }

    if(active == first){
        active = second;
        if(active->moveNext()){
        currentValue = active->current();
        isValid = true;
        return true;
        }
    }

    isValid = false;
    return false;
}

template<typename T>
T ConcatEnumerator<T>::current(){
    if (!isValid) throw std::runtime_error("Enumerator invalid");
    return currentValue;
}

template<typename T>
T ConcatEnumerator<T>::reset(){
    source->reset();
    isValid = false;
}