#include "pch.h"
#include "Obj3D.h"
#include "Game.h"
#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

Obj3D::Obj3D():m_game(nullptr),m_model(nullptr)
{
	m_active = true;
}

bool Obj3D::Update(float elapsedTime)
{
	//���[���h�s��
	m_world = Matrix::CreateFromQuaternion(m_rotation)*Matrix::CreateTranslation(m_position);
	return true;
}

void Obj3D::Render()
{
	if (m_model&&m_game)
	{
		//���f���̕`��
		m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
	}
}

bool Obj3D::GetActive()
{
	return m_active;
}
