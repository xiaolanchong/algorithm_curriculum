#include <deque>
#include <algorithm>
#include <numeric>
#include <gtest/gtest.h>

/*
Laaksonen, chapter 6
пусть дан список весов [w1, w2, …, wn],
требуется найти все суммы, которые можно получить сложением весов.

*/

using Weight = size_t;
using Weights = std::vector<size_t>;

Weights get_all_sum_weights(Weights weights)
{
   const auto totalSum = std::accumulate(weights.cbegin(), weights.cend(), size_t(0));
   const unsigned int no = 0;
   const unsigned int yes = 1;
   std::vector<unsigned int> possible(totalSum + 1, no); // vector<bool> is specialized
   possible[0] = yes;
   for (size_t k = 0; k < weights.size(); k++)
   {
      for (ptrdiff_t x = totalSum - weights[k]; x >= 0; x--)
      {
         possible[x + weights[k]] |= possible[x];
      }
   }

   Weights allSums;
   allSums.reserve(possible.size());
   for (size_t i = 0; i < possible.size(); ++i)
   {
      if (possible[i] == yes)
         allSums.push_back(i);
   }
   return allSums;
}

TEST(KnapsackWeightTest, Test)
{
   Weights w = { 1, 3, 3, 5 };
   EXPECT_EQ(get_all_sum_weights(w), Weights({0, 1, 3, 4, 5, 6, 7, 8, 9, 11, 12}));

   EXPECT_EQ(get_all_sum_weights({}), Weights({0}));
}
