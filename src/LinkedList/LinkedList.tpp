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
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while(current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

template<typename T>
T LinkedList<T>::getFirst(){
    if(size == 0){ 
        throw IndexOutOfRange(0, size);
    }
    return head->data;
}

template<typename T>
T LinkedList<T>::getLast(){
    if(size == 0){
        throw IndexOutOfRange(0, size); 
    }
    return tail->data;
}

template<typename T>
T LinkedList<T>::get(int index){
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
size_t LinkedList<T>::getLength(){
    return size;
}

template<typename T>
void LinkedList<T>::append(T item){
    Node* node = new Node(item);
    if(head == nullptr){
        head = node;
        tail = head;
    }
    else{
        tail->next = node;
        tail = node;
    }

    size++;
}

template<typename T>
void LinkedList<T>::prepend(T item){
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
void LinkedList<T>::insertAt(T item, int index){
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
T LinkedList<T>::operator[](int index){
    Node* tmp = head;
    for(size_t i = 0; i < index; ++i){
        tmp = tmp->next;
    }
    return tmp->data;
}