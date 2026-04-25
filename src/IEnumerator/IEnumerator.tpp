    
template<typename T>
SequenceEnumerator<T>::SequenceEnumerator(const Sequence<T>* seq)
    : sequence(seq), currentIndex(static_cast<size_t>(-1)), isValid(seq->getLength() > 0) {}
   
template<typename T>
bool SequenceEnumerator<T>::moveNext(){
   if (!isValid) return false;
   ++currentIndex;
   isValid = (currentIndex < sequence->getLength());
   return isValid;
}

template<typename T>
T SequenceEnumerator<T>::current(){
    if (!isValid) throw std::runtime_error("Enumerator is invalid");
    return sequence->get(currentIndex);
}

template<typename T>
void SequenceEnumerator<T>::reset(){
    currentIndex = 0;
    isValid = sequence->getLength() > 0;
}
