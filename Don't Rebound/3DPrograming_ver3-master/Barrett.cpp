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
	m_start = Vector3(-5.0f, 0.0f, -5.0f);
	m_position = m_start;
}

bool Barrett::Update(Quaternion rot, Vector3 pos, float dir)
{
	//速度
	Vector3 v;

	//向きを取得
	m_rotation = rot;

	if (Attack == true)
	{
		m_moveCount = 60;
		Attack = false;
	}
	else if (m_moveCount <= 0)
	{
		m_position = pos;
	}

	if (m_moveCount >= 0)
	{
		v.z = 0.4f;
		m_moveCount--;
	}

	//弾を移動させる
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), dir);
	v = Vector3::Transform(v, m_rotation);
	m_position += v;

	//ワールド行列の作成
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);

	return true;
}

void Barrett::Render()
{
	if (m_game&&m_model)
	{
		if (m_moveCount >= 0)
		{
			//モデルを描画
			m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, m_game->GetView(), m_game->GetProjection());
		}
	}
}

void Barrett::setAttack(bool set)
{
	Attack = set;
}
