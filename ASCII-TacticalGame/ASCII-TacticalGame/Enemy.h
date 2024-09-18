#pragma once

#include "Character.h"

class Enemy : public Character
{
public:

	Enemy();
	virtual ~Enemy();

	void Update() override;

public:

	template<typename T>
	static T* Create();
	void GetEnemyNearby(Coordinates position) override;
	
};

template<typename T>
inline T* Enemy::Create()
{
	T* enemy = new T();
	I(Game)->AddObject(enemy);
	return enemy;
}
