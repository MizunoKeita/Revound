#pragma once
#include "CollisionSphere.h"

class Monster :public CollisionSphere
{
public:
	//�R���X�g���N�^
	Monster();

	//�v���C���[�̍��W��ۑ�
	Vector3 m_PlayerPosStorage;

	//�v���C���[�̉�]��ۑ�
	Quaternion m_PlayerRotStorage;
	
	//�v���C���[�̔��a��ۑ�
	float m_PlayerRadiusStorage;

	//�ǔ���
	Vector3 m_TrackingPos;

	//�v���C���[�̕��̌���
	Vector2 m_Dir;

	//�ǔ��������
	float m_TrackingDir;

	//�ǔ��������
	float m_TrackingDirLast;

	//�~����
	float m_PI;

	//���o�t���O
	bool m_WitnessFlag;

	//�����_���ōs������
	Vector3 m_RandPos;

	//�����_���Ői�ގ���	
	int m_RandTime;

	//�X�V
	bool Update(float elapsedTime);
	
	//�`��
	void Render();

	//���񂾂瓖���蔻���\��������
	void Dead();

	//�����Ԃ�
	void Alive();

	//�v���C���[�̍��W���擾
	void GetPlayerPos(Vector3 pos);

	//�v���C���[�̍��W���擾
	void GetPlayerRot(Quaternion rot);

	//�v���C���[�̔��a���擾
	void GetPlayerRadius(float radius);

	//�����̔���
	bool CircleCollision();

	//�����X�^�[�̃X�s�[�h
	const float MONSTER_SPEED = 0.1f;
};