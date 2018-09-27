#pragma once

class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	//更新
	bool Update();

	//フレーム数を取得　0-60を繰り返す
	int GetCount();

	//秒数を取得
	int GetTime();

	//制限時間を取得
	int GetTimeLimit();

	//時間をリセット
	void ResetGameTime();

private:

	//フレームカウント
	int m_Count ;

	//秒数カウント
	int m_Time;

	//制限時間
	int m_TimeLimit;
};