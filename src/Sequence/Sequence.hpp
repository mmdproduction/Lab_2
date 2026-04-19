#include"../LinkedList/LinkedList.hpp"
#include"../DynamicArray/DynamicArray.hpp"

template <typename T>
class Sequence{
    public:
    virtual ~Sequence() = default;
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(size_t index) = 0;
    virtual size_t getSize() = 0;
    virtual void append(T value) = 0;
    virtual void prepend(T value) = 0;
    virtual Sequence<T>* getSubsequence(int startIndex, int endIndex) = 0;
    Sequence<T> concat(Sequence<T>& list);

};


template<typename T>
class SequenceArray : public Sequence<T>{
    private:

    DynamicArray<T>* array;
    size_t capacity;

    public:

    SequenceArray();
    SequenceArray(T* item, int count);
    SequenceArray(const SequenceArray<T>& other);
    ~SequenceArray();

    T getFirst() override;
    T getLast() override;
    T get(size_t index) override;
    size_t getSize() override;
    void append(T value) override;
    void prepend(T value) override;
    SequenceArray<T> getSubsequence(int startIndex, int endIndex) override;
};

template<typename T>
class SequenceList : public Sequence<T>{
    private:
    LinkedList<T>* list;
    public:

    SequenceList();
    SequenceList(T* item, int count);
    SequenceList(const SequenceList<T>& other);

    T getFirst() override;
    T getLast() override;
    T get(size_t index) override;
    size_t getSize() override;
    void append(T value) override;
    void prepend(T value) override;
    SequenceList<T> getSubsequence(int startIndex, int endIndex) override;
};

#include"Sequence.tpp"