#include "TFactory.h"
template<class T>
static T* TFactory<T>::Create()
{
	T* p = new T();
	p->Init();
	return p;
}