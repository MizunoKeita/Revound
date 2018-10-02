#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Game;

class Obj3D
{
public:
	//モデルハンドル
	std::unique_ptr<Model> m_model;

protected:

	//ゲームオブジェクトへのポインタ
	Game* m_game;

	//位置
	Vector3 m_position;

	//回転
	Quaternion m_rotation;

	//半径
	float m_Radius;

	//ワールド行列
	Matrix m_world;

public:
	//コンストラクタ
	Obj3D();

	//更新
	virtual bool Update(float elapsedTime);

	//描画
	virtual void Render();

	//アクティブを取得する
	bool GetActive();

	//ゲームオブジェクトを設定する関数
	void SetGame(Game* game) { m_game = game; }

	//位置を設定する関数
	void SetPosirion(Vector3 position) { m_position = position; }

	//回転を設定する関数
	void SetRotation(Quaternion rotation) { m_rotation = rotation; }

	bool m_active;
};