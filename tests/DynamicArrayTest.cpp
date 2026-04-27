#include <gtest/gtest.h>
#include "DynamicArray.hpp"

TEST(DynamicArrayTest, DefaultConstructor) {
    DynamicArray<int> arr;
    EXPECT_EQ(arr.getSize(), 0);
}

TEST(DynamicArrayTest, ConstructorWithSize) {
    DynamicArray<int> arr(10);
    EXPECT_EQ(arr.getSize(), 10);
}

// TEST(LinkedListTest, ConstructorWithArray){
//     int a[] = {1, 2, 3, 4};
//     DynamicArray<int> arr(a, 4);
//     EXPECT_EQ(arr.getSize(), 4);
//     EXPECT_EQ(arr.get(3), 4);
// }

TEST(DynamicArrayTest, SetAndGet) {
    DynamicArray<int> arr(5);
    arr.set(0, 42);
    arr.set(4, 100);
    
    EXPECT_EQ(arr.get(0), 42);
    EXPECT_EQ(arr.get(4), 100);
}

TEST(DynamicArrayTest, OutOfRange) {
    DynamicArray<int> arr(3);
    
    EXPECT_THROW(arr.get(3), IndexOutOfRange);
    EXPECT_THROW(arr.set(5, 10), IndexOutOfRange);
}

TEST(DynamicArrayTest, CopyConstructor) {
    DynamicArray<int> original(3);
    original.set(0, 1);
    original.set(1, 2);
    original.set(2, 3);
    
    DynamicArray<int> copy(original);
    
    EXPECT_EQ(copy.getSize(), 3);
    EXPECT_EQ(copy.get(0), 1);
    EXPECT_EQ(copy.get(1), 2);
    EXPECT_EQ(copy.get(2), 3);
}

TEST(DynamicArrayTest, Resize) {
    DynamicArray<int> arr(3);
    arr.set(0, 10);
    arr.set(1, 20);
    arr.set(2, 30);
    
    arr.resize(5);
    EXPECT_EQ(arr.getSize(), 5);
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_EQ(arr.get(1), 20);
    EXPECT_EQ(arr.get(2), 30);
    
    arr.resize(2);
    EXPECT_EQ(arr.getSize(), 2);
    EXPECT_EQ(arr.get(0), 10);
    EXPECT_EQ(arr.get(1), 20);
}
