
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <numeric>

using PermutationType = std::vector<int>;
using PermutationCol = std::vector<PermutationType>;

void generate_all_permutations_recursive(const PermutationType& in, size_t position, std::vector<bool>& chosen, PermutationType& current, PermutationCol& result)
{
   if (in.size() == current.size())
   {
      result.push_back(current);
      return;
   }

   for (size_t i = 0; i < chosen.size(); ++i)
   {
      if (chosen[i])
         continue;
      current.push_back(in[i]);
      chosen[i] = true;
      generate_all_permutations_recursive(in, i, chosen, current, result);
      current.pop_back();
      chosen[i] = false;
   }
}

// Generate all permutations of the given set
// Complexity is O(n!)
PermutationCol generate_all_permutations(const PermutationType& in)
{
   std::vector<bool> chosen(in.size(), false);
   PermutationType current;
   PermutationCol result;
   current.reserve(in.size());
   generate_all_permutations_recursive(in, 0, chosen, current, result);
   return result;
}

void sort_all(PermutationCol& result, PermutationCol& expected)
{
   std::sort(expected.begin(), expected.end());
   std::sort(result.begin(), result.end());
}

TEST(AllPermutationsTest, SimpleTest)
{
   auto res = generate_all_permutations({ 1, 2 });
   PermutationCol expected = { PermutationType{ 1, 2 }, PermutationType{ 2, 1 } };
   sort_all(res, expected);
   EXPECT_EQ(res, expected);
}

TEST(AllPermutationsTest, EmptyTest)
{
   auto res = generate_all_permutations({});
   PermutationCol expected = { { } };
   sort_all(res, expected);
   EXPECT_EQ(res, expected);
}

TEST(AllPermutationsTest, ThreeItemTest)
{
   auto res = generate_all_permutations({ 3, 2, 5 });
   PermutationCol expected = {
      PermutationType{ 3, 2, 5 }, PermutationType{ 3, 5, 2 }, PermutationType{2, 3, 5},
      PermutationType{2, 5, 3}, PermutationType{5, 3, 2}, PermutationType{5, 2, 3}
   };
   sort_all(res, expected);
   EXPECT_EQ(res, expected);
}

TEST(AllPermutationsTest, GigaTest)
{
   PermutationType in(8);
   std::iota(in.begin(), in.end(), 21);
   PermutationCol expected;
   expected.push_back(in);
   for(;std::next_permutation(in.begin(), in.end());)
   {
      expected.push_back(in);
   }

   auto res = generate_all_permutations(in);
   sort_all(res, expected);
   EXPECT_EQ(res, expected);
}
