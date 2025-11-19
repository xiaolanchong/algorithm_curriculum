#include <vector>
#include <algorithm>
#include <cmath>
#include <gtest/gtest.h>

struct Point
{
   double x;
   double y;
};

using Points = std::vector<Point>;

double get_distance(const Point& p1, const Point& p2)
{
   return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) +
      (p1.y - p2.y) * (p1.y - p2.y)
   );
}

double get_min_distance_naive(const Points& points, size_t begin, size_t end)
{
   double min_distance = std::numeric_limits<double>::max();
   for (size_t i = begin; i < end; ++i)
      for (size_t j = i + 1; j < end; ++j)
         min_distance = std::min(get_distance(points[i], points[j]), min_distance);
   return min_distance;
}

// A utility function to find the 
// distance between the closest points of 
// strip of given size. All points in 
// strip[] are sorted according to 
// y coordinate. They all have an upper
// bound on minimum distance as d. 
// Note that this method seems to be 
// a O(n^2) method, but it's a O(n) 
// method as the inner loop runs at most 6 times 
double strip_closest(Points&& strip, double d)
{
   double min_distance = d; // Initialize the minimum distance as d 

   auto compareY = [](const Point& p1, const Point& p2)
      {
         return p1.y < p2.y;
      };
   std::sort(strip.begin(), strip.end(), compareY);

   // Pick all points one by one and try the next points till the difference 
   // between y coordinates is smaller than d. 
   // This is a proven fact that this loop runs at most 6 times 
   for (size_t i = 0; i < strip.size(); ++i)
      for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < min_distance; ++j)
         min_distance = std::min(min_distance, get_distance(strip[i], strip[j]));

   return min_distance;
}

double get_min_distance_sorted(const Points& points, size_t begin, size_t end)
{
  // if (end == begin || end == (begin + 1))  // zero or 1 point
  //    return 0;
   if ((end - begin) < 3)
      return get_min_distance_naive(points, begin, end);

   // Find the middle point 
   const auto mid = (begin + end) / 2;
   const Point midPoint = points[mid];

   // Consider the vertical line passing 
   // through the middle point calculate 
   // the smallest distance dl on left 
   // of middle point and dr on right side 
   const auto dl = get_min_distance_sorted(points, begin, mid);
   const auto dr = get_min_distance_sorted(points, mid, end);

   // Find the smaller of two distances 
   const auto d = std::min(dl, dr);

   // Build an array strip[] that contains 
   // points close (closer than d) 
   // to the line passing through the middle point 
   Points strip;
   strip.reserve(end - begin);
   for (size_t i = begin; i < end; i++)
      if (std::abs(points[i].x - midPoint.x) < d)
         strip.push_back(points[i]);

   // Find the closest points in strip. 
   // Return the minimum of d and closest 
   // distance is strip[] 
   return std::min(d, strip_closest(std::move(strip), d));
}

double get_min_distance(Points&& points)
{
   if (points.size() < 2)
      return 0;
   auto compareX = [](const Point& left, const Point& right)
      {
         return left.x < right.x;
      };
   std::sort(points.begin(), points.end(), compareX);

   return get_min_distance_sorted(points, 0, points.size());
}


TEST(ClosestPointsTest, SimpleTest)
{
   Points points = { {2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4} };
   EXPECT_DOUBLE_EQ(get_min_distance(std::move(points)), std::sqrt(2));

   EXPECT_DOUBLE_EQ(get_min_distance({}), 0);
   EXPECT_DOUBLE_EQ(get_min_distance({ {1, 1} }), 0);
   EXPECT_DOUBLE_EQ(get_min_distance({ {1, 1},  {1, 1} }), 0);
   EXPECT_DOUBLE_EQ(get_min_distance({ {1, 1},  {2, 3} }), std::sqrt(5));
   EXPECT_DOUBLE_EQ(get_min_distance({ {1, 1},  {3, 11},  {11, 4},  {4, 4},  {1, 1},  {1, 1} }), 0);
}
