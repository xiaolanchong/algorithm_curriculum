#include <vector>
#include <algorithm>
#include <limits>
#include <gtest/gtest.h>

/*

Пусть имеется множество номиналов монет coins = { c1, c2, …, ck} и де-
нежная сумма n. Задача заключается в том, чтобы разменять сумму n, ис-
пользуя как можно меньше монет. Количество монет одного номинала
не ограничено. Например, если coins = {1, 2, 5} и n = 12, то оптимальное
решение 5 + 5 + 2 = 12, так что достаточно трех монет.

*/

using Coins = std::vector<size_t>;

Coins change_coins(size_t n, const Coins& coins)
{
   if (n == 0)
      return {};

   if (coins.empty())
      return {};

   std::vector<size_t> value(n + 1);
   std::vector<size_t> first(n + 1);

   value[0] = 0;
   for (int x = 1; x <= n; x++)
   {
      value[x] = std::numeric_limits<size_t>::max() / 2;
      for (auto c : coins)
      {
         if (x >= c && value[x - c] + 1 < value[x])
         {
            value[x] = value[x - c] + 1;
            first[x] = c;
         }
      }
   }

   Coins result;
   while (n > 0) {
      result.push_back(first[n]);
      n -= first[n];
   }

   return result;
}

TEST(CoinChangeTest, SimpleTest)
{
   EXPECT_EQ(Coins({2, 5, 5}), change_coins(12, { 1, 2, 5 }));
   EXPECT_EQ(Coins({}), change_coins(12, {}));
   EXPECT_EQ(Coins({}), change_coins(0, { 1, 2, 5 }));
   EXPECT_EQ(Coins({ 5 }), change_coins(5, { 1, 2, 5, 10 }));
   EXPECT_EQ(Coins({ 1, 1, 1 }), change_coins(3, { 1, 5, 10 }));
}
