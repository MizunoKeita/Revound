#pragma once

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Game;

class Obj3D
{
public:
	//���f���n���h��
	std::unique_ptr<Model> m_model;

protected:

	//�Q�[���I�u�W�F�N�g�ւ̃|�C���^
	Game* m_game;

	//�ʒu
	Vector3 m_position;

	//��]
	Quaternion m_rotation;

	//���a
	float m_Radius;

	//���[���h�s��
	Matrix m_world;

public:
	//�R���X�g���N�^
	Obj3D();

	//�X�V
	virtual bool Update(float elapsedTime);

	//�`��
	virtual void Render();

	//�A�N�e�B�u���擾����
	bool GetActive();

	//�Q�[���I�u�W�F�N�g��ݒ肷��֐�
	void SetGame(Game* game) { m_game = game; }

	//�ʒu��ݒ肷��֐�
	void SetPosirion(Vector3 position) { m_position = position; }

	//��]��ݒ肷��֐�
	void SetRotation(Quaternion rotation) { m_rotation = rotation; }

	bool m_active;
};