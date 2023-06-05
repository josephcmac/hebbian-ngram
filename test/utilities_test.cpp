#include "gtest/gtest.h"
#include "../include/utilities.h"

TEST(UtilitiesTest, testFindMedian) {
  Utilities u; // Create an instance of Utilities
  
  std::vector<double> list = {};
  EXPECT_EQ(u.findMedian(list), 0.0);

  list = {4.0};
  EXPECT_EQ(u.findMedian(list), 4.0);

  list = {4.0, 7.0};
  EXPECT_EQ(u.findMedian(list), (4.0 + 7.0)/2);

  list = {4.0, 7.0, 20000.0};
  EXPECT_EQ(u.findMedian(list), 7.0);
}
