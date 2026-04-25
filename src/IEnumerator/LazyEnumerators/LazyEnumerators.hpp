#pragma once
#include"IEnumerator.hpp"
#include<functional>

template<typename TargetType, typename SourceType>
class MapEnumerator: public IEnumerator<SourceType>{
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
}

#include"MapEnumerator.tpp"
#include"FilterEnumerator.tpp"
#include"ConcatEnumerator.tpp"