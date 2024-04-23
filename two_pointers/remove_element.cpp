#include <vector>
#include <gtest/gtest.h>

using Array = std::vector<int>;

size_t move_element_to_end(Array& array, int element)
{
   auto equal_it = array.begin();
   for(; equal_it != array.end() && *equal_it != element; ++equal_it)
   { }
   if (equal_it == array.end())
      return array.size();

   auto i = equal_it;
   ++i;
   for (; i != array.end(); ++i)
      if (*i != element)
      {
         if (equal_it != i)
            std::swap(*equal_it, *i);
         ++equal_it;
      }
   return equal_it - array.begin();
}

TEST(MoveElementToEndTest, Test)
{
   size_t res = 0;
   Array array;

   array = { 1, 3, 5, 0, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 5);
   EXPECT_EQ(array, Array({ 1, 3, 5, 2, 4, 0 }));

   array = { 1, 3, 0, 0, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 4);
   EXPECT_EQ(array, Array({ 1, 3, 2, 4, 0, 0 }));

   array = { 0, 3, 1, 4, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 5);
   EXPECT_EQ(array, Array({ 3, 1, 4, 2, 4, 0 }));

   array = { 0, 0, 0, 4, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 3);
   EXPECT_EQ(array, Array({ 4, 2, 4, 0, 0, 0 }));

   array = { 0, 0, 0, 0, 0, 0 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 0);
   EXPECT_EQ(array, Array({ 0, 0, 0, 0, 0, 0 }));

   array = { 1, 2, 3, 4, 5, 2 };
   res = move_element_to_end(array, 6);
   EXPECT_EQ(res, 6);
   EXPECT_EQ(array, Array({ 1, 2, 3, 4, 5, 2 }));
}
