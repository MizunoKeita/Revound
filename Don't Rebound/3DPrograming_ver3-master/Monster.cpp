#include "pch.h"
#include "Monster.h"
#include "DebugCamera.h"
#include "Game.h"
#include "Math.h"

Monster::Monster()
{
	//�f�o�C�X�̎擾
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// �G�t�F�N�g�t�@�N�g���[
	EffectFactory fx(device);

	//���f�����擾
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\Monster1.cmo", fx);
}

void Monster::Render()
{
	if (m_game&&m_model)
	{
		//���f����`��
		m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
	}
}