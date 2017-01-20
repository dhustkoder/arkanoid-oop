#ifndef GPROJ_ARRAY_HPP_
#define GPROJ_ARRAY_HPP_
#include <stdlib.h>
#include <assert.h>
#include "array_type.hpp"

namespace gp {

template<class T>
const T& Array<T>::operator[](const long index) const
{
	assert(index < this->size);
	return this->data[index];
}


template<class T>
T& Array<T>::operator[](const long index)
{
	assert(index < this->size);
	return this->data[index];
}


template<class T>
const T* Array<T>::cbegin() const
{
	return &this->data[0];
}


template<class T>
const T* Array<T>::cend() const
{
	return &this->data[0] + this->size;
}


template<class T>
T* Array<T>::begin()
{
	return &this->data[0];
}


template<class T>
T* Array<T>::end()
{
	return &this->data[0] + this->size;
}

template<class T>
Array<T>::Array(Array&& arr)
	: data(arr.data), 
	size(arr.size), 
	capacity(arr.capacity)
{
	arr.data = nullptr;
	arr.size = 0;
	arr.capacity = 0;
}


template<class T>
Array<T>& Array<T>::operator=(Array&& arr)
{
	T* const data_aux = this->data;
	const long size_aux = this->size;
	const long cap_aux = this->capacity;

	this->data = arr.data;
	this->size = arr.size;
	this->capacity = arr.capacity;

	arr.data = data_aux;
	arr.size = size_aux;
	arr.capacity = cap_aux;
	arr.~Array();
}


template<class T>
Array<T>::~Array()
{
	if (this->data)
		free(this->data);
}


template<class T>
Array<T> make_array()
{
	Array<T> arr;
	arr.data = static_cast<T*>(malloc(sizeof(T)));
	assert(arr.data != nullptr);
	arr.size = 0;
	arr.capacity = 1;
	return arr;
}


template<class T>
void resize(const long newsize, Array<T>* const arr)
{
	arr->data = static_cast<T*>(realloc(arr->data, sizeof(T) * newsize));
	assert(arr->data != nullptr);
	arr->capacity = newsize;
}


template<class T>
void push(const T& elem, Array<T>* const arr)
{
	if (arr->size == arr->capacity) {
		assert(arr->size < LONG_MAX);
		resize(arr->size + 1, arr);
	}

	arr->data[arr->size++] = elem;
}


template<class T>
T pop(Array<T>* const arr)
{
	return arr->data[--arr->size];
}


template<class T>
void clear(Array<T>* const arr)
{
	arr->size = 0;
}


}
#endif
