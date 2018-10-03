#include "pch.h"
#include "Bos.h"
#include "DeviceResources.h"
#include "Game.h"

Bos::Bos(Game* game)
{
	m_PlayerPosStorage = Vector3(0, 0, 0);

	m_PI = 3.141592653589793f;

	m_TrackingDir = 0.0f;

	m_TrackingDirLast = 0.0f;

	m_Radius = 16.0f;

	m_RandTime = 0;

	m_AttackInterval = 60;

	//�f�o�C�X�̎擾
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[
	EffectFactory fx(device);

	//���f�����擾
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\Bos.cmo", fx);

	//�X�t�B�A�̐ݒ�
	Collision::Sphere sphere;

	//�����蔻��̈ʒu�̕ύX
	sphere.center = Vector3(0.0f, 1.0f, 1.5f);

	//�����蔻��̑傫�������߂�
	sphere.radius = 2.0f;

	//�e
	m_Barrett = std::make_unique<Barrett>();
	m_Barrett->SetGame(game);
	m_Barrett->SetCollision(sphere);


}

Bos::~Bos()
{
}

bool Bos::Update(float elapsedTime)
{
	m_AttackInterval--;

	if (m_AttackInterval <= 0)
	{
		m_Barrett->setAttack(true);
		m_AttackInterval = 300;

		//�����_���ɐi�ވʒu�����߂�
		m_RandPos = Vector3(rand() % 50 + 8 - 30, 0.0f, rand() % 50 + 8 - 30);

		//atan2�Ō��������߂�
		m_TrackingDir = atan2(m_RandPos.x - m_position.x, m_RandPos.z - m_position.z);
	}

	//������ݒ肷��
	m_rotation = Quaternion::CreateFromAxisAngle(Vector3(0.0f, 1.0f, 0.0f), m_TrackingDir);

	m_Barrett->Update(m_rotation, m_position, m_TrackingDir);

	//���[���h�s��
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);

	return true;

}

void Bos::Render()
{
	if (m_game&&m_model)
	{
		if (m_active == true)
		{
			//���f����`��
			m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
			m_Barrett->Render();
		}
	}
}

Collision::Sphere Bos::GetBarrettCollision()
{
	return m_Barrett->GetCollision();
}

void Bos::StopBarrettAttack()
{
	m_Barrett->setAttack(false);
}
