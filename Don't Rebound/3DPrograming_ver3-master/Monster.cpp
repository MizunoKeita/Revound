#include "pch.h"
#include "Monster.h"
#include "DebugCamera.h"
#include "Game.h"

Monster::Monster()
{
	m_PlayerPosStorage = Vector3(0, 0, 0);

	m_PI = 3.141592653589793f;

	m_TrackingDir = 0.0f;

	m_TrackingDirLast = 0.0f;

	m_Radius = 16.0f;

	//デバイスの取得
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// エフェクトファクトリー
	EffectFactory fx(device);

	//モデルを取得
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\Monster1.cmo", fx);
}

bool Monster::Update(float elapsedTime)
{
	//プレイヤーと敵の距離を求める
	m_TrackingPos = m_PlayerPosStorage - m_position;
	
	//正規化
	m_TrackingPos.Normalize();

	if (CircleCollision() == true)
	{
		//スピードをかける
		m_position += m_TrackingPos*0.1f;
	}

	//atan2で向きを求める
	m_TrackingDir = atan2(m_PlayerPosStorage.x - m_position.x, m_PlayerPosStorage.z - m_position.z);

	//向きを設定する
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_TrackingDir);

	//ワールド行列
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);

	return true;
}

void Monster::Render()
{
	if (m_game&&m_model)
	{
		if (m_active == true)
		{
			//モデルを描画
			m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
		}
	}
}

void Monster::Dead()
{
	m_active = false;

	m_enable = false;
}

void Monster::Alive()
{
	m_active = true;

	m_enable = true;
}

void Monster::GetPlayerPos(Vector3 pos)
{
	m_PlayerPosStorage = pos;
}

void Monster::GetPlayerRot(Quaternion rot)
{
	m_PlayerRotStorage = rot;
}

void Monster::GetPlayerRadius(float radius)
{
	m_PlayerRadiusStorage = radius;
}

bool Monster::CircleCollision()
{
	// X座標の距離を求める->二乗することによって正の値にする
	int dx = m_PlayerPosStorage.x - m_position.x;
	int dx2 = dx * dx;

	// Y座標の距離を求める->二乗することによって正の値にする
	int dz = m_PlayerPosStorage.z - m_position.z;
	int dz2 = dz * dz;

	// オブジェクトAとオブジェクトBの距離を求める
	int d2 = (dx2 + dz2);

	// オブジェクトAの半径とオブジェクトBの半径を足す->二乗することでd2と比べられるようになる
	int r = m_PlayerRadiusStorage + m_Radius;
	int r2 = r * r;

	// A,Bの距離よりA半径+B半径のほうが大きかったら
	if (r2 > d2)
	{
		//当たった
		return true;
	}
	else
	{
		return false;
	}
	
}