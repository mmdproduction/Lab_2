
template<typename T>
ListSequence<T>::ListSequence() : list(new LinkedList<T>()) {}

template<typename T>
ListSequence<T>::ListSequence(T* item, int count) {
    list = new LinkedList<T>();
    for (int i = 0; i < count; ++i) {
        list->append(item[i]);
    }
}

template <typename T>
ListSequence<T>::ListSequence(const ListSequence<T>& other){
    list = new LinkedList(*(other.list));
}

template<typename T>
ListSequence<T>::ListSequence(const std::initializer_list<T>& list){
    this->list = new LinkedList(list);
}

template <typename T>
T& ListSequence<T>::getFirst() const{
    return list->getFirst();
}

template <typename T>
T& ListSequence<T>::getLast() const{
    return list->getLast();
}

template <typename T>
T& ListSequence<T>::get(size_t index) const{
    return list->get(index);
}

template <typename T>
size_t ListSequence<T>::getLength() const{
    return list->getLength();
}

template <typename T>
void ListSequence<T>::append(const T& value){
    list->append(value);
}

template <typename T>
void ListSequence<T>::prepend(const T& value){
    list->prepend(value);
}

template<typename T>
ListSequence<T>::~ListSequence() { delete list; }

template<typename T>
T& ListSequence<T>::operator[](int index){
    return (*list)[index];
}

template <typename T>
void ListSequence<T>::set(const T& value, size_t index){
    list->set(value, index);
}


template <typename T>
void ListSequence<T>::popAt(size_t index){
    list->popAt(index);
}