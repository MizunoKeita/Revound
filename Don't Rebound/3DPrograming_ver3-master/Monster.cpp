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

	//�f�o�C�X�̎擾
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[
	EffectFactory fx(device);

	//���f�����擾
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\Monster1.cmo", fx);
}

bool Monster::Update(float elapsedTime)
{
	//�v���C���[�ƓG�̋��������߂�
	m_TrackingPos = m_PlayerPosStorage - m_position;
	
	//���K��
	m_TrackingPos.Normalize();

	//�X�s�[�h��������
	m_position += m_TrackingPos*0.1f;

	//atan2�Ō��������߂�
	m_TrackingDir = atan2(m_PlayerPosStorage.x - m_position.x, m_PlayerPosStorage.z - m_position.z);

	//������ݒ肷��
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_TrackingDir);

	//���[���h�s��
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);

	return true;
}

void Monster::Render()
{
	if (m_game&&m_model)
	{
		if (m_active == true)
		{
			//���f����`��
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

