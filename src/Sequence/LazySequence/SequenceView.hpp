#pragma once
#include "IEnumerator.hpp"
#include"LazyEnumerators.hpp"
#include <functional>

template<typename T> class Sequence;
template<typename T> class ListSequence;
template<typename T> class ArraySequence;
template<typename T> class Iterator;

//FIXME create append/prepend that create new real sequence from view

template<typename TargetType, typename SourceType>
class MapSequenceView : public Sequence<TargetType> {
private:
    const Sequence<SourceType>& source;
    std::function<TargetType(const SourceType&)> mapper;

public:
    MapSequenceView(const Sequence<SourceType>& src, std::function<TargetType(const SourceType&)> mapFunc);

    IEnumerator<TargetType>* getEnumerator() const override;

    TargetType getFirst() const override;

    TargetType getLast() const override;

    TargetType get(size_t index) const override;

    size_t getLength() const override;

    void append(TargetType) override { throw ReadOnlyError(); } 
    void prepend(TargetType) override { throw ReadOnlyError(); }

    MapSequenceView* getSubsequence(int startIndex, int endIndex) const override;
    TargetType operator[](int index) override { return get(index); }
    ~MapSequenceView() override = default;
};

template<typename T>
class FilterSequenceView : public Sequence<T> {
private:
    const Sequence<T>& source;
    std::function<bool(const T&)> filter;

public:
    FilterSequenceView(const Sequence<T>& src, std::function<T(const T&)> filtFunc);

    IEnumerator<T>* getEnumerator() const override;

    T getFirst() const override;

    T getLast() const override;

    T get(size_t index) const override;

    size_t getLength() const override;

    void append(T) override { throw ReadOnlyError(); } 
    void prepend(T) override { throw ReadOnlyError(); } 

    FilterSequenceView* getSubsequence(int startIndex, int endIndex) const override;

    T operator[](int index) override { return get(index); }
    ~FilterSequenceView() override = default;
};

template<typename T>
class ConcatSequenceView : public Sequence<T> {
private:
    const Sequence<T>& first;
    const Sequence<T>& second;

public:
    ConcatSequenceView(const Sequence<T>& firstSrc, const Sequence<T>& secondSrc);

    IEnumerator<T>* getEnumerator() const override;

    T getFirst() const override;
    T getLast() const override;
    T get(size_t index) const override;
    size_t getLength() const override;

    void append(T) override { throw ReadOnlyError(); } 
    void prepend(T) override { throw ReadOnlyError(); }

    Sequence<T>* getSubsequence(int startIndex, int endIndex) const override;

    T operator[](int index) override { return get(index); }
    ~ConcatSequenceView() override = default;
};

#include"MapSequenceView.tpp"
#include"FilterSequenceView.tpp"
#include"ConcatSequenceView.tpp"
