#include"BitSequence.hpp"

Bit::Bit() noexcept: value(0){}
Bit::Bit(bool val) noexcept: value(val ? 1 : 0){}
Bit::Bit(int val) {
    if(val != 0 && val != 1){
        throw std::invalid_argument(" ");
    }
    value = val ? 1 : 0;
}
Bit::Bit(char val) {
    if(val != '0' && val != '1'){
        throw std::invalid_argument(" ");
    }
    value = static_cast<unsigned char>(val - '0');
}

Bit::operator bool() const{return value != 0; }
Bit::operator int() const{return value; }



Bit& Bit::operator=(bool val){ value = val ? 1 : 0; return *this; }
Bit& Bit::operator=(int val){value = (val !=0) ? 1 : 0; return *this; }
bool Bit::operator==(const Bit& other) const{ return value == other.value; }
bool Bit::operator!=(const Bit& other) const{ return value != other.value; }

Bit Bit::operator!() const noexcept { return Bit(value == 0 ? 1 : 0); }
Bit Bit::operator&(const Bit& other) const noexcept{return Bit(value & other.value); }
Bit Bit::operator|(const Bit& other) const noexcept{return Bit(value | other.value); }
Bit Bit::operator^(const Bit& other) const noexcept{return Bit(value ^ other.value); }
Bit Bit::operator~() const noexcept{return Bit(value ^ 1);}

bool Bit::getValue() const{ return value != 0; }
void Bit::setValue(bool val){ value = val ? 1 : 0; }
void Bit::flip(){value ^=1; }

std::ostream& operator<<(std::ostream& os, const Bit& bit){
    os << (bit.value ? '1' : '0');
        return os;
}

