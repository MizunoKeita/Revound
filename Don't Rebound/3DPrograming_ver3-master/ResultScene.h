#pragma once

class ResultScene
{
public:
	ResultScene();
	~ResultScene();

	//更新
	bool Update();

	//描画
	void Render();

	void SetFlag(bool flag, int end = 0);

	bool GetFlag();

private:

	//フラグ
	bool m_resultFlag;

	int m_end;

	//テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultTexture;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_gameOverTexture;
	
};