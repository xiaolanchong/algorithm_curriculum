#include <vector>
#include <optional>
#include <gtest/gtest.h>

using Array = std::vector<unsigned int>;

struct Subarray
{
   size_t start;
   size_t end;
};

std::optional<Subarray> find_sum_subarray(const Array& array, size_t sum)
{
   if (array.empty())
      return std::nullopt;

   size_t currentSum = 0;
   for (size_t start = 0, end = 0;
      start < array.size() && end < array.size();)
   {
      while (end < array.size() && currentSum < sum)
      {
         currentSum += array[end];
         ++end;
      }
      if (sum == currentSum)
         return Subarray{start, end - 1};
      currentSum -= array[start];
      ++start;
   }

   return std::optional<Subarray>{};
}

TEST(GivenSumSubarrayTest, Test)
{
   std::optional<Subarray> res;

   res = find_sum_subarray({1, 15, 1, 2, 3, 2}, 6);
   EXPECT_TRUE(res.has_value());
   EXPECT_EQ(res.value_or(Subarray{0, 0}).start, 2);
   EXPECT_EQ(res.value_or(Subarray{ 0, 0 }).end, 4);

   res = find_sum_subarray({ 1, 15, 1, 2, 3, 2 }, 16);
   EXPECT_TRUE(res.has_value());
   EXPECT_EQ(res.value_or(Subarray{ 0, 0 }).start, 0);
   EXPECT_EQ(res.value_or(Subarray{ 0, 0 }).end, 1);

   res = find_sum_subarray({ 1, 15, 1, 2, 3, 2 }, 24);
   EXPECT_TRUE(res.has_value());
   EXPECT_EQ(res.value_or(Subarray{ 0, 0 }).start, 0);
   EXPECT_EQ(res.value_or(Subarray{ 0, 0 }).end, 5);

   res = find_sum_subarray({ 41, 15, 1, 2, 3, 2 }, 1);
   EXPECT_TRUE(res.has_value());
   EXPECT_EQ(res.value_or(Subarray{ 0, 0 }).start, 2);
   EXPECT_EQ(res.value_or(Subarray{ 0, 0 }).end, 2);

   res = find_sum_subarray({ 1, 15, 1, 2, 3, 2 }, 240);
   EXPECT_TRUE(!res.has_value());

   res = find_sum_subarray({ 11, 15, 12, 2, 3, 2 }, 1);
   EXPECT_TRUE(!res.has_value());
}
