#include "pch.h"
#include "tsitPlayer.h"
#include "Game.h"
#include "Math.h"
#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

tsitPlayer::tsitPlayer() :m_direction(0.0f), m_moveFlag(STOP)
{
	m_moveCount = 0;
	m_Hp = 100.0f;
	m_start = Vector3(-5.0f, 0.0f, -5.0f);
	m_position = m_start;

	//�f�o�C�X�̎擾
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[
	EffectFactory fx(device);

	m_p_model = Model::CreateFromCMO(device, L"Resources\\Models\\redmen.cmo", fx);
}

bool tsitPlayer::Update(float elapsedTime)
{
	//���x
	Vector3 v;

	switch (m_moveFlag)
	{
	case FORWARD:		//�O�i
		v.z = 0.1f;
		break;	 
	case BACK:			//���
		v.z = -0.1f;
		break;	 
	case RIGHT_TURN:	//�E��]
		m_direction -= XMConvertToRadians(1.0f);
		break;
	case LEFT_TURN:		//����]
		m_direction += XMConvertToRadians(1.0f);
		break;
	case ATTACK:		//�U��
		v.z = 0.5f;
		break;
	default:
		break;
	}

	//�v���C���[���ړ�������
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_direction);
	v = Vector3::Transform(v, m_rotation);
	m_position += v;

	//�ړ�����
	if (Math::Distance<float>(m_position.x, 0.0f) >= 50.0f)
	{
		m_position.x -= v.x;
	}
	if (Math::Distance<float>(m_position.z, 0.0f) >= 50.0f)
	{
		m_position.z -= v.z;
	}

	//�ړ��t���O�����Z�b�g����
	m_moveFlag = STOP;

	//���[���h�s��̍쐬
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);

	return true;
}

void tsitPlayer::Render()
{
	//if (m_game&&m_model)
	if (m_game&&m_p_model)
	{

		// �r���[�s��̍쐬
		DirectX::SimpleMath::Matrix view = DebugCamera::GetView();

		// �v���W�F�N�V�����s��̍쐬
		DirectX::SimpleMath::Matrix projection = DebugCamera::GetProjection();

		//���f����`��
		m_p_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, view, projection);
	}
}

void tsitPlayer::Move(MOVE move)
{
	m_moveFlag = move;
	//�U�����Ă���Ȃ�U���t���O�𗧂Ă�
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
