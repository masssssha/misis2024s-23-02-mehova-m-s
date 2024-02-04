#include <iostream>
#include <sstream>
#include <limits>
#include <complex/complex.hpp>
Complex Complex::operator-() const noexcept {
  return Complex(-re, -im);
}

//Сложение двух комплексных, комплексное + вещественное
Complex operator+(const Complex& x, const Complex& y) noexcept {
    return Complex(x) += y;
}
Complex operator+(const Complex& x, const double y) noexcept {
    return Complex(x) += Complex(y);
}
Complex operator+(const double x, const Complex& y) noexcept {
    return Complex(x) += Complex(y);
}

//Вычитание двух комплексных, комплексное - вещественное
Complex operator-(const Complex& x, const Complex& y) noexcept {
    return Complex(x) -= y;
}
Complex operator-(const Complex& x, const double y) noexcept {
    return Complex(x) -= Complex(y);
}
Complex operator-(const double x, const Complex& y) noexcept {
    return Complex(x) -= Complex(y);
}

//Умножение двух комплексных, комплексное * вещественное
Complex operator*(const Complex& x, const Complex& y) noexcept {
    return Complex(x) *= y;
}
Complex operator*(const Complex& x, const double y) noexcept {
    return Complex(x) *= Complex(y);
}
Complex operator*(const double x, const Complex& y)noexcept {
    return Complex(x) *= Complex(y);
}

//Деление двух комплексных, комплексное / вещественное
Complex operator/(const Complex& x, const Complex& y) {
    return Complex(x) /= y;
}
Complex operator/(const Complex& x, const double y) {
    return Complex(x) /= Complex(y);
}
Complex operator/(const double x, const Complex& y) {
    return Complex(x) /= Complex(y);
}

Complex::Complex(const double real, const double imaginary) : re(real), im(imaginary) {}
Complex::Complex(const double real) : re(real) {}

Complex& Complex::operator+=(const Complex& x) noexcept {
    re += x.re;
    im += x.im;
    return *this;
}

Complex& Complex::operator+=(const double x) noexcept {
  re += x;
  return *this;
}

Complex& Complex::operator-=(const Complex& x) noexcept {
    re -= x.re;
    im -= x.im;
    return *this;
}

Complex& Complex::operator-=(const double x) noexcept {
  re -= x;
  return *this;
}

Complex& Complex::operator*=(const Complex& x) noexcept {
    double re1((*this).re);
    double im1((*this).im);
    re = re1 * x.re - im1 * x.im;
    im = re1 * x.im + im1 * x.re;
    return *this;
}

Complex& Complex::operator*=(const double x) noexcept {
  return (*this *= Complex(x));
}

Complex& Complex::operator/=(const Complex& x) {
    double re1((*this).re);
    double im1((*this).im);
    if (x.re * x.re + x.im * x.im == 0) {
      throw std::invalid_argument("Zero denumenator in Complex");
    }
    re = (re1 * x.re + im1 * x.im) / (x.re * x.re + x.im * x.im);
    im = (im1 * x.re - re1 * x.im) / (x.re * x.re + x.im * x.im);
    return *this;
}

Complex& Complex::operator/=(const double x) {
  return (*this /= Complex(x));
}

std::istream& Complex::ReadFrom(std::istream& istrm) noexcept {
  char leftBrace(0);
  double real(0.0);
  char comma(0);
  double imaganary(0.0);
  char rightBrace(0);

  istrm >> leftBrace >> real >> comma >> imaganary >> rightBrace;

  if (istrm.good()) {
    if ((Complex::leftBrace == leftBrace) && (Complex::separator == comma)
      && (Complex::rightBrace == rightBrace)) {
      re = real;
      im = imaganary;
    }
    else {
      istrm.setstate(std::ios_base::failbit);
    }
  }
  return istrm;
}

std::ostream& Complex::WriteTo(std::ostream& ostrm) const noexcept {
    ostrm << leftBrace << re << separator << im << rightBrace;
    return ostrm;
}
