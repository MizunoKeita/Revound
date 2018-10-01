#include "pch.h"
#include "FpsInspection.h"
#include <timeapi.h>

#pragma comment(lib, "winmm.lib")

FpsIns::FpsIns()
{
	frame_count = 0;		// フレームカウント

	//描画するフレームカウント
	RenFrameCount = 0;
}

FpsIns::~FpsIns()
{
}

bool FpsIns::Update()
{
	static DWORD prev_time = timeGetTime();	// 前回の計測時間

	// 今回の計測時間
	DWORD now_time = timeGetTime();

	frame_count++;	// フレーム数をカウントする
	
	// 経過時間が１秒を超えたらカウントと時間をリセット
	if (now_time - prev_time >= 1000)
	{
		prev_time = now_time;
		RenFrameCount = frame_count;
		frame_count = 0;
	}

	return false;
}

void FpsIns::Render()
{

}

int FpsIns::GetFrame()
{
	return RenFrameCount;
}

