#pragma once
#include "Monster.h"
#include "Barrett.h"
#include "Collision.h"

class Bos :public Monster
{
public:
	Bos(Game* game);
	~Bos();

	bool Update(float elapsedTime);

	void Render();

	Collision::Sphere GetBarrettCollision();

	void StopBarrettAttack();

private:
	//�e�N���X
	std::unique_ptr<Barrett> m_Barrett;

	int m_AttackInterval;
};