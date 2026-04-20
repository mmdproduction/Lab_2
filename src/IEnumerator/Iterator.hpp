#include"IEnumerator.hpp"

template<typename T>
class Iterator{
    private:

    IEnumerator<T>* enumerator;
    bool isEnd;

    public:
    Iterator(IEnumerator<T>* enumPtr, bool end = false);
    T& operator*() const;
    EnumeratorIterator& operator++();
    bool operator!=(const EnumeratorIterator& other) const;
};
#include"Iterator.tpp"