#include "pch.h"
#include "TitleScene.h"
#include "SpriteResources.h"
#include "DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

TitleScene::TitleScene()
{
	m_titleFlag = true;

	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	//タイトルテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Title.png", nullptr, m_titleTexture.GetAddressOf());
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Update()
{
	return false;
}

void TitleScene::Render()
{
	//タイトル//
	if (m_titleFlag == true)
	{
		SpriteResources::GetInstance()->m_sprites->Draw(m_titleTexture.Get(), Vector2(0, 0));
	}
}

void TitleScene::SetFlag(bool flag)
{
	m_titleFlag = flag;
}

bool TitleScene::GetFlag()
{
	return m_titleFlag;
}
