#include "gtest/gtest.h"
#include "../include/utilities.h"
#include <cmath>

// Use a fixture to set up the Utilities instance
class UtilitiesTest : public ::testing::Test
{
protected:
  Utilities u;
};

// test of findMedian

// Test case: find median of an empty list
TEST_F(UtilitiesTest, FindMedianEmptyList)
{
  std::vector<double> list;
  EXPECT_EQ(u.findMedian(list), 0.0); // Expecting median to be 0.0
}

// Test case: find median of a list with a single element
TEST_F(UtilitiesTest, FindMedianSingleElementList)
{
  std::vector<double> list = {4.0};
  EXPECT_EQ(u.findMedian(list), 4.0); // Expecting median to be 4.0
}

// Test case: find median of a list with an even number of elements
TEST_F(UtilitiesTest, FindMedianEvenSizeList)
{
  std::vector<double> list = {4.0, 7.0};
  EXPECT_EQ(u.findMedian(list), 5.5); // Expecting median to be 5.5
}

// Test case: find median of a list with an odd number of elements
TEST_F(UtilitiesTest, FindMedianOddSizeList)
{
  std::vector<double> list = {4.0, 7.0, 20000.0};
  EXPECT_EQ(u.findMedian(list), 7.0); // Expecting median to be 7.0
}

// Test case: find median of a list with duplicate elements
TEST_F(UtilitiesTest, FindMedianDuplicateElements)
{
  std::vector<double> list = {4.0, 4.0, 4.0, 4.0};
  EXPECT_EQ(u.findMedian(list), 4.0); // Expecting median to be 4.0
}

// Test case: find median of a list with mixed signs
TEST_F(UtilitiesTest, FindMedianMixedSigns)
{
  std::vector<double> list = {-1.0, 2.5, -5.0, 3.0, -2.0};
  EXPECT_EQ(u.findMedian(list), -1.0); // Expecting median to be -1.0
}

// Test case: find median of a list with floating-point numbers
TEST_F(UtilitiesTest, FindMedianFloatingPointNumbers)
{
  std::vector<double> list = {1.1, 2.2, 3.3, 4.4, 5.5};
  EXPECT_EQ(u.findMedian(list), 3.3); // Expecting median to be 3.3
}

// Test case: find median of a large list
TEST_F(UtilitiesTest, FindMedianLargeList)
{
  std::vector<double> list;
  const int size = 1000000;
  for (int i = 0; i < size; ++i)
  {
    list.push_back(static_cast<double>(i));
  }
  EXPECT_EQ(u.findMedian(list), (size - 1) / 2.0); // Expecting median to be (size - 1) / 2
}

// Test case: find median of a list with the smallest possible value
TEST_F(UtilitiesTest, FindMedianSmallestValue)
{
  std::vector<double> list = {std::numeric_limits<double>::lowest()};
  EXPECT_EQ(u.findMedian(list), std::numeric_limits<double>::lowest()); // Expecting median to be the lowest value
}

// Test case: find median of a list with the largest possible value
TEST_F(UtilitiesTest, FindMedianLargestValue)
{
  std::vector<double> list = {std::numeric_limits<double>::max()};
  EXPECT_EQ(u.findMedian(list), std::numeric_limits<double>::max()); // Expecting median to be the largest value
}

// Test cases for countInversionsWithMergeSort

// Test with no inversions
TEST_F(UtilitiesTest, HandlesNoInversions)
{
  std::vector<std::pair<double, double>> arr = {{1.0, 1.0}, {2.0, 2.0}, {3.0, 3.0}};
  size_t count = u.countInversionsWithMergeSort(arr, 0, arr.size());
  EXPECT_EQ(count, 0); // A sorted array should have no inversions
}

// Test with a single inversion
TEST_F(UtilitiesTest, HandlesSingleInversion)
{
  std::vector<std::pair<double, double>> arr = {{2.0, 2.0}, {1.0, 1.0}, {3.0, 3.0}};
  size_t count = u.countInversionsWithMergeSort(arr, 0, arr.size());
  EXPECT_EQ(count, 1); // This array should have one inversion
}

// Test with multiple inversions
TEST_F(UtilitiesTest, HandlesMultipleInversions)
{
  std::vector<std::pair<double, double>> arr = {{3.0, 3.0}, {2.0, 2.0}, {1.0, 1.0}};
  size_t count = u.countInversionsWithMergeSort(arr, 0, arr.size());
  EXPECT_EQ(count, 3); // This array should have three inversions
}

// Test with empty array
TEST_F(UtilitiesTest, HandlesEmptyArray)
{
  std::vector<std::pair<double, double>> arr;
  size_t count = u.countInversionsWithMergeSort(arr, 0, arr.size());
  EXPECT_EQ(count, 0); // An empty array should have no inversions
}

// Test with single element array
TEST_F(UtilitiesTest, HandlesSingleElementArray)
{
  std::vector<std::pair<double, double>> arr = {{1.0, 1.0}};
  size_t count = u.countInversionsWithMergeSort(arr, 0, arr.size());
  EXPECT_EQ(count, 0); // An array with a single element should have no inversions
}

// Test with an array having identical elements
TEST_F(UtilitiesTest, HandlesIdenticalElements)
{
  std::vector<std::pair<double, double>> arr = {{1.0, 1.0}, {1.0, 1.0}, {1.0, 1.0}};
  size_t count = u.countInversionsWithMergeSort(arr, 0, arr.size());
  EXPECT_EQ(count, 0); // An array with identical elements should have no inversions
}

// Test with a large array
TEST_F(UtilitiesTest, HandlesLargeArray)
{
  std::vector<std::pair<double, double>> arr;
  for (int i = 100000; i >= 1; --i)
  {
    arr.push_back({static_cast<double>(i), static_cast<double>(i)});
  }
  size_t count = u.countInversionsWithMergeSort(arr, 0, arr.size());
  EXPECT_EQ(count, static_cast<size_t>(arr.size() * (arr.size() - 1) / 2)); // A reverse sorted array should have maximum inversions
}

// Test cases for kendall_tau

// Test with identical vectors
TEST_F(UtilitiesTest, KendallTauHandlesIdenticalVectors) {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {1.0, 2.0, 3.0, 4.0, 5.0};
    double tau = u.kendall_tau(x, y);
    EXPECT_NEAR(tau, 1.0, 1e-9); // Kendall's Tau of identical vectors should be 1
}

// Test with completely reversed vectors
TEST_F(UtilitiesTest, KendallTauHandlesReversedVectors) {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> y = {5.0, 4.0, 3.0, 2.0, 1.0};
    double tau = u.kendall_tau(x, y);
    EXPECT_NEAR(tau, -1.0, 1e-9); // Kendall's Tau of completely reversed vectors should be -1
}

// Test with vectors of different lengths
TEST_F(UtilitiesTest, KendallTauThrowsWhenDifferentLengths) {
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0};
    std::vector<double> y = {1.0, 2.0, 3.0, 4.0, 5.0};
    EXPECT_THROW(u.kendall_tau(x, y), std::invalid_argument); // Should throw std::invalid_argument
}

// Test with empty vectors
TEST_F(UtilitiesTest, KendallTauHandlesEmptyVectors) {
    std::vector<double> x = {};
    std::vector<double> y = {};
    double tau = u.kendall_tau(x, y);
    EXPECT_TRUE(std::isnan(tau)); // Kendall's Tau of empty vectors should be NaN
}

// Test with one-element vectors
TEST_F(UtilitiesTest, KendallTauHandlesOneElementVectors) {
    std::vector<double> x = {1.0};
    std::vector<double> y = {1.0};
    double tau = u.kendall_tau(x, y);
    EXPECT_TRUE(std::isnan(tau)); // Kendall's Tau of one-element vectors should be NaN
}

// Test with some random vectors
TEST_F(UtilitiesTest, KendallTauHandlesRandomVectors) {
    std::vector<double> x = {1.0, 3.0, 5.0, 7.0, 9.0};
    std::vector<double> y = {2.0, 4.0, 5.0, 8.0, 10.0};
    double tau = u.kendall_tau(x, y);
    EXPECT_NEAR(tau, 1.0, 1e-9); // Kendall's Tau should be calculated correctly
}
