#include "pch.h"
#include "SpriteResources.h"

// 唯一のインスタンスをNULLで初期化
SpriteResources *SpriteResources::s_SpriteResources = NULL;

SpriteResources* SpriteResources::Create()
{
	return new SpriteResources;
}

void SpriteResources::Destroy()
{
	delete s_SpriteResources;
	s_SpriteResources = NULL;
}