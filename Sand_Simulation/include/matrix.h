#pragma once
#include <iostream>
#include <stdint.h>

template <class T>
class Matrix {
public:
	// Constructors
	Matrix();
	Matrix(int width, int height);
	Matrix(int width, int height, T value);
	
	// Destructor
	~Matrix();
	
	// Acess funcions
	void set(T value);
	void set(int x, int y, T value);
	int getSize();
	T get(int x, int y);
	T* raw();

private:
	int m_size, m_width, m_height;
	T* m_data;
};

template <class T>
Matrix<T>::Matrix() {
	m_size = 0;
	m_width = 0;
	m_height = 0;
	m_data = nullptr;
}

template <class T>
Matrix<T>::Matrix(int width, int height) 
	: m_width(width), m_height(height) {
	m_size = m_width * m_height;
	m_data = new T[m_width * m_height];
	memset(m_data, NULL, m_width * m_height * sizeof(T));
}

template <class T>
Matrix<T>::Matrix(int width, int height, T value)
	: m_width(width), m_height(height) {
	m_size = m_width * m_height;
	m_data = new T[m_width * m_height];
	memset(m_data, value, m_width * m_height * sizeof(T));
}

template <class T>
Matrix<T>::~Matrix() {
	delete[] m_data;
}

template <class T>
void Matrix<T>::set(T value) {
	memset(m_data, value, m_width * m_height * sizeof(T));
}

template <class T>
void Matrix<T>::set(int x, int y, T value) {
	int addr = (y * m_width) + x;
	m_data[addr] = value;
}

template <class T>
int Matrix<T>::getSize() {
	return m_size;
}

template <class T>
T Matrix<T>::get(int x, int y) {
	int addr = (y * m_width) + x;
	return m_data[addr];
}

template <class T>
T* Matrix<T>::raw() {
	return m_data;
}

