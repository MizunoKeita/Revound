#pragma once

class ResultScene
{
public:
	ResultScene();
	~ResultScene();

	//�X�V
	bool Update();

	//�`��
	void Render();

	void SetFlag(bool flag, int end = 0);

	bool GetFlag();

private:

	//�t���O
	bool m_resultFlag;

	int m_end;

	//�e�N�X�`���n���h��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultTexture;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_gameOverTexture;
	
};