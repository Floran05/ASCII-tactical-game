#pragma once

#include "Character.h"

class Enemy : public Character
{
public:

	Enemy();
	virtual ~Enemy();

public:

	template<typename T>
	static T* Create();
};

template<typename T>
inline T* Enemy::Create()
{
	return new T();
}
