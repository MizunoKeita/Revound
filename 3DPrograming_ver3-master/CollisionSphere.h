#pragma once

#include "Obj3D.h"
#include "Collision.h"
#include "DebugSphere.h"

class CollisionSphere :public Obj3D
{
private:
	//�R���W�������
	Collision::Sphere m_collision;
	int m_state;
	
public:

	//�R���W�����\���I�u�W�F�N�g
	Collision::Sphere GetCollision();

	//�R���W�������̐ݒ�֐�
	void SetCollision(Collision::Sphere sphere);

	//Debug�p�R���W�����\���֐�
	void DrawCollision();

	//��Ԃ�ݒ肷��
	void state(int state);

	//��Ԃ��擾����
	int GetState();

	std::unique_ptr<DebugSphere> m_obj;
};