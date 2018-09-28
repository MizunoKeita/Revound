#pragma once

#include "CollisionSphere.h"
#include "DebugCamera.h"

class Barrett : public CollisionSphere
{
public:

private:
	//����
	float m_direction;

	//�U���̊Ԋu
	int m_moveCount;

	//�����ʒu
	Vector3 m_start;

	//Attack�t���O
	bool Attack;

public:
	
	//�R���X�g���N�^
	Barrett();

	//�X�V
	bool Update(DirectX::SimpleMath::Quaternion rot, DirectX::SimpleMath::Vector3 pos,float dir);

	//�`��
	void Render() override;

	//�U�����鎞��true�ɂ���
	void setAttack(bool set);
};