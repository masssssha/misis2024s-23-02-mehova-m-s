#include <dynarr/dynarr.hpp>

//copy maker
DynArr::DynArr(const DynArr& x)
	: size_(x.size_) {
	data_ = new float[x.size_];
	for (int i = 0; i < x.size_; i++) {
		*(data_ + i) = *(x.data_ + i);
	}
	capacity_ = size_;
}

//size maker
DynArr::DynArr(const std::ptrdiff_t s)
	: size_(s) {
	if (s <= 0) {
		throw std::invalid_argument("Size must be a positive number");
	}
	data_ = new float[s] {0.0f};
	capacity_ = size_;
}

//crush
DynArr::~DynArr() {
	delete[] data_;
	data_ = nullptr;
	capacity_ = 0;
}

//size
std::ptrdiff_t DynArr::Size() const {
	return size_;
}

void DynArr::Resize(const std::ptrdiff_t s) {
	if (s <= 0) {
		throw std::invalid_argument("Size must be a positive number");
	}
	if (s <= capacity_) {
		if (s > size_) {
			for (std::ptrdiff_t i = size_; i < s; i++) {
				*(data_ + i) = 0.0f;
			}
		}
		size_ = s;
	}	else {
		float* newdata_ = new float[s];
		for (int i = 0; i < s; i++) {
			if (i < (*this).Size()) {
				*(newdata_ + i) = *(data_ + i);
			} else {
				*(newdata_ + i) = 0.0f;
			}
		}
		delete[] data_;
		data_ = newdata_;
		size_ = s;
		capacity_ = s;
	}
}

//[]
float& DynArr::operator[](const std::ptrdiff_t i) {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range");
	}
	return *(data_ + i);
}

const float& DynArr::operator[](const std::ptrdiff_t i) const {
	if (i < 0 || i >= size_) {
		throw std::out_of_range("Index out of range");
	}
	return *(data_ + i);
}
