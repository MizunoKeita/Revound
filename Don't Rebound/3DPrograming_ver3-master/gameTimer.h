#pragma once

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	//更新
	bool Update();

	//描画
	void Render();

	//フレーム数を取得　0-60を繰り返す
	int GetCount();

	//秒数を取得
	int GetTime();

	//制限時間を取得
	int GetTimeLimit();

	//時間をリセット
	void ResetGameTime();

	int GetMaxTime();

private:

	//フレームカウント
	int m_Count ;

	//秒数カウント
	int m_Time;

	//制限時間
	int m_TimeLimit;

	//タイムUIのテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeUiTexture;

	//時間のテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeTexture[10];

	const int MAX_TIME = 60;
};