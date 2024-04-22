#include <vector>
#include <stack>
#include <gtest/gtest.h>

using VertexIndex = unsigned int;
using Vertices = std::vector<VertexIndex>;
using Graph = std::vector<Vertices>;

bool is_reachable(const Graph& graph, VertexIndex from, VertexIndex to, std::vector<bool>& visited)
{
   if (graph.size() <= from || graph.size() <= to)
      return false;
   if (from == to)
      return true;
   for (const auto& adjacentVertex : graph[from])
   {
      if (visited[adjacentVertex])
         continue;
      visited[adjacentVertex] = true;
      if (is_reachable(graph, adjacentVertex, to, visited))
         return true;
   }
   return false;
}

bool is_reachable(const Graph& graph, VertexIndex from, VertexIndex to)
{
   std::vector<bool> visited(graph.size(), false);
   return is_reachable(graph, from, to, visited);
}

////////////////////////////////////////////////////

using VertexStack = std::stack<VertexIndex>;

bool is_reachable_stacked(const Graph& graph, VertexIndex from, VertexIndex to)
{
   std::vector<bool> visited(graph.size(), false);
   VertexStack verticesToVisit;
   verticesToVisit.push(from);
   while (!verticesToVisit.empty())
   {
      const auto visitingVertex = verticesToVisit.top();
      verticesToVisit.pop();

      if (visitingVertex == to)
         return true;

      if (graph.size() <= visitingVertex || graph.size() <= to)
         continue;

      if (visited[visitingVertex])
         continue;

      visited[visitingVertex] = true;
      for (const auto& adjacentVertex : graph[visitingVertex])
      {
         if (!visited[adjacentVertex])
            verticesToVisit.push(adjacentVertex);
      }
   }
   return false;
}

TEST(DepthFirstSearchTest, SimpleTest)
{
   Graph graph(
      {
         {1, 3, 5},
         {1, 4, 7},
         {7, 3, 8},
         {7, 1, 6},
         {6},
         {2},
         {2, 3},
         {7, 2, 5},
         {}
      });
   EXPECT_TRUE(is_reachable(graph, 0, 8));
   EXPECT_FALSE(is_reachable(graph, 8, 0));
   EXPECT_TRUE(is_reachable(graph, 0, 0));
   EXPECT_TRUE(is_reachable_stacked(graph, 0, 8));
   EXPECT_FALSE(is_reachable_stacked(graph, 8, 0));
   EXPECT_TRUE(is_reachable_stacked(graph, 0, 0));
}