#include "pch.h"
#include "CollisionSphere.h"
#include "Game.h"
#include "DebugCamera.h"

void CollisionSphere::SetCollision(Collision::Sphere sphere)
{
	//コリジョン情報の設定
	m_collision = sphere;

	m_enable = true;

	if (m_game)
	{
		//Debug用コリジョンモデルの作成
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
		//Debug用コリジョンの描画
		m_obj->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
	}
}

//状態を設定する
void CollisionSphere::SetEnable(int enable)
{
	m_enable = enable;
}

//状態を取得する
int CollisionSphere::GetEnable()
{
	return m_enable;
}

