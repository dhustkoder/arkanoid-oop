#ifndef GPROJ_ARRAY_HPP_
#define GPROJ_ARRAY_HPP_
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "array_type.hpp"

namespace gp {

	
template<class T>
Array<T>::Array() :
	data(nullptr),
	size(0),
	capacity(0)
{
	reserve(1, this);
}


template<class T>
Array<T>::Array(Array&& other)
	: data(other.data), 
	size(other.size), 
	capacity(other.capacity)
{
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}


template<class T>
Array<T>& Array<T>::operator=(Array&& other)
{
	T* const data_aux = this->data;
	const int size_aux = this->size;
	const int cap_aux = this->capacity;

	this->data = other.data;
	this->size = other.size;
	this->capacity = other.capacity;

	other.data = data_aux;
	other.size = size_aux;
	other.capacity = cap_aux;
}


template<class T>
Array<T>::~Array()
{
	if (this->data)
		free(this->data);
}


template<class T>
const T& Array<T>::operator[](const int index) const
{
	assert(index < this->size);
	return this->data[index];
}


template<class T>
T& Array<T>::operator[](const int index)
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
const T* Array<T>::begin() const
{
	return this->cbegin();
}


template<class T>
const T* Array<T>::end() const
{
	return this->cend();
}


template<class T>
T* Array<T>::begin()
{
	return const_cast<T*>(this->cbegin());
}


template<class T>
T* Array<T>::end()
{
	return const_cast<T*>(this->cend());
}


template<class T>
void reserve(const long newsize, Array<T>* const arr)
{
	assert(newsize < INT_MAX);
	arr->data = static_cast<T*>(realloc(arr->data, sizeof(T) * newsize));
	assert(arr->data != nullptr);
	arr->capacity = newsize;
}


template<class T>
void resize(const long newsize, Array<T>* const arr)
{
	reserve(newsize, arr);
	arr->size = newsize;
}


template<class T>
void push_back(const T& elem, Array<T>* const arr)
{
	if (arr->size == arr->capacity) {
		const long cursize = static_cast<long>(arr->size);
		const long newsize = (cursize + 1l) + ((cursize + 1l) / 2l);
		reserve(newsize, arr);
	}

	arr->data[arr->size++] = elem;
}


template<class T>
T pop_back(Array<T>* const arr)
{
	assert(arr->size > 0);
	return arr->data[--arr->size];
}


template<class T>
void clear(Array<T>* const arr)
{
	arr->size = 0;
}


}
#endif

