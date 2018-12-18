#include <iostream>
#include "arvector.h"
#include "BinomialHeap.h"
#include <gtest/gtest.h>

using std::cin;
using std::cout;
using std::string;


TEST (HeapTest, EmptyTest) {
    BinomialHeap<int> a;
    EXPECT_THROW(a.get_min(), std::logic_error);
}

TEST (HeapTest, EmptyTest2) {
    BinomialHeap<int> a;
    EXPECT_THROW(a.extract_min(), std::logic_error);
}

TEST (HeapTest, SmallTest) {
    BinomialHeap<int> a;
    for (int i = 1; i <= 3; i += 2) {
        a.insert(i);
    }
    a.extract_min();
    EXPECT_EQ(a.get_min(), 3);
    a.insert(2);
    EXPECT_EQ(a.get_min(), 2);
}

TEST (HeapTest, EqualTest) {
    BinomialHeap<int> a;
    a.insert(1);
    a.insert(1);
    a.extract_min();
    EXPECT_EQ(a.extract_min(), 1);
}

TEST (HeapTest, LargeStressTest) {
    std::vector<int> b;
    std::multiset<int> c;
    BinomialHeap<int> a;
    const int TEST_SIZE = 10000;
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

TEST (HeapTest, MergeSmallTest){
    BinomialHeap <int> a, b;
    a.insert(2);
    b.insert(1);
    a.merge(&b);
    EXPECT_EQ(a.extract_min(), 1);
    EXPECT_EQ(a.extract_min(), 2);
}

TEST (HeapTest, MergeSpeedTest){
    BinomialHeap <int> a, b;
    for (int i = 1; i <= 100000; i++){
        if (i % 2 == 1){
            a.insert(i);
        }else{
            b.insert(i);
        }
    }
    b.merge(&a);
    for (int i = 1; i <= 100000; i++){
        EXPECT_EQ(b.extract_min(), i);
    }
}


TEST (HeapTest, LargeSpeedTest) {
    BinomialHeap<int> a;
    const int TEST_SIZE = 100000;
    for (int i = 0; i < TEST_SIZE; i++) {
        a.insert(rand());
    }
    for (int i = 0; i < TEST_SIZE; i++) {
        a.extract_min();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}