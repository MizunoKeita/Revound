#pragma once
class FpsIns
{
public:
	FpsIns();
	~FpsIns();

	//�X�V
	bool Update();

	//�`��
	void Render();

	//�t���[�����[�g���擾
	int GetFrame();

private:

	int   frame_count;		// �t���[���J�E���g
	//�`�悷��t���[���J�E���g
	int   RenFrameCount;
};
