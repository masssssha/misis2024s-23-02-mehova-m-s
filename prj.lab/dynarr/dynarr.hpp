#ifndef DYNARR_HPP
#define	DYNARR_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <utility>

class DynArr {
public:
	DynArr() = default;
	DynArr(const DynArr& x);    //done
	DynArr(const std::ptrdiff_t s);     //done
	~DynArr();                          //done
	DynArr(DynArr&& x) noexcept;
	std::ptrdiff_t Size() const;
	void Resize(const std::ptrdiff_t s);
	DynArr& operator=(const DynArr& x);
	DynArr& operator=(DynArr&& x) noexcept;
	float& operator[](const std::ptrdiff_t i);        //done
	const float& operator[](const std::ptrdiff_t i) const;    //done
	std::ptrdiff_t capacity() const noexcept {
		return capacity_;
	}
private:
	std::ptrdiff_t size_ = 0;
	std::ptrdiff_t capacity_ = 0;
	float* data_ = nullptr;
};

#endif
