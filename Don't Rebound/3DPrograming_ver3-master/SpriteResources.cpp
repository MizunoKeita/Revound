#include "pch.h"
#include "SpriteResources.h"

// �B��̃C���X�^���X��NULL�ŏ�����
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