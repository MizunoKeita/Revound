#pragma once
class FpsIns
{
public:
	FpsIns();
	~FpsIns();

	//更新
	bool Update();

	//描画
	void Render();

	//フレームレートを取得
	int GetFrame();

private:

	int   frame_count;		// フレームカウント
	//描画するフレームカウント
	int   RenFrameCount;
};
