#pragma once

#include <iostream>
namespace
{
	const size_t DEFAULT_CAP = 8;
}
template <typename T>
class Vector
{
	T* data;
	size_t size = 0;
	size_t capacity = DEFAULT_CAP;

	void copyFrom(const Vector<T>& other);
	void free();
	void moveFrom(Vector<T>&& other);
	void resize(size_t newCap);

public:
	Vector();
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector<T>();

	size_t getCount() const;
	size_t getCapacity() const;

	void push_back(const T& _data);
	void push_back(T&& _data);
	void pop_back();
	void insert(const T& _data, unsigned idx);
	void insert(T&& _data, unsigned idx);
	void remove(unsigned idx);
	void clear();

	bool empty() const;
	T& operator[](const size_t idx);
	const T& operator[](const size_t idx) const;

};
template <typename T>
void Vector<T>::copyFrom(const Vector<T>& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];
	for (int i = 0; i < size; i++) {
		data[i] = other.data[i];
	}
}

template <typename T>
void Vector<T>::free()
{
	delete[] data;
	data = nullptr;
	capacity = size = 0;
}

template <typename T>
void Vector<T>::moveFrom(Vector<T>&& other)
{
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
	other.capacity = other.size = 0;
}

template <typename T>
void Vector<T>::resize(size_t newCap)
{
	capacity = newCap;
	T* temp = new T[newCap];
	for (int i = 0; i < size; i++) {
		temp[i] = std::move(data[i]);
	}
	delete[] data;
	data = temp;
}

template <typename T>
Vector<T>::Vector()
{
	data = nullptr;
	size = capacity = 0;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	copyFrom(other);
}

template <typename T>
Vector<T>::Vector(Vector<T>&& other)
{
	moveFrom(std::move(other));
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template <typename T>
Vector<T>::~Vector<T>()
{
	free();
}


template <typename T>
size_t Vector<T>::getCount() const
{
	return size;
}

template <typename T>
size_t Vector<T>::getCapacity() const
{
	return capacity;
}


template <typename T>
void Vector<T>::push_back(const T& _data)
{
	if (capacity == 0) {
		resize(DEFAULT_CAP);
	}
	if (size == capacity) {
		resize(2 * capacity);
	}
	data[size++] = _data;
}

template <typename T>
void Vector<T>::push_back(T&& _data)
{
	if (capacity == 0) {
		resize(DEFAULT_CAP);
	}
	if (size == capacity) {
		resize(2 * capacity);
	}
	data[size++] = std::move(_data);
}

template <typename T>
void Vector<T>::pop_back()
{
	if (empty()) {
		throw std::exception("Empty vector");
	}

	size--;
}

template <typename T>
void Vector<T>::insert(const T& _data, unsigned idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}

	if (size == capacity) {
		resize(2 * capacity);
	}

	size++;
	for (int i = size - 1; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}
	data[idx] = _data;
}

template <typename T>
void Vector<T>::insert(T&& _data, unsigned idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}

	if (size == capacity) {
		resize(2 * capacity);
	}

	size++;
	for (int i = size - 1; i > idx; i--) {
		data[i] = std::move(data[i - 1]);
	}
	data[idx] = std::move(_data);
}
template <typename T>
void Vector<T>::remove(unsigned idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}

	for (int i = idx; i < size - 1; i++) {
		data[i] = std::move(data[i + 1]);
	}
	size--;
	if (size == capacity / 4) {
		resize(capacity / 2);
	}
}

template <typename T>
void Vector<T>::clear()
{
	delete[] data;
	size = 0;
	capacity = DEFAULT_CAP;
	data = new T[capacity];
}


template <typename T>
bool Vector<T>::empty() const
{
	return size == 0;
}

template <typename T>
T& Vector<T>::operator[](const size_t idx)
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}
	return data[idx];
}

template <typename T>
const T& Vector<T>::operator[](const size_t idx) const
{
	if (idx >= size) {
		throw std::out_of_range("Index out of range");
	}
	return data[idx];
}