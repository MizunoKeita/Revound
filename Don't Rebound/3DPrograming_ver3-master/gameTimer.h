#pragma once

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	//�X�V
	bool Update();

	//�`��
	void Render();

	//�t���[�������擾�@0-60���J��Ԃ�
	int GetCount();

	//�b�����擾
	int GetTime();

	//�������Ԃ��擾
	int GetTimeLimit();

	//���Ԃ����Z�b�g
	void ResetGameTime();

	int GetMaxTime();

private:

	//�t���[���J�E���g
	int m_Count ;

	//�b���J�E���g
	int m_Time;

	//��������
	int m_TimeLimit;

	//�^�C��UI�̃e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeUiTexture;

	//���Ԃ̃e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeTexture[10];

	const int MAX_TIME = 60;
};