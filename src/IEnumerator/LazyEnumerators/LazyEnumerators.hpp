#pragma once
#include"IEnumerator.hpp"
#include<functional>

template<typename TargetType, typename SourceType>
class MapEnumerator: public IEnumerator<TargetType>{
    private:

    IEnumerator<SourceType>* source;
    std::function<TargetType(const SourceType&)> mapper;
    bool isValid;
    TargetType currentValue;

    public:
    MapEnumerator(IEnumerator<SourceType>* src, std::function<TargetType(const SourceType&)> mapFunc);

    ~MapEnumerator() override { delete source; }
    bool moveNext() override;
    TargetType current() override;
    void reset() override;
};

template<typename T>
class FilterEnumerator: public IEnumerator<T>{
    private:

    IEnumerator<T>* source;
    std::function<bool(const T&)> filter;
    bool isValid;
    T currentValue;

    public:
    FilterEnumerator(IEnumerator<T>* src, std::function<bool(const T&)> mapFunc);

    ~FilterEnumerator() override { delete source; }

    bool moveNext() override;
    T current() override;
    void reset() override;
};


template<typename T>
class ConcatEnumerator: public IEnumerator<T>{
    private:

    IEnumerator<T>* first;
    IEnumerator<T>* second;
    IEnumerator<T>* active;

    bool isValid;
    T currentValue;

    public:
    ConcatEnumerator(IEnumerator<T>* firstEnum, IEnumerator<T>* SecondEnum);
    ~ConcatEnumerator() override { delete first; delete second; };

    bool moveNext() override;
    T current() override;
    void reset() override;
};

template<typename T>
class IndexEnumerator: public IEnumerator<T>{
    private:

    IEnumerator<T>* source;
    size_t targetIndex;
    size_t currentIndex;
    bool isValid;
    bool found;

    T currentValue;

    public:

    IndexEnumerator(IEnumerator<T>* src, size_t index);
    ~IndexEnumerator() override { delete source; }

    bool moveNext() override;
    T current() override;
    void reset() override;
};

template<typename T>
class SkipEnumerator : public IEnumerator<T> {
    private:

    IEnumerator<T>* source;
    size_t skip;
    size_t take;
    size_t currentIndex;
    bool isValid;

    public:

    SkipEnumerator(IEnumerator<T>* source, size_t skipCount, size_t takeCount);
    ~SkipEnumerator() override { delete source; };

    bool moveNext() override;
    T current() override;
    void reset() override;

};



#include"MapEnumerator.tpp"
#include"FilterEnumerator.tpp"
#include"ConcatEnumerator.tpp"
#include"IndexEnumerator.tpp"
#include"SkipEnumerator.tpp"