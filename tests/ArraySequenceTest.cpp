#include <gtest/gtest.h>
#include "Sequence.hpp"



TEST(ArraySequenceTest, DefaultConstructor){
    ArraySequence<int> list;
    EXPECT_EQ(list.getLength(), 0);
}

TEST(ArraySequenceTest, ConstructorWithArray){
    int a[] = {1, 2, 3, 4};
    ArraySequence<int> list(a, 4);
    EXPECT_EQ(list.getLength(), 4);
    EXPECT_EQ(list.get(3), 4);
}

TEST(ArraySequenceTest, ConstructorWithInitializeList){
    ArraySequence<int> list({1, 2, 3, 4});
    EXPECT_EQ(list.getLength(), 4);
    EXPECT_EQ(list.get(3), 4);
}

TEST(ArraySequenceTest, AppendAndGet) {
    ArraySequence<int> list;
    list.append(42);
    list.append(100);
    
    EXPECT_EQ(list.get(0), 42);
    EXPECT_EQ(list.get(1), 100);
}

TEST(ArraySequenceTest, PrependAndGet) {
    ArraySequence<int> list;
    list.prepend(42);
    list.prepend(100);
    
    EXPECT_EQ(list.get(1), 42);
    EXPECT_EQ(list.get(0), 100);
}

TEST(ArraySequenceTest, AppendAndOperator) {
    ArraySequence<int> list;
    list.append(42);
    list.append(100);
    
    EXPECT_EQ(list[0], 42);
    EXPECT_EQ(list[1], 100);
}

TEST(ArraySequenceTest, PrependAndOperator) {
    ArraySequence<int> list;
    list.prepend(42);
    list.prepend(100);
    
    EXPECT_EQ(list[1], 42);
    EXPECT_EQ(list[0], 100);
}

TEST(ArraySequenceTest, OutOfRange) {
    ArraySequence<int> list;
    
    EXPECT_THROW(list.get(3), IndexOutOfRange);
}

TEST(ArraySequenceTest, CopyConstructor) {
    ArraySequence<int> original;
    original.append(1);
    original.append(12);
    original.append(23);
    
    ArraySequence<int> copy(original);
    
    EXPECT_EQ(copy.getLength(), 3);
    EXPECT_EQ(copy.get(0), 1);
    EXPECT_EQ(copy.get(1), 12);
    EXPECT_EQ(copy.get(2), 23);
}

TEST(ArraySequenceTest, GetFirstAndGetLast) {
    ArraySequence<int> arraySeq;
    arraySeq.append(1);
    arraySeq.append(12);
    arraySeq.append(23);

    
    EXPECT_EQ(arraySeq.getLength(), 3);
    EXPECT_EQ(arraySeq.getFirst(), 1);
    EXPECT_EQ(arraySeq.getLast(), 23);
    
}

TEST(ArraySequenceTest, StringDefaultConstructor){
    ArraySequence<std::string> list;
    EXPECT_EQ(list.getLength(), 0);
}

TEST(ArraySequenceTest, StringConstructorWithArray){
    std::string a[] = {"1", "2", "3", "4"};
    ArraySequence<std::string> list(a, 4);
    EXPECT_EQ(list.getLength(), 4);
    EXPECT_EQ(list.get(3), "4");
}

TEST(ArraySequenceTest, StringConstructorWithInitializeList){
    ArraySequence<std::string> list({"1", "2", "3", "4"});
    EXPECT_EQ(list.getLength(), 4);
    EXPECT_EQ(list.get(3), "4");
}

TEST(ArraySequenceTest, StringAppendAndGet) {
    ArraySequence<std::string> list;
    list.append("42");
    list.append("100");
    
    EXPECT_EQ(list.get(0), "42");
    EXPECT_EQ(list.get(1), "100");
}

TEST(ArraySequenceTest, StringPrependAndGet) {
    ArraySequence<std::string> list;
    list.prepend("42");
    list.prepend("100");
    
    EXPECT_EQ(list.get(1), "42");
    EXPECT_EQ(list.get(0), "100");
}

TEST(ArraySequenceTest, StringAppendAndOperator) {
    ArraySequence<std::string> list;
    list.append("42");
    list.append("100");
    
    EXPECT_EQ(list[0], "42");
    EXPECT_EQ(list[1], "100");
}

TEST(ArraySequenceTest, StringPrependAndOperator) {
    ArraySequence<std::string> list;
    list.prepend("42");
    list.prepend("100");
    
    EXPECT_EQ(list[1], "42");
    EXPECT_EQ(list[0], "100");
}

TEST(ArraySequenceTest, StringOutOfRange) {
    ArraySequence<std::string> list;
    
    EXPECT_THROW(list.get(3), IndexOutOfRange);
}

TEST(ArraySequenceTest, StringCopyConstructor) {
    ArraySequence<std::string> original;
    original.append("1");
    original.append("12");
    original.append("23");
    
    ArraySequence<std::string> copy(original);
    
    EXPECT_EQ(copy.getLength(), 3);
    EXPECT_EQ(copy.get(0), "1");
    EXPECT_EQ(copy.get(1), "12");
    EXPECT_EQ(copy.get(2), "23");
}

TEST(ArraySequenceTest, StringGetFirstAndgetLast) {
    ArraySequence<std::string> arraySeq;
    arraySeq.append("1");
    arraySeq.append("12");
    arraySeq.append("23");

    
    EXPECT_EQ(arraySeq.getLength(), 3);
    EXPECT_EQ(arraySeq.getFirst(), "1");
    EXPECT_EQ(arraySeq.getLast(), "23");
    
}
