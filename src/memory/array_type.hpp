#ifndef GPROJ_ARRAY_TYPE_HPP_
#define GPROJ_ARRAY_TYPE_HPP_

namespace gp {

template<class T>
struct Array {
	T* data;
	int size;
	int capacity;

	Array(const Array&) = delete;
	Array& operator=(const Array&) = delete;

	Array() = default;
	Array(Array&&);
	Array& operator=(Array&&);

	~Array();

	const T* cbegin() const;
	const T* cend() const;
	const T* begin() const;
	const T* end() const;
	T* begin();
	T* end();

	const T& operator[](int index) const;
	T& operator[](int index);
};



}
#endif
