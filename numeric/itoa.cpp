#include <string>
#include <gtest/gtest.h>

std::string my_itoa(int number, unsigned int base = 10)
{
   std::string result;
   const bool isSigned = number < 0;
   number = std::abs(number);

   do
   {
      const auto quotient = number / base;
      const auto reminder = number % base;
      char digit = reminder < 10 ? (reminder + '0') : (reminder - 10 + 'a');
      result.push_back(digit);
      number = quotient;
   }
   while (number != 0);

   if (isSigned)
      result.push_back('-');
   std::reverse(result.begin(), result.end());
   return result;
}

const int error = -1;

int my_atoi(const std::string& str, unsigned int base = 10)
{
   if (str.empty())
      return error;
   auto it = str.begin();
   bool isSigned = false;
   if (*it == '-')
   {
      isSigned = true;
      ++it;
   }
   if (it == str.end())
      return error;
   int result = 0;
   for (;it != str.end(); ++it)
   {
      int digit = *it <= '9' ? *it - '0' : *it - 'a';
      result = base * result + digit;
   }

   return isSigned ? -result: result;
}

TEST(ItoaTest, Test)
{
   EXPECT_EQ("0", my_itoa(0));
   EXPECT_EQ("1", my_itoa(1));
   EXPECT_EQ("345", my_itoa(345));
   EXPECT_EQ("-1", my_itoa(-1));
   EXPECT_EQ("-34455", my_itoa(-34455));
   EXPECT_EQ("1946579432", my_itoa(1946579432));

   EXPECT_EQ("feab1", my_itoa(0xfeab1, 16));
}

TEST(AtoiTest, Test)
{
   EXPECT_EQ(my_atoi("0"), 0);
   EXPECT_EQ(my_atoi("1"), (1));
   EXPECT_EQ(my_atoi("345"), (345));
   EXPECT_EQ(my_atoi("-1"), (-1));
   EXPECT_EQ(my_atoi("345", 16), 0x345);
   EXPECT_EQ(my_atoi("", 16), error);
   EXPECT_EQ(my_atoi("-", 16), error);
}
