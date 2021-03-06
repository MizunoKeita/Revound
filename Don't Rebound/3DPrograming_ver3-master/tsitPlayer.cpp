#include "pch.h"
#include "tsitPlayer.h"
#include "Game.h"
#include "Math.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

tsitPlayer::tsitPlayer() :m_direction(0.0f), m_moveFlag(STOP)
{
	m_moveCount = 0;
	m_Hp = 100.0f;
	m_start = Vector3(-5.0f, 0.0f, -5.0f);
	m_position = m_start;
}

bool tsitPlayer::Update(float elapsedTime)
{
	//速度
	Vector3 v;

	switch (m_moveFlag)
	{
	case FORWARD:		//前進
		v.z = 0.1f;
		break;	 
	case BACK:			//後退
		v.z = -0.1f;
		break;	 
	case RIGHT_TURN:	//右回転
		m_direction -= XMConvertToRadians(1.0f);
		break;
	case LEFT_TURN:		//左回転
		m_direction += XMConvertToRadians(1.0f);
		break;
	case ATTACK:		//攻撃
		v.z = 0.5f;
		break;
	default:
		break;
	}

	//プレイヤーを移動させる
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_direction);
	v = Vector3::Transform(v, m_rotation);
	m_position += v;

	//移動制限
	if (Math::Distance<float>(m_position.x, 0.0f) >= 50.0f)
	{
		m_position.x -= v.x;
	}
	if (Math::Distance<float>(m_position.z, 0.0f) >= 50.0f)
	{
		m_position.z -= v.z;
	}

	//移動フラグをリセットする
	m_moveFlag = STOP;

	//ワールド行列の作成
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);

	return true;
}

void tsitPlayer::Render()
{
	if (m_game&&m_model)
	{
		//モデルを描画
		m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, m_game->GetView(), m_game->GetProjection());
	}
}

void tsitPlayer::Move(MOVE move)
{
	m_moveFlag = move;
	//攻撃しているなら攻撃フラグを立てる
	if (move == ATTACK)
	{
		m_moveCount = 1;
	}
	else
	{
		m_moveCount = 0;
	}
}

int tsitPlayer::GetMoveCount()
{
	return m_moveCount;
}

Vector3 tsitPlayer::getPos()
{
	return m_position;
}

float tsitPlayer::Getdirection()
{
	return m_direction;
}

float tsitPlayer::GetHp()
{
	return m_Hp;
}

void tsitPlayer::SubHp(float hp)
{
	if (m_Hp > 0.0f)
	{
		m_Hp -= hp;
	}
}

void tsitPlayer::SetStatus()
{
	m_moveCount = 0;
	m_Hp = 100.0f;
	m_position = m_start;
}

Quaternion tsitPlayer::GetRotation()
{
	return m_rotation;
}
