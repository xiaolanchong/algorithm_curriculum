#include <vector>
#include <gtest/gtest.h>

/*
специальный класс ориентированных графов – графы преемников (successor graph),
в которых полустепень исхода каждой вершины равна 1, т. е. у каждой вершины всего один преемник.
Граф преемников состоит из одной или нескольких компонент связности.
Каждая компонента содержит один цикл, в который могут вести несколько путей.
*/

using Index = ptrdiff_t;
constexpr Index NO_SUCCESSOR = -1;
using SuccessorGraph = std::vector<Index>;

struct Result
{
   Index cycleStart;
   size_t cycleLength;
};

constexpr Result NO_LOOP{ NO_SUCCESSOR, 0 };

/*
алгоритм Флойда.
граф преемников, который содержит только путь, заканчивающийся циклом.
Мы можем задать следующие вопросы: если выйти из начальной вершины, 
то какова будет первая встреченная вершина, принадлежащая циклу, и сколько всего вершин содержит цикл?
*/
Result find_cycle(const SuccessorGraph& graph)
{
   if (graph.size() < 2)
      return NO_LOOP;
   auto succ = [&graph](Index vertex)
      {
         if (vertex == NO_SUCCESSOR)
            return NO_SUCCESSOR;
         return graph[vertex];
      };

   /*
   , который проходит по графу и использует два указателя a и b.
   Вначале оба указывают на начальную вершину x.
   На каждой итерации a сдвигается вперед на один шаг, а b – на два шага.
   Процесс продолжается, пока оба указателя не встретятся:
   */

   const Index startVertex = 0;
   Index a = succ(startVertex);
   Index b = succ(succ(startVertex));
   while (a != b)
   {
      a = succ(a);
      b = succ(succ(b));
   }
   if (a == NO_SUCCESSOR)
      return NO_LOOP;

   /*
   В этот момент указатель a прошел k шагов, а указатель b – 2k шагов,
поэтому длина цикла делит k. Следовательно, первую вершину, принадлежащую циклу,
можно найти, переставив указатель a на x и продвигая
указатели вперед по одному шагу, пока они снова не встретятся.
   */
   a = startVertex;
   while (a != b)
   {
      a = succ(a);
      b = succ(b);
   }
   const auto cycleStart = a;

/* Проход по циклу */
   b = succ(a);
   size_t length = 1;
   while (a != b)
   {
      b = succ(b);
      length++;
   }

   return { cycleStart, length };
}

TEST(CycleDetectionTest, Test)
{
   Result res{};
   res = find_cycle({1, 2, 3, 4, 5, 6, 7, 3});
   EXPECT_EQ(res.cycleStart, 3);
   EXPECT_EQ(res.cycleLength, 5);

   res = find_cycle({ 1, 2, 3, 4, 5, 6, 7, 0 });
   EXPECT_EQ(res.cycleStart, 0);
   EXPECT_EQ(res.cycleLength, 8);

   res = find_cycle({ 1, 2, 3, 4, 5, 6, 7, NO_SUCCESSOR});
   EXPECT_EQ(res.cycleStart, NO_SUCCESSOR);
   EXPECT_EQ(res.cycleLength, 0);

   res = find_cycle({ });
   EXPECT_EQ(res.cycleStart, NO_SUCCESSOR);
   EXPECT_EQ(res.cycleLength, 0);

   res = find_cycle({ NO_SUCCESSOR });
   EXPECT_EQ(res.cycleStart, NO_SUCCESSOR);
   EXPECT_EQ(res.cycleLength, 0);

   res = find_cycle({ 1, NO_SUCCESSOR });
   EXPECT_EQ(res.cycleStart, NO_SUCCESSOR);
   EXPECT_EQ(res.cycleLength, 0);
}
