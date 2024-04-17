#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

using Array = std::vector<int>;

/*
Алгоритм состоит из ряда шагов, на каждом из которых диапазон
поиска делится пополам. На каждом шаге проверяется средний элемент
активного подмассива. Если средний элемент совпадает с искомым зна-
чением, то поиск заканчивается. В противном случае поиск рекурсивно
продолжается в левой или правой половине подмассива в зависимости от
значения среднего элемента.
*/

ptrdiff_t binary_search(const Array& array, int x)
{
   ptrdiff_t a = 0, b = array.size() - 1;
   while (a <= b)
   {
      ptrdiff_t k = (a + b) / 2;
      if (array[k] == x)
      {
         // x найден в позиции с индексом k
         return k;
      }
      if (array[k] < x)
         a = k + 1;
      else
         b = k - 1;
   }
   return -1;
}

/*
просматривать массив слева направо, совершая прыжки.
*/

ptrdiff_t jump_binary_search(const Array& array, int x)
{
   size_t k = 0;
   for (size_t b = array.size() / 2; b >= 1; b /= 2)
   {
      while (k + b < array.size() && array[k + b] <= x)
         k += b;
   }
   if (array[k] == x)
   {
      // x найден в позиции с индексом k
      return k;
   }
   return -1;
}

/*
* Двоичный поиск по ответу
Пусть мы решаем некоторую задачу, и существует функция valid(x),
возвращающая true, если x – допустимое решение, и false в противном
случае. Кроме того, мы знаем, что valid(x) равно false, когда x < k, и равно
true, когда x ≥ k. В такой ситуации можно использовать двоичный поиск
для эффективного нахождения k.
*/

using IsValid = std::function<bool(ptrdiff_t)>;

ptrdiff_t answer_binary_search(const IsValid& isValid, ptrdiff_t minValidValue)
{
   ptrdiff_t x = -1;
   for (ptrdiff_t b = minValidValue; b >= 1; b /= 2)
   {
      while (!isValid(x + b))
         x += b;
   }
   ptrdiff_t k = x + 1;
   return k;
}

TEST(BinarySearch, Test)
{
   const Array array({ 1, 3, 3, 4, 5, 5, 6, 9, 10, 12, 12, 15 });
   EXPECT_EQ(7, binary_search(array, 9));
   EXPECT_EQ(0, binary_search(array, 1));
   EXPECT_EQ(11, binary_search(array, 15));

   EXPECT_EQ(-1, binary_search(array, 777)); // right
   EXPECT_EQ(-1, binary_search(array, -100)); // left
   EXPECT_EQ(-1, binary_search(array, 7));   // middle
}

TEST(BinarySearch, JumpTest)
{
   const Array array({ 1, 3, 3, 4, 5, 5, 6, 9, 10, 12, 12, 15 });
   EXPECT_EQ(7, jump_binary_search(array, 9));
   EXPECT_EQ(0, jump_binary_search(array, 1));
   EXPECT_EQ(11, jump_binary_search(array, 15));

   EXPECT_EQ(-1, jump_binary_search(array, 777)); // right
   EXPECT_EQ(-1, jump_binary_search(array, -100)); // left
   EXPECT_EQ(-1, jump_binary_search(array, 7));   // middle
}

TEST(BinarySearch, AnswerTest)
{
   EXPECT_EQ(9, answer_binary_search([](auto val) { return val >= 9; }, 15));
   EXPECT_EQ(15, answer_binary_search([](auto val) { return val >= 15; }, 15));
   EXPECT_EQ(15, answer_binary_search([](auto val) { return val >= 15; }, 15000));
   EXPECT_EQ(0, answer_binary_search([](auto val) { return true; }, 150));
}
