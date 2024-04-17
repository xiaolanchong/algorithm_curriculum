#include <vector>
#include <algorithm>
#include <gtest/gtest.h>

/*

Given n events with their starting and ending times, find a
schedule that includes as many events as possible. It is not possible to select an
event partially. For example, consider the following events:
event starting time ending time
A 1 3
B 2 5
C 3 9
D 6 8

In this case the maximum number of events is two. For example, we can select
events B and D.

Always select the next possible event that ends as early as possible.
this algorithm always produces an optimal solution. The reason
for this is that it is always an optimal choice to first select an event that
ends as early as possible. After this, it is an optimal choice to select the next
event using the same strategy, etc., until we cannot select any more events
*/

using EventId = char;

struct Event
{
   EventId id;
   int startingTime;
   int endingTime;
};

using Events = std::vector<Event>;
using EventIds = std::vector<EventId>;

EventIds select_events(Events&& events)
{
   EventIds eventIds;
   std::sort(events.begin(), events.end(),
      [](const Event& left, const Event& right)
      {
         return left.endingTime < right.endingTime;
      });
   int freeStartingTime = 0;
   for (const Event& event : events)
   {
      if (freeStartingTime > event.startingTime)
         continue;
      freeStartingTime = event.endingTime;
      eventIds.push_back(event.id);
   }
   return eventIds;
}

TEST(TimeTableTest, Test)
{
   EXPECT_EQ(EventIds({ 'A', 'D'}), select_events({{'A', 1, 3}, {'B', 2, 5}, {'C', 3, 9}, {'D', 6, 8}}));
}
