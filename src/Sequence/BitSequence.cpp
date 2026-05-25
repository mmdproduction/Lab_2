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


std::ostream& operator<<(std::ostream& os, const Bit& bit) {
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


void BitSequence::provideCapacity(size_t newCapacity){
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

Bit& BitSequence::getFirst() const {
    if (bitCount == 0) throw EmptySequence();
    return getBit(0);
}

Bit& BitSequence::getLast() const {
    if (bitCount == 0) throw EmptySequence();
    return getBit(bitCount - 1);
}

Bit& BitSequence::get(size_t index) const {
    if (index >= bitCount) throw IndexOutOfRange(index, bitCount);
    return getBit(index);
}

size_t BitSequence::getLength() const {
    return bitCount;
}

Bit& BitSequence::getBit(size_t index) const {
    if (index >= bitCount) IndexOutOfRange(index, bitCount);
    
    
    size_t byteIndex = getByteIndex(index);
    size_t bitOffset = getBitOffset(index);
    
    return Bit((data.get(byteIndex) & getBitMask(bitOffset)) != 0);
}

Bit& BitSequence::operator[](int index){
    size_t byteIndex = getByteIndex(index);
    size_t bitOffset = getBitOffset(index);
    
    return Bit((data.get(byteIndex) & getBitMask(bitOffset)) != 0);
}

void BitSequence::setBit(const Bit& value, size_t index){
    if (index >= bitCount) IndexOutOfRange(index, bitCount);
    
    size_t byteIndex = getByteIndex(index);
    size_t bitOffset = getBitOffset(index);
    uint8_t mask = getBitMask(bitOffset);
    uint8_t current = data.get(byteIndex);

    if(value){
        data.set(byteIndex, current | mask);
    }
    else{
        data.set(byteIndex, current & ~mask);
    }
}


void BitSequence::append(const Bit& value){
    size_t newIndex = bitCount++;
    provideCapacity(bitCount);

    if(value) setBit(value, newIndex);
}

void BitSequence::prepend(const Bit& value){
    BitSequence result(bitCount + 1);

    for(size_t i = 0; i < bitCount; ++i){
        result.setBit(getBit(i), i + 1);
    }
    result.setBit(value, 0);

    *this = result;
}

BitSequence BitSequence::operator&(const BitSequence& other){
    if(bitCount != other.bitCount) throw InvalidBitSequenceLength();
    BitSequence result(bitCount);

    for (size_t i = 0; i < data.getSize(); ++i) {
        uint8_t val = data.get(i) & other.data.get(i);
        result.data.set(i, val);
    }

    return result;
}

BitSequence BitSequence::operator|(const BitSequence& other){
    if(bitCount != other.bitCount) throw InvalidBitSequenceLength();
    BitSequence result(bitCount);

    for (size_t i = 0; i < data.getSize(); ++i) {
        uint8_t val = data.get(i) | other.data.get(i);
        result.data.set(i, val);
    }

    return result;
}

BitSequence BitSequence::operator^(const BitSequence& other){
    if(bitCount != other.bitCount) throw InvalidBitSequenceLength();
    BitSequence result(bitCount);

    for (size_t i = 0; i < data.getSize(); ++i) {
        uint8_t val = data.get(i) ^ other.data.get(i);
        result.data.set(i, val);
    }

    return result;
}

BitSequence BitSequence::operator~(){
    BitSequence result(bitCount);

    for (size_t i = 0; i < data.getSize(); ++i) {
        uint8_t val = ~data.get(i);
        result.data.set(i, val);
    }

    if(size_t validBits = bitCount % 8; validBits != 0){

        uint8_t mask = static_cast<uint8_t>((1 << validBits) - 1);
        size_t lastByte = result.data.getSize() - 1;
        uint8_t current = result.data.get(lastByte);
        result.data.set(lastByte, current & mask);

    }

    return result;
}