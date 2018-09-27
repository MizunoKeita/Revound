#pragma once

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	//�X�V
	bool Update();

	//�t���[�������擾�@0-60���J��Ԃ�
	int GetCount();

	//�b�����擾
	int GetTime();

	//�������Ԃ��擾
	int GetTimeLimit();

	//���Ԃ����Z�b�g
	void ResetGameTime();

private:

	//�t���[���J�E���g
	int m_Count ;

	//�b���J�E���g
	int m_Time;

	//��������
	int m_TimeLimit;
};