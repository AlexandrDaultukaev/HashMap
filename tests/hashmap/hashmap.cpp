#include "hashmap.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <utility>
TEST(HashmapSuite, Test1) {
    srand(12);
    HashMap<int, int> hm;
    for (int i = 0; i < 100; i++) {
        hm[1 + rand() % 100] = 1 + rand() % 100;
    }
    HashMap<int, int> hm2;
    hm2 = hm;

    EXPECT_EQ(hm2, hm);
}

TEST(HashmapSuite, Test2) {
    HashMap<std::string, int> hm;
    hm["31"] = 1;
    hm["32"] = 2;
    hm["33"] = 3;
    for (Iterator<std::string, int> it = hm.begin(); it != hm.end(); it++) {
        if (it->second == 1) {
            EXPECT_EQ(it->first, "31");
        } else if (it->second == 2) {
            EXPECT_EQ(it->first, "32");
        } else if (it->second == 3) {
            EXPECT_EQ(it->first, "33");
        } else {
            // Если вдруг итератор нам принёс мусорное значение
            EXPECT_EQ(false, true);
        }
    }
}
