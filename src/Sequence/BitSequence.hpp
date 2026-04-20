#pragma once
#include"Sequence.hpp"

class Bit{
    private:
    unsigned char value;
    public:
    Bit();
    Bit(bool val);
    Bit(int val);
    
    operator bool() const;
    operator int() const;

    Bit operator!() const;
    Bit& operator=(bool val);
    Bit& operator=(int val);

    bool operator==(const Bit& other) const;
    bool operator!=(const Bit& other) const;

    bool getValue() const;
    void setValue(bool val);
    void flip();
    friend std::ostream& operator<<(std::ostream& os, const Bit& bit);
};