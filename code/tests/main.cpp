#include <gtest/gtest.h>

#include "quicksort.h"
#include "utils.h"

/**
 * @brief test Generates a random sequence of specified size and sorts it with Quicksort using N threads.
 * @param nbThreads number of threads to use to sort the sequence
 * @param size of the sequence to sort
 * @param seed to use for the random generation of the sequence
 */
void test(int nbThreads, int size, int seed) {
    Quicksort<int> sorter(nbThreads);
    std::vector<int> array = generateSequence(size, seed);
    sorter.sort(array);
    EXPECT_FALSE(array.empty());  // check that the result is not empty
    EXPECT_TRUE(isSorted(array)); // check that result is sorted
}

/**
 * @brief testSortedArray Verifies that a sorted array remains sorted.
 * @param nbThreads number of threads to use
 * @param size of the sequence
 */
void testSortedArray(int nbThreads, int size) {
    Quicksort<int> sorter(nbThreads);
    std::vector<int> array = generateSortedSequence(size);
    sorter.sort(array);
    EXPECT_FALSE(array.empty());  // check that the result is not empty
    EXPECT_TRUE(isSorted(array)); // array should remain sorted
}


TEST(SortingTest, SingleThreadSmallArray) {
    test(1, 10, 42);
}

TEST(SortingTest, MultiThreadSmallArray) {
    test(4, 10, 42);
}

TEST(SortingTest, SingleThreadLargeArray) {
    test(1, 10000, 42);
}

TEST(SortingTest, MultiThreadLargeArray) {
    test(8, 10000, 42);
}

TEST(SortingTest, AlreadySortedArray) {
    testSortedArray(4, 1000);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
