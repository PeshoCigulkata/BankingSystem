#pragma once
#include <iostream>

template<typename T>
class Vector {
private:
	static constexpr size_t min_cap = 16;
	static constexpr size_t growth = 2;
	size_t capacity = min_cap;
	size_t count = 0;
	T* data = nullptr;
	void free();
	void copyFrom(const Vector<T>& other);
	void moveFrom(Vector<T>&& other);
	void resize(size_t newCap);
	Vector(size_t startCapacity);
public:
	Vector();
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	Vector<T>& operator=(const Vector<T>& other);
	Vector<T>& operator=(Vector<T>&& other);
	~Vector();
	void push_back(const T& elem);
	void push_back(T&& elem);
	void insert(size_t at, const T& elem);
	void insert(size_t at, T&& elem);
	void remove(size_t at);
	const T& operator[](size_t at) const;
	T& operator[](size_t at);
	size_t getCount() const;
	size_t getCapacity() const;
};
template<typename T>
void Vector<T>::free() {
	delete[] data;
	data = nullptr;
}
template<typename T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	capacity = other.capacity;
	count = other.count;
	data = new T[capacity];
	for (size_t i = 0; i < count; ++i) {
		data[i] = other.data[i];
	}
}
template<typename T>
void Vector<T>::moveFrom(Vector<T>&& other) {
	capacity = other.capacity;
	count = other.count;
	data = other.data;
	other.data = nullptr;
	other.count = 0;
	other.capacity = 0;
}
template<typename T>
void Vector<T>::resize(size_t newCap) {
	T* tmp = new T[newCap];
	for (size_t i = 0; i < count; ++i) {
		tmp[i] = std::move(data[i]);
	}
	delete[] data;
	data = tmp;
	capacity = newCap;
}
template<typename T>
Vector<T>::Vector(size_t startCapacity) {
	capacity = std::max(startCapacity, min_cap);
	data = new T[capacity];
	count = 0;
}
template<typename T>
Vector<T>::Vector() : Vector(0) {}
template<typename T>
Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}
template<typename T>
Vector<T>::Vector(Vector<T>&& other) {
	moveFrom(std::move(other));
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
template<typename T>
Vector<T>::~Vector() {
	free();
}
template <typename T>
void Vector<T>::push_back(const T& elem) {
	if (count >= capacity) {
		resize(capacity * growth);
	}
	data[count++] = elem;
}
template <typename T>
void Vector<T>::push_back(T&& elem) {
	if (count >= capacity) {
		resize(capacity * growth);
	}
	data[count++] = std::move(elem);
}
template<typename T>
void Vector<T>::insert(size_t at, const T& elem) {
	if (at > count) {
		throw std::out_of_range("Vector::Insert index bigger than count");
	}
	if (count >= capacity) {
		resize(capacity * 2);
	}
	for (int i = (int)count - 1; i >= (int)at; --i) {
		data[i + 1] = std::move(data[i]);
	}
	data[at] = elem;
	++count;
}
template<typename T>
void Vector<T>::insert(size_t at, T&& elem) {
	if (at > count) {
		throw std::out_of_range("Vector::Insert index bigger than count");
	}
	if (count >= capacity) {
		resize(capacity * 2);
	}
	for (int i = (int)count - 1; i >= (int)at; --i) {
		data[i + 1] = std::move(data[i]);
	}
	data[at] = std::move(elem);
	++count;
}
template<typename T>
void Vector<T>::remove(size_t at) {
	if (at >= count) {
		throw std::out_of_range("Vector::Not a valid index");
	}
	for (size_t i = at; i < count - 1; ++i) {
		data[i] = std::move(data[i + 1]);
	}
	--count;
	if (count <= capacity / (growth * growth)) {
		resize(std::max(capacity / growth, min_cap));
	}
}
template <typename T>
const T& Vector<T>::operator[](size_t at) const {
	if (at >= count) {
		throw std::out_of_range("Vector::Not a valid index");
	}
	return data[at];
}
template <typename T>
T& Vector<T>::operator[](size_t at) {
	if (at >= count) {
		throw std::out_of_range("Vector::Not a valid index");
	}
	return data[at];
}
template<typename T>
size_t Vector<T>::getCount() const {
	return count;
}
template<typename T>
size_t Vector<T>::getCapacity() const {
	return capacity;
}