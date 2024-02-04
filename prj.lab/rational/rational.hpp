#ifndef RATIONAL_HPP
#define RATIONAL_HPP

#include <iosfwd>
#include <sstream>

class Rational {
	public:
		Rational() = default;
		~Rational() = default;
		Rational(const Rational& x) = default;
		Rational(const std::int64_t& first, const std::int64_t& second);
		Rational(const std::int64_t& first);
		Rational& operator=(const Rational&) = default;

		std::int64_t num() const noexcept { return num_; }
		std::int64_t den() const noexcept { return den_; }

		std::istream& readFrom(std::istream& istrm) noexcept;
		std::ostream& writeTo(std::ostream& ostrm) const noexcept;
		bool operator==(const Rational& x) const noexcept { return num_ * x.den_ - x.num_ * den_ == 0; }
		bool operator!=(const Rational& x) const noexcept { return !operator==(x); }
		bool operator>(const Rational& x) const noexcept { return num_ * x.den_ - x.num_ * den_ > 0; }
		bool operator<(const Rational& x) const noexcept { return num_ * x.den_ - x.num_ * den_ < 0; }
		bool operator>=(const Rational& x) const noexcept { return num_ * x.den_ - x.num_ * den_ >= 0; }
		bool operator<=(const Rational& x) const noexcept { return num_ * x.den_ - x.num_ * den_ <= 0; }
		Rational operator-() const noexcept { return { -num_, den_ }; }
		Rational& operator+=(const Rational& x) noexcept;
		Rational& operator-=(const Rational& x) noexcept;
		Rational& operator*=(const Rational& x) noexcept;
		Rational& operator/=(const Rational& x);
		Rational& operator+=(const int64_t x) noexcept;
		Rational& operator-=(const int64_t x) noexcept;
		Rational& operator*=(const int64_t x) noexcept;
		Rational& operator/=(const int64_t x);
	private:
		std::int64_t num_ = 0;
		std::int64_t den_ = 1;
		std::int64_t nod(const std::int64_t& x, const std::int64_t& y) {
			std::int64_t a = std::max(std::abs(x), std::abs(y));
			std::int64_t b = std::min(std::abs(x), std::abs(y));
			if (b == 0) {
				den_ = 1;
				return 1;
			}
			while (a != b) {
				a -= b;
				std::int64_t temp = a;
				a = std::max(temp, b);
				b = std::min(temp, b);
			}
			return b;
		}
		void norm() {
			auto ans = nod(std::abs(num_), std::abs(den_));
			if (den_ < 0) {
				num_ *= (-1);
				den_ *= (-1);
			}
			num_ /= ans;
			den_ /= ans;
		}
};

Rational operator+(const Rational& x, const Rational& y) noexcept;
Rational operator+(const Rational& x, const int64_t y) noexcept;
Rational operator+(const int64_t x, const Rational& y) noexcept;
Rational operator-(const Rational& x, const Rational& y) noexcept;
Rational operator-(const Rational& x, const int64_t y) noexcept;
Rational operator-(const int64_t x, const Rational& y) noexcept;
Rational operator*(const Rational& x, const Rational& y) noexcept;
Rational operator*(const Rational& x, const int64_t y) noexcept;
Rational operator*(const int64_t x, const Rational& y) noexcept;
Rational operator/(const Rational& x, const Rational& y);
Rational operator/(const Rational& x, const int64_t y);
Rational operator/(const int64_t x, const Rational& y);

inline std::istream& operator>>(std::istream& istrm, Rational& x) noexcept {
	return x.readFrom(istrm);
}

inline std::ostream& operator<<(std::ostream& ostrm, Rational& x) noexcept {
	return x.writeTo(ostrm);
}

#endif
