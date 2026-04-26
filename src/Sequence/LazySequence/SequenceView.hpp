#pragma once
#include "IEnumerator.hpp"
#include"LazyEnumerators.hpp"
#include <functional>

template<typename T> class Sequence;
template<typename T> class ListSequence;
template<typename T> class ArraySequence;
template<typename T> class Iterator;


template<typename TargetType, typename SourceType>
class MapSequenceView : public Sequence<TargetType> {
private:
    const Sequence<SourceType>& source;
    std::function<TargetType(const SourceType&)> mapper;

public:
    MapSequenceView(const Sequence<SourceType>& src, std::function<TargetType(const SourceType&)> mapFunc)
        : source(src), mapper(mapFunc) {}

    IEnumerator<TargetType>* getEnumerator() const override;

    TargetType getFirst() const override;

    TargetType getLast() const override;

    TargetType get(size_t index) const override;

    size_t getLength() const override;

    void append(TargetType) override { throw std::runtime_error("Read-only"); }
    void prepend(TargetType) override { throw std::runtime_error("Read-only"); }

    MapSequenceView* getSubsequence(int startIndex, int endIndex) const override;

     Sequence<TargetType>* concat(Sequence<TargetType>& other) const override;

    TargetType operator[](int index) override { return get(index); }
    ~MapSequenceView() override = default;
};

template<typename T>
class FilterSequenceView : public Sequence<T> {
private:
    const Sequence<T>& source;
    std::function<bool(const T&)> mapper;

public:
    FilterSequenceView(const Sequence<T>& src, std::function<T(const T&)> mapFunc)
        : source(src), mapper(mapFunc) {}

    IEnumerator<T>* getEnumerator() const override;

    T getFirst() const override;

    T getLast() const override;

    T get(size_t index) const override;

    size_t getLength() const override;

    void append(T) override { throw std::runtime_error("Read-only"); }
    void prepend(T) override { throw std::runtime_error("Read-only"); }

    FilterSequenceView* getSubsequence(int startIndex, int endIndex) const override;

    Sequence<T>* concat(Sequence<T>& other) const override;

    T operator[](int index) override { return get(index); }
    ~FilterSequenceView() override = default;
};


