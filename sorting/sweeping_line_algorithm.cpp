#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

// Sweeping line algorithm based on sorting

using Time = int;

struct VisitingTime
{
   Time enter;
   Time exit;
};

using VisitingTimes = std::vector<VisitingTime>;

// Laaksonen 4th chapter
// Пусть имеется ресторан, и мы знаем время прихода и ухода всех клиентов в течение дня.
// найти максимальное число клиентов, находившихся в ресторане одновременно.
size_t count_max_visitor(const VisitingTimes& visitingTimes)
{
   enum class Event
   {
      Enter,
      Exit,
   };

   std::vector<std::pair<Time, Event>> times;
   times.reserve(2 * visitingTimes.size());
   for (const auto& visit : visitingTimes)
   {
      times.push_back({ visit.enter, Event::Enter});
      times.push_back({ visit.exit,  Event::Exit });
   }

   std::sort(times.begin(), times.end());
   size_t counter = 0;
   size_t maxCounter = 0;
   for (const auto& [time, event] : times)
   {
      if (event == Event::Enter)
      {
         ++counter;
         maxCounter = std::max(maxCounter, counter);
      }
      else
         --counter;
   }
   return maxCounter;
}

TEST(SweepingLineAlgorithmTest, Test)
{
   EXPECT_EQ(2, count_max_visitor({ {0, 4}, {1, 3} }));
   EXPECT_EQ(0, count_max_visitor({ }));
   EXPECT_EQ(1, count_max_visitor({ {1, 2} }));
}
