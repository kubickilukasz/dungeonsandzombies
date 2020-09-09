#pragma once

#ifndef SINGLETON
#define SINGLETON

template <class T>
class Singleton{
private:

	static T* _instance;

	template <class T>
	Singleton() {};

	template <class T>
	Singleton(Singleton const&) {};

	template <class T>
	Singleton& operator=(Singleton const&) {};

protected:

	~Singleton();

public:

	static T* instance() {

		if (_instance == nullptr) {

			_instance = new T();
		}

		return _instance;
	}

	void remove();


};

template <class T> T* Singleton<T>::_instance = nullptr;

#endif
