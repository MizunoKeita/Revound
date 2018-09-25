#include "pch.h"
#include "CollisionSphere.h"
#include "Game.h"

void CollisionSphere::SetCollision(Collision::Sphere sphere)
{
	//�R���W�������̐ݒ�
	m_collision = sphere;

	m_state = 1;

	if (m_game)
	{
		//Debug�p�R���W�������f���̍쐬
		m_obj = std::make_unique<DebugSphere>(m_game->GetDevice(), m_collision.center, m_collision.radius);
	}
}

Collision::Sphere CollisionSphere::GetCollision()
{
	Collision::Sphere sphere;
	sphere.center = DirectX::SimpleMath::Vector3::Transform(m_collision.center, m_world);
	sphere.radius = m_collision.radius;
	return sphere;
}

void CollisionSphere::DrawCollision()
{
	if (m_game)
	{
		//Debug�p�R���W�����̕`��
		m_obj->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, m_game->GetView(), m_game->GetProjection());
	}
}

//��Ԃ�ݒ肷��
void CollisionSphere::state(int state)
{
	m_state = state;
}

//��Ԃ��擾����
int CollisionSphere::GetState()
{
	return m_state;
}
