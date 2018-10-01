#include "pch.h"
#include "FpsInspection.h"
#include <timeapi.h>

#pragma comment(lib, "winmm.lib")

FpsIns::FpsIns()
{
	frame_count = 0;		// �t���[���J�E���g

	//�`�悷��t���[���J�E���g
	RenFrameCount = 0;
}

FpsIns::~FpsIns()
{
}

bool FpsIns::Update()
{
	static DWORD prev_time = timeGetTime();	// �O��̌v������

	// ����̌v������
	DWORD now_time = timeGetTime();

	frame_count++;	// �t���[�������J�E���g����
	
	// �o�ߎ��Ԃ��P�b�𒴂�����J�E���g�Ǝ��Ԃ����Z�b�g
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

