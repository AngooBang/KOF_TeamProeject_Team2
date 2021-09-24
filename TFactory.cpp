#include "TFactory.h"
template<class T>
T* TFactory<T>::Create()
{
	T* p = new T();
	p.Init();
	return p;
}