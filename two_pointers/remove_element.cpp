#include <vector>
#include <gtest/gtest.h>

using Array = std::vector<int>;

template<typename Cont, typename ValType>
size_t move_element_to_end(Cont&& cont, ValType value)
{
   auto it = move_element_to_end(cont.begin(), cont.end(), value);
   return std::distance(cont.begin(), it);
}

template<typename Itr, typename ValType>
Itr move_element_to_end(Itr begin, Itr end, ValType value)
{
   auto itFrom = begin, itNext = begin;
   for (; itFrom != end; ++itFrom) {
      if (!(*itFrom == value)) {
         if (itNext != itFrom)
            //*itNext = std::move(*itFrom);
            std::swap(*itNext, *itFrom);
         ++itNext;
      }
   }
   return itNext;
}

template<typename Itr, typename Pred>
Itr my_remove_if(Itr begin, Itr end, Pred pred)
{
   auto itFrom = begin, itNext = begin;
   for (; itFrom != end; ++itFrom) {
      if (!pred(itFrom-begin)) {
         if (itNext != itFrom)
            *itNext = std::move(*itFrom);
         ++itNext;
      }
   }
   return itNext;
}

TEST(MoveElementToEndTest, Test)
{
   size_t res = 0;
   Array array;

   array = { 1, 3, 5, 0, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 5);
   EXPECT_EQ(array, Array({ 1, 3, 5, 2, 4, 0 }));

   array = { 1, 3, 0, 0, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 4);
   EXPECT_EQ(array, Array({ 1, 3, 2, 4, 0, 0 }));

   array = { 0, 3, 1, 4, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 5);
   EXPECT_EQ(array, Array({ 3, 1, 4, 2, 4, 0 }));

   array = { 0, 0, 0, 4, 2, 4 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 3);
   EXPECT_EQ(array, Array({ 4, 2, 4, 0, 0, 0 }));

   array = { 0, 0, 0, 0, 0, 0 };
   res = move_element_to_end(array, 0);
   EXPECT_EQ(res, 0);
   EXPECT_EQ(array, Array({ 0, 0, 0, 0, 0, 0 }));

   array = { 1, 2, 3, 4, 5, 2 };
   res = move_element_to_end(array, 6);
   EXPECT_EQ(res, 6);
   EXPECT_EQ(array, Array({ 1, 2, 3, 4, 5, 2 }));
}

void remove_smiles(std::string& s)
{
   enum class Token
   {
      start,
      colon_or_semicolon,
      dash,
      smile,
   };

   auto removePred = [&s, state=Token::start](size_t pos) mutable
   {
      switch(state)
      {
      case Token::start:
         if (pos + 2 < s.size())
         {
            if (
               (s[pos] == ':' || s[pos] == ';') &&
               s[pos + 1] == '-' &&
               s[pos + 2] == ')')
            {
               state = Token::colon_or_semicolon;
               return true;
            }
         }
         return false;
      case Token::colon_or_semicolon:
         state = Token::dash;
         return true;

      case Token::dash:
         state = Token::smile;
         return true;

      case Token::smile:
         if (s[pos] == ')')
            return true;
         state = Token::start;
         return false;
      }
      return false;
   };
   auto it = my_remove_if(s.begin(), s.end(), removePred);
   s.erase(it, s.end());
}

TEST(RemoveSmiles, Test)
{
   std::string s;

   s = "aaaa:-)bbb";
   remove_smiles(s);
   EXPECT_EQ(s, "aaaabbb");

   s = ":-)bbb";
   remove_smiles(s);
   EXPECT_EQ(s, "bbb");

   s = "aaaa:-)";
   remove_smiles(s);
   EXPECT_EQ(s, "aaaa");

   s = "aaaa:-))))bbb";
   remove_smiles(s);
   EXPECT_EQ(s, "aaaabbb");

   s = "aaaa:-bbb";
   remove_smiles(s);
   EXPECT_EQ(s, "aaaa:-bbb");

   s = "aaaa:-))bbb:-))";
   remove_smiles(s);
   EXPECT_EQ(s, "aaaabbb");

   s = "aaaa:-))bbb:-))ccc";
   remove_smiles(s);
   EXPECT_EQ(s, "aaaabbbccc");

   s = "aaaa:)bbb:-))ccc";
   remove_smiles(s);
   EXPECT_EQ(s, "aaaa:)bbbccc");
}
