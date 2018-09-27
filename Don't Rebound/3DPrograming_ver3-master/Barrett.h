#pragma once

#include "CollisionSphere.h"
#include "DebugCamera.h"

class Barrett : public CollisionSphere
{
public:

private:
	//向き
	float m_direction;

	//攻撃の間隔
	int m_moveCount;

	//初期位置
	Vector3 m_start;

	//Attackフラグ
	bool Attack;

public:
	
	//コンストラクタ
	Barrett();

	//更新
	bool Update(DirectX::SimpleMath::Quaternion rot, DirectX::SimpleMath::Vector3 pos,float dir);

	//描画
	void Render() override;

	//攻撃する時にtrueにする
	void setAttack(bool set);
};