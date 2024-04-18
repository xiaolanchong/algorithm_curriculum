#include <vector>
#include <algorithm>
#include <numeric>
#include <gtest/gtest.h>

/*
* A. Shen, 1.1.4
* Calculate the power of a number with O(logN) complexity
*/
int get_power(int a, size_t power)
{
   int result = 1;
   int factor = a;
   for (; power != 0;)
   {
      if (power % 2 == 0)
      {
         power /= 2;
         factor *= factor;
      }
      else
      {
         --power;
         result *= factor;
      }
   }
   return result;
}

TEST(PowerTest, Test)
{
   EXPECT_EQ(8, get_power(2, 3));
   EXPECT_EQ(-32, get_power(-2, 5));
   EXPECT_EQ(1024*1024, get_power(2, 20));
   EXPECT_EQ(1, get_power(12, 0));
   EXPECT_EQ(12, get_power(12, 1));
}
