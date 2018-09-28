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

	const float MONSTER_SPEED = 0.1f;
};