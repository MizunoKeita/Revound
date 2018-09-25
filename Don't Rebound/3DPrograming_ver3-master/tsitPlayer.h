#pragma once

#include "CollisionSphere.h"

class tsitPlayer : public CollisionSphere
{
public:
	enum MOVE
	{
		STOP,		//��~
		FORWARD,	//�O�i
		BACK,		//���
		RIGHT_TURN,	//�E��]
		LEFT_TURN,	//����]
		ATTACK,		//�U��
	};

private:
	//����
	float m_direction;

	//�ړ��t���O
	MOVE m_moveFlag;

	int m_moveCount;

	//HP
	float m_Hp;

	Vector3 m_start;
public:

	//�R���X�g���N�^
	tsitPlayer();

	//�X�V
	bool Update(float elapsedTime) override;

	//�`��
	void Render() override;

	//�ړ�����֐�
	void Move(MOVE move);

	int GetMoveCount();

	Vector3 getPos();

	float Getdirection();

	float GetHp();

	void SubHp(float hp);

	void SetStatus();

	Quaternion GetRotation();
};