#include"BitSequence.hpp"

Bit::Bit(): value(0){}
Bit::Bit(bool val): value(val ? 1 : 0){}
Bit::Bit(int val): value(val ? 1 : 0) {}

Bit::operator bool() const{return value != 0; }
Bit::operator int() const{return value; }

Bit Bit::operator!() const{ return Bit(!value); }
Bit& Bit::operator=(bool val){ value = val ? 1 : 0; return *this; }
Bit& Bit::operator=(int val){value = (val !=0) ? 1 : 0; return *this; }
bool Bit::operator==(const Bit& other) const{ return value == other.value; }
bool Bit::operator!=(const Bit& other) const{ return value != other.value; }

bool Bit::getValue() const{ return value != 0; }
void Bit::setValue(bool val){ value = val ? 1 : 0; }
void Bit::flip(){value = value? 0 : 1; }

friend std::ostream& operator<<(std::ostream& os, const Bit& bit){
    os << (bit.value ? '1' : '0');
        return os;
}