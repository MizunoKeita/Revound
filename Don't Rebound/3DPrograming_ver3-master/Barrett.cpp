#include "pch.h"
#include "Barrett.h"
#include "Game.h"
#include "Math.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Barrett::Barrett() :m_direction(0.0f)
{
	Attack = false;
	m_moveCount = 0;
	m_start = Vector3(0.0f, 0.0f, 0.0f);
	m_position = m_start;

	//デバイスの取得
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// エフェクトファクトリー
	EffectFactory fx(device);

	//モデルを取得
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\redboll.cmo", fx);
}

bool Barrett::Update(Quaternion rot, Vector3 pos, float dir)
{
	//速度
	Vector3 v;

	//向きを取得
	m_rotation = rot;

	if (Attack == true)
	{
		if (m_moveCount <= 0)
		{
			m_moveCount = 60;
		}
	}
	else if (m_moveCount <= 0)
	{
		m_position = pos + Vector3(0.0f, 2.0f, 0.0f);
	}

	if (m_moveCount > 0)
	{
		v.z = 0.4f;
		m_moveCount--;
	}
	
	if (m_moveCount == 0)
	{
		Attack = false;
	}

	if (m_moveCount > 0)
	{
		//弾を移動させる
		m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), dir);
		v = Vector3::Transform(v, m_rotation);
		m_position += v;
	}
	//ワールド行列の作成
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);

	return true;
}

void Barrett::Render()
{
	if (m_game&&m_model)
	{
		if (Attack == true)
		{
			//モデルを描画
			m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
		}
	}
}

void Barrett::setAttack(bool set)
{
	Attack = set;
}
