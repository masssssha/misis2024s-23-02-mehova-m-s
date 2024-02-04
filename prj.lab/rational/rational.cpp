#include <rational/rational.hpp>

#include <iostream>
#include <sstream>

//�����������
Rational::Rational(const std::int64_t& first, const std::int64_t& second) {
	if (second == 0) {
			throw std::invalid_argument("Zero denumenator in Rational ctor");
	}
	num_ = first;
	den_ = second;
	norm();
}
Rational::Rational(const std::int64_t& first) : num_(first) {}

//����
std::istream& Rational::readFrom(std::istream& istrm) noexcept {
	int64_t num(0);
	char delimiter(0);
	int64_t den(1);
	istrm >> num;
	istrm.get(delimiter);
	int64_t trash = istrm.peek();
	istrm >> den;
	if (!istrm || trash > '9' || trash < '0') {
		istrm.setstate(std::ios_base::failbit);
		return istrm;
	}
	if (istrm.good() || istrm.eof()) {
		if ('/' == delimiter && den > 0) {
			*this = Rational(num, den);
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	return istrm;
}

//�����
std::ostream& Rational::writeTo(std::ostream& ostrm) const noexcept {
	ostrm << num_ << '/' << den_;
	return ostrm;
}

//operator += -= *= /=
Rational& Rational::operator+=(const Rational& x) noexcept {
	std::int64_t num_1 = num_;
	std::int64_t den1 = den_;
	num_ = (num_1 * x.den_) + (x.num_ * den1);
	den_ = den1 * x.den_;
	norm();
	return *this;
}

Rational& Rational::operator+=(const int64_t x) noexcept {
	return operator+=(Rational(x));
}

Rational& Rational::operator-=(const Rational &x) noexcept {
	std::int64_t num_1 = num_;
	std::int64_t den1 = den_;
	num_ = (num_1 * x.den_) - (x.num_ * den1);
	den_ = den1 * x.den_;
	norm();
	return *this;
}

Rational& Rational::operator-=(const int64_t x) noexcept {
	return operator-=(Rational(x));
}

Rational& Rational::operator*=(const Rational& x) noexcept {
	num_ *= x.num_;
	den_ *= x.den_;
	norm();
	return *this;
}

Rational& Rational::operator*=(const int64_t x) noexcept {
	return operator*=(Rational(x));
}

Rational& Rational::operator/=(const Rational& x) {
	if (x.num_ == 0) {
		throw std::invalid_argument("Zero denumenator in Rational ctor");
	}
	num_ *= x.den_;
	den_ *= x.num_;
	norm();
	return *this;
}

Rational& Rational::operator/=(const int64_t x) {
	return operator/=(Rational(x));
}

//operator r + r, d + r, r + d
Rational operator+(const Rational& x, const Rational& y) noexcept {
	return Rational(x) += y;
}
Rational operator+(const Rational& x, const int64_t y) noexcept {
	return Rational(x) += Rational(y);
}
Rational operator+(const int64_t x, const Rational& y) noexcept {
	return Rational(x) += Rational(y);
}

//operator r - r, d - r, r - d
Rational operator-(const Rational& x, const Rational& y) noexcept {
	return Rational(x) -= y;
}
Rational operator-(const Rational& x, const int64_t y) noexcept {
	return Rational(x) -= Rational(y);
}
Rational operator-(const int64_t x, const Rational& y) noexcept {
	return Rational(x) -= Rational(y);
}

//operator r * r, d * r, r * d
Rational operator*(const Rational& x, const Rational& y) noexcept {
	return Rational(x) *= y;
}
Rational operator*(const Rational& x, const int64_t y) noexcept {
	return Rational(x) *= Rational(y);
}
Rational operator*(const int64_t x, const Rational& y) noexcept {
	return Rational(x) *= Rational(y);
}


//operator r / r, d / r, r / d
Rational operator/(const Rational& x, const Rational& y) {
	return Rational(x) /= y;
}
Rational operator/(const Rational& x, const int64_t y) {
	return Rational(x) /= Rational(y);
}
Rational operator/(const int64_t x, const Rational& y) {
	return Rational(x) /= Rational(y);
}
