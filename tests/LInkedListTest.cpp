#include <gtest/gtest.h>
#include "LinkedList.hpp"


TEST(LinkedListTest, DefaultConstructor){
    LinkedList<int> list;
    EXPECT_EQ(list.getLength(), 0);
}

TEST(LinkedListTest, ConstructorWithArray){
    int a[] = {1, 2, 3, 4};
    LinkedList<int> list(a, 4);
    EXPECT_EQ(list.getLength(), 4);
    EXPECT_EQ(list.get(3), 4);
}

TEST(LinkedListTest, AppendAndGet) {
    LinkedList<int> list;
    list.append(42);
    list.append(100);
    
    EXPECT_EQ(list.get(0), 42);
    EXPECT_EQ(list.get(1), 100);
}

TEST(LinkedListTest, OutOfRange) {
    LinkedList<int> list;
    
    EXPECT_THROW(list.get(3), IndexOutOfRange);
}

TEST(LinkedListTest, CopyConstructor) {
    LinkedList<int> original;
    original.append(1);
    original.append(12);
    original.append(23);
    
    LinkedList<int> copy(original);
    
    EXPECT_EQ(copy.getLength(), 3);
    EXPECT_EQ(copy.get(0), 1);
    EXPECT_EQ(copy.get(1), 12);
    EXPECT_EQ(copy.get(2), 23);
}



