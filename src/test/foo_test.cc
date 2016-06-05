
#include <cmath>

#include "gtest/gtest.h"
#include "foo.h"

// basic functions test
TEST(SingleSqrtTest, Positive) {
  EXPECT_EQ(1.0, s_sqrt(1.0)); 
  EXPECT_EQ(0.5, s_sqrt(0.25));
}

TEST(SingleSqrtTest, ZeroAndNegative) {
  EXPECT_EQ(0.0, s_sqrt(0.0));
  // GTEST will fail on this test case
  // EXPECT_EQ(nan("NAN"), s_sqrt(-100.0));
}

TEST(DoubleSqrtTest, Positive) {
  EXPECT_EQ(1.0, d_sqrt(1.0)); 
  EXPECT_EQ(0.5, d_sqrt(0.25));
  EXPECT_EQ(50.332, d_sqrt(2533.310224));
}

TEST(DoubleSqrtTest, ZeroAndNegative) {
  EXPECT_EQ(0.0, d_sqrt(0.0));
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
