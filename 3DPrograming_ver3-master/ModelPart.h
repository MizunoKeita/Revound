#pragma once
#include "pch.h"

// ���f���p�[�c�\����
struct ModelPart
{
	// ���f���n���h��
	DirectX::Model* model = nullptr;

	// ���[���h�s��
	DirectX::SimpleMath::Matrix world;

	// �ϊ��s��
	DirectX::SimpleMath::Matrix transform;

	// �����ʒu�s��
	DirectX::SimpleMath::Matrix initial;

	// �q�ւ̃|�C���^
	ModelPart* child = nullptr;

	// �Z��ւ̃|�C���^
	ModelPart* sibling = nullptr;

	// �e�p�[�c�̏����ʒu�s���e�̍��W�n�ɕϊ�����֐�
	static void SetupMatrix(ModelPart* parts, DirectX::SimpleMath::Matrix* offset)
	{
		if (parts->child) SetupMatrix(parts->child, &parts->initial.Invert());
		if (parts->sibling) SetupMatrix(parts->sibling, offset);
		if (offset) parts->initial *= *offset;
	}

	// �e�p�[�c�̃��[���h�s����X�V����֐�
	static void UpdateMatrix(ModelPart* parts, DirectX::SimpleMath::Matrix* parent)
	{
		parts->world = parts->transform * parts->initial;
		parts->world *= *parent;
		if (parts->child) UpdateMatrix(parts->child, &parts->world);
		if (parts->sibling) UpdateMatrix(parts->sibling, parent);
	}
};
