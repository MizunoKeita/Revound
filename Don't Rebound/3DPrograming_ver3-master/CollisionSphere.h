#pragma once

#include "Obj3D.h"
#include "Collision.h"
#include "DebugSphere.h"

class CollisionSphere :public Obj3D
{
private:
	//�R���W�������
	Collision::Sphere m_collision;
	
public:

	//�R���W�����\���I�u�W�F�N�g
	Collision::Sphere GetCollision();

	//�R���W�������̐ݒ�֐�
	void SetCollision(Collision::Sphere sphere);

	//Debug�p�R���W�����\���֐�
	void DrawCollision();

	//��Ԃ�ݒ肷��
	void SetEnable(int enable);

	//��Ԃ��擾����
	int GetEnable();

	std::unique_ptr<DebugSphere> m_obj;

	bool m_enable;
};