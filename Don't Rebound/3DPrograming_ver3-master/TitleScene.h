#pragma once

class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	//�X�V
	bool Update();

	//�`��
	void Render();

	void SetFlag(bool flag);

	bool GetFlag();

private:

	//�^�C�g���t���O
	bool m_titleFlag;

	//�^�C�g���e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleTexture;
};
