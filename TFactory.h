#pragma once

template <class T>
class TFactory
{
public:
	TFactory() {}
	~TFactory() {}

	static T* Create();
};


