#include"BitSequence.hpp"

Bit::Bit() noexcept: value(0){}
Bit::Bit(bool val) noexcept: value(val){}
Bit::Bit(int val) {
    if(val != 0 && val != 1){
        throw InvalidArgument();
    }
    value = val == 1 ? true : false;
}
Bit::Bit(char val) {
    if(val != '0' && val != '1'){
        throw InvalidArgument();
    }
    value = val == '1'? true : false;
}

Bit::operator int() const{return value ? 1 : 0; }
bool Bit::operator==(const Bit& other) const {
    return value == other.value;
}

bool Bit::operator!=(const Bit& other) const {
    return value != other.value;
}

bool Bit::getValue() const{ return !value; }
void Bit::setValue(bool val){ value = val ? true : false; }
void Bit::flip(){value ^=1; }


std::ostream& Bit::operator<<(std::ostream& os, const Bit& bit) {
        return os << (bit.value ? '1' : '0');
    }


size_t BitSequence::getByteIndex(size_t bitIndex) { 
    return bitIndex / 8;
}

size_t BitSequence::getBitOffset(size_t bitIndex) {
    return bitIndex % 8;
}

uint8_t BitSequence::getBitMask(size_t bitOffset) {
    return static_cast<uint8_t>(1 << bitOffset); 
}


BitSequence::provideCapacity(size_t newCapacity){
    size_t newByteSize = (newCapacity + 7) / 8;

    if(newByteSize > data.getSize()) data.resize(newByteSize);
}

BitSequence::BitSequence() 
    : data(), bitCount(0) {}

BitSequence::BitSequence(size_t size) 
    : data((size + 7) / 8), bitCount(size) {
    for (size_t i = 0; i < data.getSize(); ++i) {
        data.set(i, 0);
    }
}

BitSequence::BitSequence(const BitSequence& other)
    : data(other.data), bitCount(other.bitCount) {}

Bit BitSequence::getFirst() const {
    if (bitCount == 0) throw EmptySequence();
    return getBit(0);
}

Bit BitSequence::getLast() const {
    if (bitCount == 0) throw EmptySequence();
    return getBit(bitCount - 1);
}

Bit BitSequence::get(size_t index) const {
    if (index >= bitCount) throw InvalidIndex(index, bitCount);
    return getBit(index);
}