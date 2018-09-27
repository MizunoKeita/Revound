#pragma once
#include "CollisionSphere.h"

class Monster :public CollisionSphere
{
public:

	//コンストラクタ
	Monster();

	//描画
	void Render();

};