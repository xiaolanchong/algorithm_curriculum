#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

/*

Наибольшей возрастающей подпоследовательностью в массиве из n эле-
ментов называется самая длинная последовательность элементов массива,
простирающаяся слева направо и такая, что каждый следующий элемент больше предыдущего.

*/

using Array = std::vector<int>;

size_t find_max_length(const Array& array)
{
   if (array.empty())
      return 0;
   std::vector<size_t> length(array.size());
   for (size_t k = 0; k < array.size(); k++)
   {
      length[k] = 1;
      for (size_t i = 0; i < k; i++)
      {
         if (array[i] < array[k])
         {
            length[k] = std::max(length[k], length[i] + 1);
         }
      }
   }
   return *std::max_element(length.cbegin(), length.cend());
}

TEST(FindMaxLengthTest, SimpleTest)
{
   EXPECT_EQ(4, find_max_length({ 6, 2, 5, 1, 7, 4, 8, 3 }));
   EXPECT_EQ(0, find_max_length({  }));
   EXPECT_EQ(6, find_max_length({ 1, 2, 3, 10, 11, 12 }));
   EXPECT_EQ(1, find_max_length({ 12, 11, 10, 9, 5, 1 }));
}
