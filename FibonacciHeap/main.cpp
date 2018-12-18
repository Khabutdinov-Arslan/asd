#include <iostream>
#include "FibonacciHeap.h"
#include <gtest/gtest.h>

TEST (HeapTest, EmptyTest) {
    FibonacciHeap<int> a;
    EXPECT_THROW(a.get_min(), std::logic_error);
}

TEST (HeapTest, EmptyTest2) {
    FibonacciHeap<int> a;
    EXPECT_THROW(a.extract_min(), std::logic_error);
}

TEST (HeapTest, EqualTest) {
    FibonacciHeap<int> a;
    a.insert(1);
    a.insert(1);
    a.extract_min();
    EXPECT_EQ(a.extract_min(), 1);
}


TEST (HeapTest, LargeStressTest) {
    std::vector<int> b;
    std::multiset<int> c;
    FibonacciHeap<int> a;
    const int TEST_SIZE = 100000;
    for (int i = 0; i < TEST_SIZE; i++) {
        b.push_back(rand());
        c.insert(b[i]);
        a.insert(b[i]);
    }
    for (int i = 0; i < TEST_SIZE; i++) {
        int r1 = a.get_min(), r2 = *c.begin();
        EXPECT_EQ(r1, r2);
        a.extract_min();
        c.erase(c.begin());
    }
}


TEST (HeapTest, LargeSpeedTest) {
    FibonacciHeap<int> a;
    const int TEST_SIZE = 10;
    for (int i = 0; i < TEST_SIZE; i++) {
        a.insert(rand());
    }
    for (int i = 0; i < TEST_SIZE; i++) {
        a.extract_min();
    }
}

TEST (HeapTest, DecreaseKeyIsEmptyTest) {
    FibonacciHeap<int> a;
    Pointer<int> i1 = a.insert(3);
    Pointer<int> i2 = a.insert(4);
    a.insert(3);
    a.decrease_node_key(i1, 2);
    EXPECT_EQ(2, a.extract_min());
    a.decrease_node_key(i2, 1);
    EXPECT_EQ(1, a.extract_min());
    EXPECT_EQ(0, a.is_empty());
    a.extract_min();
    EXPECT_EQ(1, a.is_empty());
}

TEST (HeapTest, MergeSmallTest){
    FibonacciHeap <int> a, b;
    a.insert(2);
    b.insert(1);
    a.merge(b);
    EXPECT_EQ(a.extract_min(), 1);
    EXPECT_EQ(a.extract_min(), 2);
}

TEST (HeapTest, MergeSpeedTest){
    FibonacciHeap <int> a, b;
    for (int i = 1; i <= 100000; i++){
        if (i % 2 == 1){
            a.insert(i);
        }else{
            b.insert(i);
        }
    }
    b.merge(a);
    for (int i = 1; i <= 100000; i++){
        EXPECT_EQ(b.extract_min(), i);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}