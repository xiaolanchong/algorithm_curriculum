#include <vector>
#include <gtest/gtest.h>

using Array = std::vector<int>;

void merge(Array& in, Array& helper, ptrdiff_t low, ptrdiff_t middle, ptrdiff_t high)
{
   /* Copy both halves into a helper array */
   for (ptrdiff_t i = low; i <= high; i++)
   {
      helper[i] = in[i];
   }

   ptrdiff_t helperLeft = low;
   ptrdiff_t helperRight = middle + 1;
   ptrdiff_t current = low;
   /* 
   Iterate through helper array. Compare the left and right * half, 
   copying back the smaller element from the two halves * into the original array.
   */

   while (helperLeft <= middle && helperRight <= high)
   {
      if (helper[helperLeft] <= helper[helperRight])
      {
         in[current] = helper[helperLeft];
         helperLeft++;
      }
      else
      { // If right element is smaller than left element 
         in[current] = helper [helperRight];
         helperRight++;
      }
      current++;
   }

   // Copy the rest of the left side of the array into the target array.
   // The right half doesn't need to be copied, already there.
   ptrdiff_t remaining = middle - helperLeft;
   for (ptrdiff_t i = 0; i <= remaining; ++i)
   {
      in[current + i] = helper[helperLeft + i];
   }
}

void merge_sort(Array& in, Array& helper, ptrdiff_t low, ptrdiff_t high)
{
   if (low >= high)
      return;
   ptrdiff_t middle = (low + high) / 2;
   merge_sort(in, helper, low, middle); // Sort left half 
   merge_sort (in, helper, middle+1, high); // Sort right half
   merge(in, helper, low, middle, high); // Merge them
}

void merge_sort(Array& in)
{
   Array helper(in.size());
   merge_sort(in, helper, 0, in.size() - 1);
}

TEST(MergeSortTest, SimpleTest)
{
   Array in = { 2, 4, 0, 5, -1 };
   merge_sort(in);
   EXPECT_EQ(in, Array({ -1, 0, 2, 4, 5 }));
}

TEST(MergeSortTest, EmptyTest)
{
   Array in;
   merge_sort(in);
   EXPECT_EQ(in, Array({}));
}

TEST(MergeSortTest, OneElementTest)
{
   Array in = { 1 };
   merge_sort(in);
   EXPECT_EQ(in, Array({1}));
}

TEST(MergeSortTest, ReversedTest)
{
   Array in = { 10, 8, 6, 4, 2, 0 };
   merge_sort(in);
   EXPECT_EQ(in, Array({ 0, 2, 4, 6, 8, 10 }));
}

TEST(MergeSortTest, AlreadySortedTest)
{
   Array in = { 0, 2, 4, 6, 8, 10 };
   merge_sort(in);
   EXPECT_EQ(in, Array({ 0, 2, 4, 6, 8, 10 }));
}
