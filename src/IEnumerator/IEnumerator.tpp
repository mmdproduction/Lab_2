    
template<typename T>
SequenceEnumerator<T>::SequenceEnumerator(const Sequence<T>* seq)
    : sequence(seq), currentIndex(0), isValid(seq->getSize() > 0) {}
   
template<typename T>
bool SequenceEnumerator<T>::moveNext() override {
   if (!isValid) return false;
   ++currentIndex;
   isValid = (currentIndex < sequence->getSize());
   return isValid;
}

template<typename T>
T& SequenceEnumerator<T>::current() override {
    if (!isValid) throw std::runtime_error("Enumerator is invalid");
    return const_cast<T&>(sequence->get(currentIndex));
}

template<typename T>
void SequenceEnumerator<T>::reset() override {
    currentIndex = 0;
    isValid = sequence->getSize() > 0;
}