#include "pch.h"
#include "CollisionSphere.h"
#include "Game.h"
#include "DebugCamera.h"

void CollisionSphere::SetCollision(Collision::Sphere sphere)
{
	//�R���W�������̐ݒ�
	m_collision = sphere;

	m_enable = true;

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
		m_obj->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
	}
}

//��Ԃ�ݒ肷��
void CollisionSphere::SetEnable(int enable)
{
	m_enable = enable;
}

//��Ԃ��擾����
int CollisionSphere::GetEnable()
{
	return m_enable;
}

