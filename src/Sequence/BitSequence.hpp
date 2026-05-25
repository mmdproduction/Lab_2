#pragma once
#include"Sequence.hpp"
#include <iostream>
#include <ostream>


class Bit{
    private:
    bool value;
    public:
    Bit() noexcept;
    Bit(bool val) noexcept;
    Bit(int val);
    Bit(char val);

    operator int() const;
 
    bool getValue() const;
    void setValue(bool val);

    bool operator==(const Bit& other) const;
    bool operator!=(const Bit& other) const;

    void flip();
    friend std::ostream& operator<<(std::ostream& os, const Bit& bit);
};


class BitSequence: public Sequence<Bit>{
    private:

    DynamicArray<uint8_t> data;
    size_t bitCount;

    static size_t getByteIndex(size_t bitIndex);
    static size_t getBitOffset(size_t bitIndex);
    static uint8_t getBitMask(size_t bitOffset);
    Bit getBit(size_t index) const;
    void setBit(const Bit& value, size_t index);

    void provideCapacity(size_t newCapacity);

    public:

    BitSequence();
    BitSequence(size_t size);
    BitSequence(const BitSequence& other);
    ~BitSequence() override = default;

    Bit getFirst() const override;
    Bit getLast() const override;
    Bit get(size_t index) const override;
    size_t getLength() const override;
    void append(const Bit& value) override;
    void prepend(const Bit& value) override;
    void set(const Bit& value, size_t index) override;

    void popAt(size_t index) override;

    Bit operator[](int index) override;



    BitSequence operator&(const BitSequence& other);
    BitSequence operator|(const BitSequence& other);
    BitSequence operator^(const BitSequence& other);
    BitSequence operator~();
};