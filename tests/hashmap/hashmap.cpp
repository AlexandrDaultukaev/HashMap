#include "hashmap.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <utility>

const int seed = 12;
const int num_elements = 100;

TEST(HashmapSuite, Test1) {
    srand(seed);
    HashMap<int, int, std::hash<int>> hm;
    for (int i = 0; i < num_elements; i++) {
        hm[1 + rand() % num_elements] = 1 + rand() % num_elements;
    }
    HashMap<int, int, std::hash<int>> hm2;
    hm2 = hm;

    EXPECT_EQ(hm2, hm);
    EXPECT_EQ(hm2 == hm, true);
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

TEST(HashmapSuite, TestCustomHashFunction) {

    struct Myhash {
        std::size_t operator()(const std::string &k) const {

            return std::hash<std::string>()(k) << 1U;
        }
    };

    HashMap<std::string, int, Myhash> hm;

    hm["31"] = 1;
    hm["32"] = 2;
    hm.set_value("33", 3);
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

TEST(HashmapSuite, TestGetFindValue) {

    HashMap<std::string, int> hm;

    hm["31"] = 1;
    hm["32"] = 2;
    hm["33"] = 3;
    EXPECT_EQ(hm.get_value("33"), 3);
    EXPECT_EQ(hm.get_value("34"), 0);
    EXPECT_EQ(*(hm.find_value("33")), 3);
    EXPECT_EQ(*(hm.find_value("34")), 0);
}

TEST(HashmapSuite, TestHashMapOnSTL) {

    HashMap<std::string, int> hm;

    hm["31"] = 1;
    hm["32"] = 2;
    hm["33"] = 3;
    auto result = std::find(
        hm.begin(), hm.end(), std::pair<const std::string, int>("32", 2));
    if (result != hm.end()) {
        EXPECT_EQ(result->first, "32");
        EXPECT_EQ(result->second, 2);
    } else {
        EXPECT_EQ(false, true);
    }
    result = std::find(
        hm.begin(), hm.end(), std::pair<const std::string, int>("32", 3));
    EXPECT_EQ(result, hm.end());
}
