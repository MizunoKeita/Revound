#pragma once
#include "CollisionSphere.h"

class Monster :public CollisionSphere
{
public:

	//コンストラクタ
	Monster();

	//描画
	void Render();

	//死んだら当たり判定や表示を消す
	void Dead();

	//生き返る
	void Alive();
};