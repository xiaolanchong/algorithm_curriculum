// DijkstraFast.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <unordered_map>
#include <tuple>
#include <array>
#include <queue>
#include <algorithm>

using Vertex = unsigned int; // 0 ...
using Weight = unsigned int; // 1 ...
using AdjVertex = std::pair<Vertex, Weight>;
using Graph = std::vector<std::vector<AdjVertex>>;

Vertex ToNumber(char letter)
{
   return letter - 'A';
}

char ToLetter(Vertex v)
{
   return static_cast<char>(v + 'A');
}

Graph CreateGraph()
{
   using Edge = std::tuple<char, char, Weight>;
   std::array<Edge, 21> edges =
   {
      Edge{'E', 'B', 4},
      Edge{'E', 'I', 8},
      Edge{'B', 'A', 2},
      Edge{'G', 'E', 5},
      Edge{'A', 'H', 2},
      Edge{'F', 'C', 5},
      Edge{'G', 'H', 5},
      Edge{'E', 'C', 9},
      Edge{'H', 'A', 9},
      Edge{'H', 'B', 4},
      Edge{'B', 'C', 6},
      Edge{'E', 'A', 4},
      Edge{'C', 'H', 6},
      Edge{'I', 'E', 3},
      Edge{'I', 'C', 1},
      Edge{'I', 'B', 5},
      Edge{'D', 'H', 2},
      Edge{'G', 'F', 6},
      Edge{'C', 'G', 7},
      Edge{'A', 'E', 9},
      Edge{'A', 'C', 5},
   };

   Graph g;
   g.resize(ToNumber('I') + 1);
   for (const auto& [v1, v2, w] : edges)
   {
      const auto v1num = ToNumber(v1);
      const auto v2num = ToNumber(v2);
      g[v1num].push_back({ v2num, w });
      g[v2num].push_back({ v1num, w });
   }
   return g;
}

using Distance = Weight;
using Path = std::vector<Vertex>;

Path getMinPath(const std::unordered_map<Vertex, Vertex>& prevVertices, Vertex end)
   {
      Path minPath;
      minPath.push_back(end);
      Vertex vvv = end;
      for (auto it = prevVertices.find(vvv); it != prevVertices.end(); it = prevVertices.find(vvv))
      {
         minPath.push_back(it->second);
         vvv = it->second;
      }
      std::reverse(minPath.begin(), minPath.end());
      return minPath;
   };

std::tuple<Distance, Path> FindDistance(const Graph& graph, Vertex start, Vertex end)
{
   const Distance MAX_DISTANCE = Distance(1'000'000'000);
   std::vector<Distance> distances(graph.size(), MAX_DISTANCE);
   distances[start] = 0;

   using SortedVertex = std::pair<Distance, Vertex>;
   using SortedDistances = std::priority_queue<std::pair<Distance, Vertex>, std::vector<SortedVertex>, std::less<SortedVertex>>;
   SortedDistances sortedDistances;
   sortedDistances.push({0, start});

   std::unordered_map<Vertex, Vertex> prevVertices;

   std::vector<bool> processedVertices(graph.size(), false);
   while (!sortedDistances.empty())
   {
      const auto minDist = sortedDistances.top().first;
      const auto minDistVertex = sortedDistances.top().second;
      sortedDistances.pop();

      if (processedVertices[minDistVertex])
         continue;
      processedVertices[minDistVertex] = true;

      for (const auto& [adjVertex, adjVerDist]: graph[minDistVertex])
      {
         auto curDist = distances[adjVertex];
         if (curDist > minDist + adjVerDist)
         {
            auto newDist = minDist + adjVerDist;
            distances[adjVertex] = newDist;
            sortedDistances.push({newDist, adjVertex});
            prevVertices[adjVertex] = minDistVertex;
         }
      }
   }
   return { distances[end], getMinPath(prevVertices, end) };
}


int main()
{
   const auto start = 'E';
   const auto end = 'H';
   auto graph = CreateGraph();
   auto [dist, path] = FindDistance(graph, ToNumber(start), ToNumber(end));
   std::cout << "Min distance: " << dist << std::endl;
   std::cout << "Path: ";
   for (auto v: path)
   {
      std::cout << ToLetter(v) << ' ';
   }
}