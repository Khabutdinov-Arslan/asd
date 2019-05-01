#include <iostream>
#include <gtest/gtest.h>
#include "arvector.h"
#include "arheap.h"
#include <string>
#include <vector>
#include <set>

using std::cin;
using std::cout;
using std::string;

TEST (VectorTest, SmallAddTest){
    Vector <int> a;
    for (int i = 1; i <= 10; i++){
        a.push_back(i);
    }
    for (int i = 0; i < 10; i++){
        EXPECT_EQ(a[i], i + 1);
    }
}

TEST (VectorTest, BadPopTest){
    Vector <int> a;
    ASSERT_THROW(a.pop_back(), std::logic_error);
}

TEST (VectorTest, BadIndexTest){
    Vector <int> a;
    a.push_back(1);
    a.push_back(2);
    ASSERT_THROW(a[2], std::out_of_range);
}

TEST (VectorTest, BadChangeTest){
    Vector <int> a;
    a.push_back(1);
    a.push_back(2);
    a.pop_back();
    ASSERT_THROW(a.change(0, 1), std::out_of_range);
}

TEST (VectorTest, LargeStabilityTest){
    Vector <int> a;
    std::vector <int> b;
    const int TEST_SIZE = 1000000;
    for (int i = 0; i < TEST_SIZE; i++){
        int cur = rand();
        a.push_back(cur);
        b.push_back(cur);
        EXPECT_EQ(a[i], b[i]);
    }
    for (int i = TEST_SIZE - 2; i > 0; i--){
        a.pop_back();
        b.pop_back();
        EXPECT_EQ(a[i], b[i]);
    }
    EXPECT_EQ(a.get_size(), 2);
}

TEST (HeapTest, EmptyTest){
    Heap <int> a;
    EXPECT_THROW(a.get_min(), std::logic_error);
}

TEST (HeapTest, SmallTest){
    Heap <int> a;
    for (int i = 1; i <= 3; i += 2){
        a.insert(i);
    }
    a.extract_min();
    EXPECT_EQ(a.get_min(), 3);
    a.insert(2);
    EXPECT_EQ(a.get_min(), 2);
}

TEST (HeapTest, LargeStressTest){
    std::vector <int> b;
    std::multiset <int> c;
    const int TEST_SIZE = 1000000;
    for (int i = 0; i < TEST_SIZE; i++){
        b.push_back(rand());
        c.insert(b[i]);
    }
    Heap <int> a(b.begin(), b.end());
    for (int i = 0; i < TEST_SIZE; i++){
        int r1 = a.get_min(), r2 = *c.begin();
        EXPECT_EQ(r1, r2);
        a.extract_min();
        c.erase(c.begin());
    }
}

TEST (HeapTest, MassConstructorSpeedTest){
    const int TEST_SIZE = 1000000;
    int b[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; i++){
        b[i] = rand();
    }
    Heap <int> a(b, b + TEST_SIZE);
}

TEST (HeapTest, ConstructorSpeedTest){
    const int TEST_SIZE = 1000000;
    int b[TEST_SIZE];
    for (int i = 0; i < TEST_SIZE; i++){
        b[i] = rand();
    }
    Heap <int> a(b, b + TEST_SIZE);
}

TEST (HeapTest, LargeSpeedTest){
    Heap <int> a;
    const int TEST_SIZE = 1000000;
    for (int i = 0; i < TEST_SIZE; i++){
        a.insert(rand());
    }
}

int main(int argc, char **argv){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}