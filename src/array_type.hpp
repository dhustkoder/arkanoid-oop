#ifndef GPROJ_ARRAY_TYPE_HPP_
#define GPROJ_ARRAY_TYPE_HPP_

namespace gp {

template<class T>
struct Array {
	T* data;
	long size;
	long capacity;

	Array(const Array&) = delete;
	Array& operator=(const Array&) = delete;

	Array() = default;
	Array(Array&&);
	Array& operator=(Array&&);

	~Array();

	const T* cbegin() const;
	const T* cend() const;
	T* begin();
	T* end();

	const T& operator[](long index) const;
	T& operator[](long index);
};



}
#endif
