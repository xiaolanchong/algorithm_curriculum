
#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Array = std::vector<int>;

// Find a sequential subarray with the max item sum
// Assignment from the 1st chapter of Laaksonen Competitive Programming, but with a correct solution
int get_max_sum_subarray(const Array& in)
{
   if (in.empty())
      return 0;
   int bestSum = in[0];
   size_t bestSumEnding = 0;
   for (size_t i = 1; i < in.size(); ++i)
   {
      if (i == bestSumEnding + 1) // adjacent elements
      {
         const auto newSum = bestSum + in[i];
         if (newSum > bestSum)
         {
            bestSum = newSum;
            bestSumEnding = i;
         }
      }
      else if (bestSum < in[i])
      {
         bestSum = in[i];
         bestSumEnding = i;
      }
   }
   return bestSum;
}

TEST(MaxSumSubarrayTest, SimpleTest)
{
   EXPECT_EQ(6, get_max_sum_subarray({ 1, 2, 3, -5 }));
}

TEST(MaxSumSubarrayTest, EmptyTest)
{
   EXPECT_EQ(0, get_max_sum_subarray({}));
}

TEST(MaxSumSubarrayTest, LastElementTest)
{
   EXPECT_EQ(3, get_max_sum_subarray({ 1, -1, -5, 3}));
}

TEST(MaxSumSubarrayTest, FirstElementTest)
{
   EXPECT_EQ(10, get_max_sum_subarray({ 10, -1, -5, 3 }));
}
