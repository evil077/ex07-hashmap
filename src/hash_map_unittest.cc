// Copyright 2018, Allan Knight.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Allan Knight nor the names of other
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

// A unit tester for EX05-String in CS140 at Santa Barbara City College.
//
// Author: ahknight@pipeline.sbcc.edu (Allan Knight)


// Includes for google test and the unit under test.

#include <climits>
#include <random>
#include <chrono>

#include "hash_map.h"

#include "gtest/gtest.h"

namespace {

    using edu::vcccd::vc::csv15::HashMap;

// Tests edu::sbcc:cs140::String.

    using std::string;

    using namespace ::testing_internal;

    typedef uint64_t uint;

    class HashMapTest : public ::testing::Test {
    protected:
        static const uint MAX_TESTED_SCORE = 20;
        static const uint MAX_OVERALL_SCORE = 25;
        static uint _testScore;

    protected:
        static void TearDownTestCase() {
            if (_testScore == MAX_TESTED_SCORE) {
                std::cout << std::endl << "Your unit test score is "
                          << _testScore << " out of "
                          << MAX_TESTED_SCORE << std::endl;
            } else {
                std::cout << "Your unit test score is "
                          << _testScore << " out of "
                          << MAX_TESTED_SCORE << " ("<< (int)(_testScore - MAX_TESTED_SCORE)
                          << ")" << std::endl;
            }

            std::cout << "The assignment is worth a total of " << MAX_OVERALL_SCORE
                      << " where the remaining points" << std::endl;
            std::cout << "comes from grading related to documentation, algorithms, and other"
                      << std::endl;
            std::cout << "criteria." << std::endl << std::endl;
        }
    };

    uint HashMapTest::_testScore = 0;

    TEST_F(HashMapTest, Construction) {
    // This test is named "Identity", it checks that the basic identity
    // complex number, i, has the correct values for real and imaginary
    // parts.

    HashMap<std::string, uint> map1;
    ASSERT_EQ(0, map1.size());
    ASSERT_TRUE(map1.empty());
    _testScore += 1;

    HashMap<std::string, uint> map2(map1);
    ASSERT_EQ(0, map2.size());
    ASSERT_TRUE(map2.empty());
    _testScore += 1;

    map1["test"] = 1;
    ASSERT_EQ(1, map1.size());
    ASSERT_EQ(0, map2.size());

    _testScore += 1;

    HashMap<std::string, uint> map3(map1);
    ASSERT_EQ(1, map1.size());
    ASSERT_EQ(1, map3.size());
    ASSERT_EQ(0, map2.size());
    ASSERT_EQ(1, map3["test"]);
    _testScore += 1;
}

TEST_F(HashMapTest, InsertFind) {
        HashMap<std::string, int> map1;
        ASSERT_TRUE(map1.empty());
        map1["key"] = 1;
        ASSERT_EQ(1, map1["key"]);
        ASSERT_EQ(1, map1.size());
        ASSERT_FALSE(map1.empty());
        _testScore += 1;

        map1["key"] = 2;
        ASSERT_EQ(2, map1["key"]);
        ASSERT_EQ(1, map1.size());
        _testScore += 1;

        auto found = map1.find("key");
        ASSERT_EQ(2, found->second);

        _testScore += 1;

        auto notFound = map1.find("test");
        ASSERT_EQ(map1.end(), notFound);

        _testScore += 1;

        map1.insert("test",  4);
        ASSERT_EQ(4, map1["test"]);

        _testScore += 1;
    }

    TEST_F(HashMapTest, Erase) {
        HashMap<std::string, uint> map1;
        map1["key"] = 1;
        map1["test"] = 2;
        ASSERT_EQ(2, map1.size());

        map1.erase(map1.find("key"));
        ASSERT_EQ(1, map1.size());
        ASSERT_EQ(map1.end(), map1.find("key"));
        ASSERT_EQ(2, map1["test"]);

        _testScore += 1;

        map1.clear();
        ASSERT_EQ(0, map1.size());
        ASSERT_EQ(map1.end(), map1.find("key"));
        ASSERT_EQ(map1.end(), map1.find("test"));

        _testScore += 1;

        map1["test1"] = 10;
        map1["key1"] = 11;
        ASSERT_EQ(10, map1["test1"]);
        map1.erase(map1.begin(), map1.begin()++);
        ASSERT_EQ(1, map1.size());
        ASSERT_EQ(11, map1["key1"]);
        ASSERT_EQ(map1.end(), map1.find("test1"));

        _testScore += 1;

        ASSERT_EQ(0, map1.erase("test1"));
        ASSERT_EQ(1, map1.erase("key1"));
        ASSERT_EQ(0, map1.size());
        ASSERT_TRUE(map1.empty());

        _testScore += 1;

    }

    TEST_F(HashMapTest, Swap) {
        HashMap<std::string, uint> map1, map2;
        map1["key"] = 12;
        ASSERT_EQ(1, map1.size());
        ASSERT_EQ(0, map2.size());
        map1.swap(map2);
        ASSERT_EQ(0, map1.size());
        ASSERT_EQ(1, map2.size());
        ASSERT_EQ(12, map2["key"]);
        ASSERT_EQ(map1.end(), map1.find("key"));
        _testScore += 2;
    }

    TEST_F(HashMapTest, Rehash) {
        HashMap<size_t, size_t> map;
        size_t capacity = map.bucket_count();
        for (size_t i = 0; i < capacity + 1; i++) {
            map[i] = i;
        }
        ASSERT_EQ(capacity+1, map.size());
        ASSERT_LT(capacity+1, map.bucket_count());
        _testScore += 2;
        for (auto kp = map.begin(); kp != map.end(); kp++)  {
            ASSERT_EQ(kp->first, kp->second);
        }
        _testScore += 3;
    }
}