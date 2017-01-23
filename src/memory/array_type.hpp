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

	Array();
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


template<class T>
void reserve(const long newsize, Array<T>* const arr);
template<class T>
void resize(const long newsize, Array<T>* const arr);
template<class T>
void push_back(const T& elem, Array<T>* const arr);
template<class T>
T pop_back(Array<T>* const arr);
template<class T>
void clear(Array<T>* const arr);


}
#endif
