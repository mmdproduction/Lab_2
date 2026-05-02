#pragma once
#include"Sequence.hpp"
#include <iostream>
#include <ostream>


//FIXME recreate all
class Bit{
    private:
    bool value;
    public:
    Bit() noexcept;
    explicit Bit(bool val) noexcept;
    explicit Bit(int val);
    explicit Bit(char val);

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
    size_t bitSize;

    static size_t getByteIndex(size_t bitIndex);
    static size_t getBitOffset(size_t bitIndex);
    static uint8_t getBitMask(size_t bitOffset);

    void provideCapacity(size_t newCapacity);

    public:

    BitSequence();
    BitSequence(size_t size);
    BitSequence(const BitSequence& other);
    BitSequence(int num);
    ~BitSequence() override = default;

    Bit getFirst() const override;
    Bit getLast() const override;
    Bit get(size_t index) const override;
    size_t getLength() const override;
    void append(Bit value) override;
    void prepend(Bit value) override;
    Bit operator[](int index) override;

    BitSequence operator&(BitSequence& other);
    BitSequence operator|(BitSequence& other);
    BitSequence operator^(BitSequence& other);
    BitSequence operator~();
    BitSequence operator<<(BitSequence& other);
    BitSequence operator>>(BitSequence& other);
};