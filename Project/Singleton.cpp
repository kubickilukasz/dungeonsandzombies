#include "Singleton.h"

template <class T>
Singleton<T>::~Singleton() {
	remove();
}

template <class T>
void Singleton<T>::remove(){

	if (_instance == nullptr) {

		delete _instance;
	}

}


