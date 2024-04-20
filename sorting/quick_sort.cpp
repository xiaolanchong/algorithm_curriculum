#include <vector>
#include <gtest/gtest.h>

using Array = std::vector<int>;

ptrdiff_t partition(Array& arr, ptrdiff_t left, ptrdiff_t right)
{
   if (left >= right)
      return left;
   ptrdiff_t pivot = arr[(left + right) / 2]; // Pick pivot point 
   while (left <= right)
   {
      // Find element on left that should be on right 
      while (arr[left] < pivot) left++;
      // Find element on right that should be on left 
      while (arr[right] > pivot) right--;
      // Swap elements, and move left and right indices
      if (left <= right)
      {
         std::swap(arr[left], arr[right]); // swaps elements 
         left++;
         right--;
      }
   }
   return left;
}


void quick_sort(Array& arr, ptrdiff_t left, ptrdiff_t right)
{
   ptrdiff_t index = partition(arr, left, right);
   if (left < index - 1) 
   { 
      // Sort left half 
      quick_sort(arr, left, index - 1);
   }
   if (index < right)
   { 
      // Sort right half
      quick_sort(arr, index, right);
   }
}

void quick_sort(Array& arr)
{
   return quick_sort(arr, 0, arr.size() - 1);
}

TEST(QuickSortTest, SimpleTest)
{
   Array in = { 2, 4, 0, 5, -1 };
   quick_sort(in);
   EXPECT_EQ(in, Array({ -1, 0, 2, 4, 5 }));
}

TEST(QuickSortTest, EmptyTest)
{
   Array in;
   quick_sort(in);
   EXPECT_EQ(in, Array({}));
}

TEST(QuickSortTest, OneElementTest)
{
   Array in = { 1 };
   quick_sort(in);
   EXPECT_EQ(in, Array({ 1 }));
}

TEST(QuickSortTest, ReversedTest)
{
   Array in = { 10, 8, 6, 4, 2, 0 };
   quick_sort(in);
   EXPECT_EQ(in, Array({ 0, 2, 4, 6, 8, 10 }));
}

TEST(QuickSortTest, AlreadySortedTest)
{
   Array in = { 0, 2, 4, 6, 8, 10 };
   quick_sort(in);
   EXPECT_EQ(in, Array({ 0, 2, 4, 6, 8, 10 }));
}
