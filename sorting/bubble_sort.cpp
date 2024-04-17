#include <gtest/gtest.h>
#include <vector>

using ArrayType = std::vector<int>;

void bubble_sort(ArrayType& array)
{
   for (size_t i = 0; i < array.size(); i++)
   {
      for (size_t j = 0; j + 1 < array.size(); j++)
      {
         if (array[j] > array[j + 1])
         {
            std::swap(array[j], array[j + 1]);
         }
      }
   }
}

TEST(BubbleSortTest, Test)
{
   ArrayType array;
   array = {1, -1, 2, -2, -10};
   bubble_sort(array);

   EXPECT_EQ(array, ArrayType({-10, -2, -1, 1, 2}));

   array = { };
   bubble_sort(array);
   EXPECT_EQ(array, ArrayType({ }));
}