#include "Vector.h"

template class Vector<int>;
template class Vector<float>;

template <class T>
Vector<T>::Vector(): x(0), y(0){ }

template <class T>
Vector<T>::Vector(const T x,const T y) : x(x), y(y){ }

template <class T>
Vector<T>::Vector(Vector<T> v1, Vector<T> v2) {
	x = v1.x - v2.x;
	y = v1.y - v2.y;
}

template <class T>
float Vector<T>::length() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

template <class T>
float Vector<T>::distance(Vector<T> v1, Vector<T> v2) {
	return sqrt( pow(v1.x - v2.x , 2) + pow(v1.y - v2.y, 2));
}

template <class T>
float Vector<T>::distance(Vector<T> v) {
	return Vector<T>::distance(*this , v);
}

template <class T>
Vector<T> Vector<T>::sum(Vector<T> v1, Vector<T> v2) {
	return Vector<T>(v1.x + v2.x , v1.y + v2.y);
}

template <class T>
Vector<T> Vector<T>::sum(Vector<T> v) {
	return Vector<T>::sum(*this , v);
}

template <class T>
Vector<T> Vector<T>::sub(Vector<T> v1, Vector<T> v2) {
	return Vector<T>(v1 , v2);
}

template <class T>
Vector<T> Vector<T>::sub(Vector<T> v) {
	return Vector<T>(*this, v);
}

template <class T>
float Vector<T>::scalar(Vector<T> v1, Vector<T> v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

template <class T>
float Vector<T>::scalar(Vector<T> v) {
	return Vector<T>::scalar(*this , v);
}

template <class T>
float Vector<T>::angle(Vector<T> v1, Vector<T> v2) {
	float scalar = Vector<T>::scalar(v1, v2);
	float det = v1.x * v2.y - v1.y * v2.x;
	return atan2f(det, scalar) * (180.0 / 3.141592653589793238463);
}

template <class T>
float Vector<T>::angle(Vector<T> v) {
	return Vector<T>::angle(*this , v);
}

template <class T>
float Vector<T>::operator *(Vector<T> v) {
	return Vector<T>::scalar(*this, v);
}

template <class T>
Vector<T> Vector<T>::operator *(float s) {
	return Vector<T>(this->x * s, this->y * s);
}

template <class T>
Vector<T> Vector<T>::operator +(Vector<T> v) {
	return Vector<T>::sum(*this, v);
}

template <class T>
Vector<T> Vector<T>::operator -(Vector<T> v) {
	return Vector<T>::sub(*this, v);
}

template <class T>
Vector<T> Vector<T>::Normalize() {
	if (x == 0 && y == 0){
		return *this;

	}else {

		float length = this->length();
		return Vector<T>((T)(x / length), (T)(y / length));
	}
	
}


