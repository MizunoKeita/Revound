#pragma once
#include "CollisionSphere.h"

class Monster :public CollisionSphere
{
public:
	//コンストラクタ
	Monster();

	//プレイヤーの座標を保存
	Vector3 m_PlayerPosStorage;

	//プレイヤーの回転を保存
	Quaternion m_PlayerRotStorage;
	
	//プレイヤーの半径を保存
	float m_PlayerRadiusStorage;

	//追尾量
	Vector3 m_TrackingPos;

	//プレイヤーの方の向き
	Vector2 m_Dir;

	//追尾する向き
	float m_TrackingDir;

	//追尾する向き
	float m_TrackingDirLast;

	//円周率
	float m_PI;

	//視覚フラグ
	bool m_WitnessFlag;

	//ランダムで行く方向
	Vector3 m_RandPos;

	//ランダムで進む時間	
	int m_RandTime;

	//更新
	bool Update(float elapsedTime);
	
	//描画
	void Render();

	//死んだら当たり判定や表示を消す
	void Dead();

	//生き返る
	void Alive();

	//プレイヤーの座標を取得
	void GetPlayerPos(Vector3 pos);

	//プレイヤーの座標を取得
	void GetPlayerRot(Quaternion rot);

	//プレイヤーの半径を取得
	void GetPlayerRadius(float radius);

	//距離の判定
	bool CircleCollision();

	//モンスターのスピード
	const float MONSTER_SPEED = 0.1f;
};