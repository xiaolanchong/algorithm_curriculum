
#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

/*
дано n работ и для каждой указаны продол-
жительность и крайний срок. Наша задача – выбрать порядок выполнения
работ. Для каждой работы нам начисляется d – x баллов, где d – крайний
срок исполнения работы, а x – момент ее фактического завершения.
Какое максимальное число баллов мы можем заработать?

Работа Продолжительность Крайний срок
A 4 2
B 3 5
C 2 7
D 4 5

в оптимальном решении короткие работы всегда предшествуют длинным,
поэтому работы следует отсортировать по продолжительности.
*/

struct Work
{
   size_t duration;
   size_t deadline;
};

using WorkList = std::vector<Work>;

ptrdiff_t schedule_work(WorkList&& workList)
{
   std::sort(workList.begin(), workList.end(), [](const Work& left, const Work& right)
      {
         return left.duration < right.duration;
      });
   ptrdiff_t totalYield = 0;
   size_t time = 0;
   for (const Work& work : workList)
   {
      auto endTime = time + work.duration;
      ptrdiff_t award = work.deadline - endTime;
      totalYield += award;
      time = endTime;
   }
   return totalYield;
}

TEST(WorkScheduleTest, Test)
{
   EXPECT_EQ(-10, schedule_work({ {4, 2}, {3, 5}, {2, 7}, {4, 5} }));
}
