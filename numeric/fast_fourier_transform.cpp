#include <vector>
#include <algorithm>
#include <numeric>
#include <complex>
#define _USE_MATH_DEFINES
#include <cmath>
#include <gtest/gtest.h>

using ComplexDouble = std::complex<double>;
constexpr double pi = M_PI; // std::acos(-1.0);

enum class Direction
{
   Forward,
   Backward,
};

using Coeffs = std::vector<ComplexDouble>;

/*

Функция fft выполняет алгоритм БПФ. Ей передается вектор a, содер-
жащий коэффициенты полинома, и дополнительный параметр d. Если d
равен 1 (по умолчанию), то функция вычисляет прямое преобразование
Фурье, а если –1, то обратное. Как уже было сказано, функция предполага-
ет, что n – степень двойки.
Сначала функция строит вектор r, равный поразрядной обратной пере-
становке a, соответствующей порядку, в котором производится доступ к
значениям на нижнем уровне рекурсии. Этот прием позволяет вычислить
преобразование без создания дополнительных векторов и рекурсивных
вызовов. После этого функция вычисляет преобразования Фурье векторов
длины 2, 4, 8, ..., n. Наконец, если требовалось вычислить обратное преоб-
разование Фурье, то все выходные значения делятся на n.
*/

Coeffs fft(const Coeffs& a, Direction direction = Direction::Forward)
{
   const size_t n = a.size();
   Coeffs r(n);
   for (size_t k = 0; k < n; k++) {
      int b = 0;
      for (size_t z = 1; z < n; z *= 2) {
         b *= 2;
         if (k & z) b++;
      }
      r[b] = a[k];
   }
   const int factor = direction == Direction::Forward ? 1 : -1;
   for (size_t m = 2; m <= n; m *= 2) {
      ComplexDouble wm = std::exp(ComplexDouble{ 0, factor * 2 * pi / m });
      for (size_t k = 0; k < n; k += m) {
         ComplexDouble w = 1;
         for (size_t j = 0; j < m / 2; j++) {
            ComplexDouble u = r[k + j];
            ComplexDouble t = w * r[k + j + m / 2];
            r[k + j] = u + t;
            r[k + j + m / 2] = u - t;
            w = w * wm;
         }
      }
   }
   if (direction == Direction::Backward) {
      for (size_t i = 0; i < n; i++) r[i] /= double(n);
   }
   return r;
}
/*
с помощью функции fft вычислить произведение
f(x) = 2x + 3 и g(x) = 5x + 1. Сначала преобразовываем оба полинома в пред-
ставление значениями в точках, затем вычисляем произведение и, нако-
нец, выполняем обратное преобразование в представление коэффициен-
тами. Получается 10x2 + 17x + 3, как и положено.
Хотя алгоритм БПФ оперирует комплексными числами, входные и вы-
ходные значения часто являются целыми. После вычисления произведе-
ния мы можем написать (int)(p[i].real()+0.5), чтобы получить вещест-
венную часть комплексного числа p[i] и преобразовать ее в целое.
*/

template<typename T>
constexpr bool IsPowerOfTwo(T x)
{
   return (x & (x - 1)) == 0;
}

Coeffs multiply(const Coeffs& a, const Coeffs& b)
{
   assert(IsPowerOfTwo(a.size()));
   assert(IsPowerOfTwo(b.size()));
   assert(a.size() == b.size());
   const size_t n = a.size();
   auto tf = fft(a);
   auto tg = fft(b);
   Coeffs tp(a.size());
   for (size_t i = 0; i < n; i++)
      tp[i] = tf[i] * tg[i];
   auto p = fft(tp, Direction::Backward); // [3,17,10,0]
   return p;
}

Coeffs get_convolution(const Coeffs& a, const Coeffs& b)
{
   //std::reverse(b.begin(), b.end());
   const size_t nextPowOf2A = (size_t)std::pow(2, std::ceil(std::log2(a.size())));
   const size_t nextPowOf2B = (size_t)std::pow(2, std::ceil(std::log2(b.size())));

   const size_t maxPowOf2 = std::max(nextPowOf2A, nextPowOf2B);
   Coeffs aFilled(2 * maxPowOf2);
   std::copy(a.cbegin(), a.cend(), aFilled.begin());
   Coeffs bFilled(2 * maxPowOf2);
   std::copy(b.crbegin(), b.crend(), bFilled.begin()); // + reversed
   Coeffs cFilled = multiply(aFilled, bFilled);
   auto toTruncate = std::find_if(cFilled.rbegin(), cFilled.rend(),
      [](ComplexDouble elem) { return std::abs(elem.real()) > 1e-10; });
   cFilled.erase(toTruncate.base(), cFilled.end());
   return cFilled;
}

/*
f(x) = 2x + 3 и g(x) = 5x + 1, f*g = 10x2 + 17x + 3
*/
TEST(FastFourierTransformTest, MultipyTest)
{
   constexpr size_t n = 4;
   Coeffs f = { 3, 2, 0, 0 };
   Coeffs g = { 1, 5, 0, 0 };
   auto p = multiply(f, g);
   const Coeffs expected({ 3, 17, 10, 0 });
   ASSERT_EQ(p.size(), expected.size());
   for (size_t i = 0; i < expected.size(); i++) {
      ASSERT_NEAR(p[i].imag(), expected[i].imag(), 1e-15);
      ASSERT_NEAR(p[i].real(), expected[i].real(), 1e-15);
   }
}

TEST(FastFourierTransformTest, ConvolutionTest)
{
   const Coeffs a({ 5, 1, 3, 4, 2, 1, 2 });
   const Coeffs b({ 1, 3, 2 });
   const Coeffs expected({ 10, 17, 14, 18, 19, 12, 9, 7, 2 });
   auto p = get_convolution(a, b);
   ASSERT_EQ(p.size(), expected.size());
   for (size_t i = 0; i < expected.size(); i++) {
      ASSERT_NEAR(p[i].imag(), expected[i].imag(), 1e-10);
      ASSERT_NEAR(p[i].real(), expected[i].real(), 1e-10);
   }
}
