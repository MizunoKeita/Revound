#pragma once

#include "Obj3D.h"
#include "Collision.h"
#include "DebugSphere.h"

class CollisionSphere :public Obj3D
{
private:
	//コリジョン情報
	Collision::Sphere m_collision;
	
public:

	//コリジョン表示オブジェクト
	Collision::Sphere GetCollision();

	//コリジョン情報の設定関数
	void SetCollision(Collision::Sphere sphere);

	//Debug用コリジョン表示関数
	void DrawCollision();

	//状態を設定する
	void SetEnable(int enable);

	//状態を取得する
	int GetEnable();

	std::unique_ptr<DebugSphere> m_obj;

	bool m_enable;
};