#include <vector>
#include <gtest/gtest.h>

using namespace std;

int maxProfit(const vector<int>& prices) 
{
   if (prices.empty()) return 0;

   int left = 0;       // buy
   int maxProfit = 0;

   for (int right = 1; right < prices.size(); right++) 
   {
      if (prices[right] > prices[left]) 
      {
         maxProfit = max(maxProfit, prices[right] - prices[left]);
      } 
      else 
      {
         // find the min element so far
         // Better buying price found
         left = right;
      }
   }

   return maxProfit;
}

TEST(MaxStockProfitTest, Test)
{
   EXPECT_EQ(maxProfit({ 7, 1, 5, 3, 6, 4 }), 5);
   EXPECT_EQ(maxProfit({ 4 }), 0);
   EXPECT_EQ(maxProfit({  }), 0);
   EXPECT_EQ(maxProfit({ 5, 5, 5, 5 }), 0);
   EXPECT_EQ(maxProfit({ 5, 8, 6, 1, 3 }), 3);
   EXPECT_EQ(maxProfit({ 5, 8, 6, 1, 1 }), 3);
}