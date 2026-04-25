#pragma once
#include"Sequence.hpp"
#include <iostream>
#include <ostream>

class Bit{
    private:
    unsigned char value;
    public:
    Bit() noexcept;
    explicit Bit(bool val) noexcept;
    explicit Bit(int val);
    explicit Bit(char val);
    
    operator bool() const;
    operator int() const;

    Bit& operator=(bool val);
    Bit& operator=(int val);

    Bit operator&(const Bit& other) const noexcept;
    Bit operator|(const Bit& other) const noexcept;
    Bit operator^(const Bit& other) const noexcept;
    Bit operator~() const noexcept; 
    Bit operator!() const noexcept;


    bool operator==(const Bit& other) const;
    bool operator!=(const Bit& other) const;

    bool getValue() const;
    void setValue(bool val);
    void flip();
    friend std::ostream& operator<<(std::ostream& os, const Bit& bit);
};


class BitSequence: public Sequence<Bit>{
    private:
    DynamicArray<uint64_t>* data;
    public:

    BitSequence();
    BitSequence(int size);
    BitSequence(const Bit* bits, int count);

    BitSequence operator&(BitSequence& other);
    BitSequence operator|(BitSequence& other);
    BitSequence operator^(BitSequence& other);
    BitSequence operator~();
    BitSequence operator<<(BitSequence& other);
    BitSequence operator>>(BitSequence& other);
};