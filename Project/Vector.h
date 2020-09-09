#pragma once
#include <math.h>
#include <iostream>

#ifndef VECTOR
#define VECTOR

template <class T>
class Vector
{
private:

	

public: 

	T x;
	T y;

	Vector();
	Vector(const T x,const T y); 
	Vector(Vector<T> v1, Vector<T> v2);

	float length();

	static float distance(Vector<T> v1, Vector<T> v2);

	float distance(Vector<T> v);

	static Vector<T> sum(Vector<T> v1, Vector<T> v2);

	Vector<T> sum(Vector<T> v);

	static Vector<T> sub(Vector<T> v1, Vector<T> v2);

	Vector<T> sub(Vector<T> v);

	static float scalar(Vector<T> v1, Vector<T> v2);

	float scalar(Vector<T> v);

	static float angle(Vector<T> v1, Vector<T> v2);

	float angle(Vector<T> v);

	float operator *(Vector<T> v);

	Vector<T> operator *(float s);

	Vector<T> operator +(Vector<T> v);

	Vector<T> operator -(Vector<T> v);

	Vector<T> Normalize();

};

typedef Vector<int> VectorInt;
typedef Vector<float> VectorFloat;

#endif

