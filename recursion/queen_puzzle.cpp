
#include <gtest/gtest.h>
#include <vector>

using OccupiedVec = std::vector<bool>;

size_t count_recursively(size_t row, OccupiedVec& col, OccupiedVec& diag1, OccupiedVec& diag2, size_t currentCount)
{
   if (row == col.size())
      return currentCount + 1;
   for (size_t i = 0; i < col.size(); ++i)
   {

   }
   return 0;
}

// backtrackin
size_t count_queen_placement(size_t boardSize)
{
   OccupiedVec col(boardSize, false);
   OccupiedVec diag1(boardSize, false);
   OccupiedVec diag2(boardSize, false);

   return count_recursively(0, col, diag1, diag2, 0);
}
