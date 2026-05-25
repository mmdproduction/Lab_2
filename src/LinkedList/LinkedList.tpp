template<typename T>
LinkedList<T>::LinkedList(): size(0), head(nullptr), tail(nullptr){}

template<typename T>
LinkedList<T>::LinkedList(T* item, int count): size(0), head(nullptr), tail(nullptr){
    for(size_t i = 0; i < count; ++i){
        append(item[i]);
    }
}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list): size(0), head(nullptr), tail(nullptr){
    auto current = list.head;

    while(current != nullptr){
        append(current->data);
        current = current->next;
    }
} 

template<typename T>
LinkedList<T>::LinkedList(const std::initializer_list<T>& list): size(0), head(nullptr), tail(nullptr){
    for(const auto elem : list){
        append(elem);
    }
} 


template<typename T>
LinkedList<T>::~LinkedList() {
    
    if (head == nullptr) return;

    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }

    head = nullptr;
    tail = nullptr;
    size = 0;
}

template<typename T>
T& LinkedList<T>::getFirst() const{
    if(size == 0){ 
        throw IndexOutOfRange(0, size);
    }
    return head->data;
}

template<typename T>
T& LinkedList<T>::getLast() const{
    if(size == 0){
        throw IndexOutOfRange(0, size); 
    }
    return tail->data;
}

template<typename T>
T& LinkedList<T>::get(int index) const {
    if(index < 0 || index >= size){
        throw IndexOutOfRange(index, size); 
    }
    Node* tmp = head;
    for(int i = 0; i < index; ++i){
        if(tmp == nullptr){
            throw InvalidPointer();
        }
        tmp = tmp->next;
    }
    if(tmp == nullptr){
            throw InvalidPointer();
        }
    return tmp->data;
}

template<typename T>
LinkedList<T>* LinkedList<T>::getSubList(int startIndex, int endIndex){
    if(startIndex < 0 || startIndex >= size){
        throw IndexOutOfRange(startIndex, size);
    } 
    if(endIndex < 0 || endIndex >= size){
        throw IndexOutOfRange(endIndex, size);
    } 
    Node* tpm = head;
    for(size_t i = 0; i < startIndex; ++i){
        tpm = tpm->next;
    }
    LinkedList<T>* subList = new LinkedList();
    for(size_t i = startIndex; i < endIndex; ++i){
        subList->append(tpm->data);
        tpm = tpm->next;
    }
    return subList;
}

template<typename T>
size_t LinkedList<T>::getLength() const{
    return size;
}

template<typename T>
void LinkedList<T>::append(const T& item){
    Node* node = new Node(item);
    if(head == nullptr){
        head = node;
        tail = node;
    }
    else{
        tail->next = node;
        tail = node;
    }

    size++;
}

template<typename T>
void LinkedList<T>::prepend(const T& item){
    Node* node = new Node(item);
    if(head == nullptr){
        head = node;
        tail = head;
    }
    else{
        node->next = head;
        head = node;
    }
    size++;
}

template<typename T>
void LinkedList<T>::insertAt(const T& item, int index){
    if(index < 0 || index > size){
        throw IndexOutOfRange(index, size);
    }
    if(index == 0){
        prepend(item);
        return;
    }
    if(index == size){
        append(item);
        return;
    }
    Node* node = new Node(item);
    Node* tpm = head;
    for(size_t i = 0; i < index - 1; ++i){
        tpm = tpm->next;
    }
    node->next = tpm->next;
    tpm->next = node;

    size++;
}

template<typename T>
void LinkedList<T>::set(const T& item, size_t index){
    if(index < 0 || index >= size){
        throw IndexOutOfRange(index, size);
    }
    
    if(index == 0){
        head->data = item;
        return;
    }

    Node* tpm = head;
    for(size_t i = 0; i < index; ++i){
        tpm = tpm->next;
    }
    tpm->data = item;
}

template<typename T>
void LinkedList<T>::popAt(size_t index){
    if(index >= size){
        throw IndexOutOfRange(index, size);
    }
    if(index == 0){
        Node* tpm = head;
        head = head->next;
        delete tpm;
        return;
    }

    Node* tpm = head;
    for(size_t i = 0; i < index - 1; ++i){
        tpm = tpm->next;
    }
    Node* del = tpm->next;
    tpm->next = tpm->next->next;
    delete del;
    size--;
}

template<typename T>
LinkedList<T>* LinkedList<T>::concat(LinkedList<T>& list){
    LinkedList<T>* concatList = new LinkedList();
    Node* tpm = head;
    while(tpm != nullptr){
        concatList.append(tpm->data);
        tpm  = tpm->next;
    }
    tpm = list.head;
    while(tpm != nullptr){
        concatList.append(tpm->data);
        tpm  = tpm->next;
    }
    return concatList;
}

template<typename T>
T& LinkedList<T>::operator[](int index) const{
    Node* tmp = head;
    for(size_t i = 0; i < index; ++i){
        tmp = tmp->next;
    }
    return tmp->data;
}

template<typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {
        LinkedList temp(other);
        std::swap(head, temp.head);
        std::swap(tail, temp.tail);
        std::swap(size, temp.size);
    }
    return *this;
}