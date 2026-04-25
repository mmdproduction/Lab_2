#include"IEnumerator.hpp"

template<typename T>
class Iterator{
    private:

    IEnumerator<T>* enumerator;
    bool isEnd;

    public:
    Iterator(IEnumerator<T>* enumPtr, bool end = false);
    T operator*() const;
    Iterator<T>& operator++();
    bool operator!=(const Iterator& other) const;

    static Iterator<T> endIterator() {
    return Iterator<T>(nullptr, true);
    }
};
#include"Iterator.tpp"
