#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

/*
Laaksonen, chapter 6
поиск пути из левого верхнего в правый
нижний угол сетки n×n при условии, что разрешено двигаться только вниз
и вправо. В каждой клетке находится целое число, и путь должен быть таким,
чтобы сумма значений в лежащих на нем клетках была максимальной.
*/

using Cost = size_t;
using Row = std::vector<Cost>;
using Grid = std::vector<Row>;

enum class Step: char
{
   Right = 'R',
   Down = 'D',
};

using Steps = std::vector<Step>;

Steps find_max_path_in_grid(const Grid& grid)
{
   if (grid.empty())
      return {};

   Grid stepSum(grid.size());
   for (size_t i = 0; i < grid.size(); ++i)
   {
      if (grid[i].empty())
         return {};
      stepSum[i].resize(grid[i].size());
   }

   auto getCostSum = [&stepSum](ptrdiff_t y, ptrdiff_t x)
      {
         if (x < 0 || y < 0)
            return Cost(0);
         else
            return stepSum[y][x];
      };
   for (ptrdiff_t y = 0; y < static_cast<ptrdiff_t>(grid.size()); y++)
   {
      for (ptrdiff_t x = 0; x < static_cast<ptrdiff_t>(grid[y].size()); x++)
      {
         stepSum[y][x] = std::max(getCostSum(y, x - 1), getCostSum(y - 1, x)) + grid[y][x];
      }
   }

   Steps steps;
   for (ptrdiff_t y = grid.size() - 1, x = grid.back().size() - 1; x >= 0 && y >= 0;)
   {
      if (x == 0 && y == 0)
         break;
      if (x > 0 && y > 0)
      {
         if ((stepSum[y - 1][x] - grid[y][x]) > (stepSum[y][x - 1] - grid[y][x]))
         {
            steps.push_back(Step::Down);
            --y;
         }
         else
         {
            steps.push_back(Step::Right);
            --x;
         }
      }
      else if (x > 0)
      {
         steps.push_back(Step::Right);
         --x;
      }
      else
      {
         steps.push_back(Step::Down);
         --y;
      }
   }
   std::reverse(steps.begin(), steps.end());
   return steps;
}

TEST(GridPathTest, SimplePath)
{
   Grid grid = { 
      {1, 1, 1, 1},
      {2, 4, 2, 0},
      {2, 4, 2, 3},
   };

   auto steps = find_max_path_in_grid(grid);
   EXPECT_EQ(steps, Steps({ Step::Down, Step::Right, Step::Down, Step::Right, Step::Right }));
}

TEST(GridPathTest, EmptyGrid)
{
   EXPECT_EQ(find_max_path_in_grid({}), Steps({}));
   EXPECT_EQ(find_max_path_in_grid({ {}, {} }), Steps({}));
}

TEST(GridPathTest, NarrowGrid)
{
   EXPECT_EQ(find_max_path_in_grid({ { 1, 1, 2, 2 } }), Steps({ Step::Right, Step::Right, Step::Right }));
   EXPECT_EQ(find_max_path_in_grid({ {2}, {3}, {1}, {0} }), Steps({ Step::Down, Step::Down, Step::Down }));
}

TEST(GridPathTest, UniformGrid)
{
   Grid grid = {
   {1, 1, 1, 1},
   {1, 1, 1, 1},
   {1, 1, 1, 1},
   };
   EXPECT_EQ(find_max_path_in_grid(grid), Steps({ Step::Down, Step::Down, Step::Right, Step::Right, Step::Right }));
}
