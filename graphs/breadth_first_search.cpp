#include <vector>
#include <queue>
#include <gtest/gtest.h>

using VertexIndex = unsigned int;
using Vertices = std::vector<VertexIndex>;
using Graph = std::vector<Vertices>;

////////////////////////////////////////////////////

bool is_reachable_bfs(const Graph& graph, VertexIndex from, VertexIndex to)
{
   std::vector<bool> visited(graph.size(), false);
   std::queue<VertexIndex> verticesToVisit;
   verticesToVisit.push(from);
   while (!verticesToVisit.empty())
   {
      const auto visitingVertex = verticesToVisit.front();
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

TEST(BreadthFirstSearchTest, SimpleTest)
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
   EXPECT_TRUE(is_reachable_bfs(graph, 0, 8));
   EXPECT_FALSE(is_reachable_bfs(graph, 8, 0));
   EXPECT_TRUE(is_reachable_bfs(graph, 0, 0));
}
