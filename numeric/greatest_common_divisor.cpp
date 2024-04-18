#include <vector>
#include <algorithm>
#include <numeric>
#include <gtest/gtest.h>

int gcd(int a, int b)
{
   auto minVal = std::min(a, b);
   auto maxVal = std::max(a, b);
   for (; minVal != 0;)
   {
      auto reminder = maxVal % minVal;
      maxVal = minVal;
      minVal = reminder;
   }
   return maxVal;
}

TEST(GcdTest, Test)
{
   EXPECT_EQ(gcd(50, 15), 5);
   EXPECT_EQ(gcd(15, 50), 5);
   EXPECT_EQ(gcd(8, 8), 8);
   EXPECT_EQ(gcd(1, 1), 1);
   EXPECT_EQ(gcd(80, 0), 80);
   EXPECT_EQ(gcd(0, 80), 80);
   EXPECT_EQ(gcd(80, -15), 5);
   EXPECT_EQ(gcd(-80, -15), -5);
}
