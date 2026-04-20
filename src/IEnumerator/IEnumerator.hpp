#pragma once


template<typename T>
class IEnumerator{
    public:
    virtual ~IEnumerator() = default;
    virtual bool moveNext() = 0;
    virtual T& current() = 0;
    virtual void reset() = 0;
};

template<typename T>
class IEnumerable{
    public:
    virtual ~IEnumerable() = default;
    virtual IEnumerator<T>* getEnumerator() = 0;
};

template<typename T>
class SequenceEnumerator : public IEnumerator<T> {
private:
    const Sequence<T>* sequence;
    size_t currentIndex;
    bool isValid;

public:
    SequenceEnumerator(const Sequence<T>* seq);

    bool moveNext() override;
    T& current() override;
    void reset() override;

};

#include"IEnumerator.tpp"