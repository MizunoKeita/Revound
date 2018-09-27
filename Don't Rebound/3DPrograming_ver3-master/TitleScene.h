#pragma once

class TitleScene
{
public:
	TitleScene();
	~TitleScene();

	//更新
	bool Update();

	//描画
	void Render();

	void SetFlag(bool flag);

	bool GetFlag();

private:

	//タイトルフラグ
	bool m_titleFlag;

	//タイトルテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleTexture;
};
