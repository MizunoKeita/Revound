#pragma once
#include "CollisionSphere.h"

class Monster :public CollisionSphere
{
public:

	//�R���X�g���N�^
	Monster();

	//�`��
	void Render();

	//���񂾂瓖���蔻���\��������
	void Dead();

	//�����Ԃ�
	void Alive();
};