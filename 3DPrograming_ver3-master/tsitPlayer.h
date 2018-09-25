#pragma once

#include "CollisionSphere.h"

class tsitPlayer : public CollisionSphere
{
public:
	enum MOVE
	{
		STOP,		//停止
		FORWARD,	//前進
		BACK,		//後退
		RIGHT_TURN,	//右回転
		LEFT_TURN,	//左回転
		ATTACK,		//攻撃
	};

private:
	//向き
	float m_direction;

	//移動フラグ
	MOVE m_moveFlag;

	int m_moveCount;

	//HP
	float m_Hp;

	Vector3 m_start;
public:

	//コンストラクタ
	tsitPlayer();

	//更新
	bool Update(float elapsedTime) override;

	//描画
	void Render() override;

	//移動する関数
	void Move(MOVE move);

	int GetMoveCount();

	Vector3 getPos();

	float Getdirection();

	float GetHp();

	void SubHp(float hp);

	void SetStatus();

	Quaternion GetRotation();
};