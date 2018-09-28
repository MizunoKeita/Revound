#include "pch.h"
#include "ResultScene.h"
#include "SpriteResources.h"
#include "DeviceResources.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

ResultScene::ResultScene()
{
	m_resultFlag = false;

	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	//リザルトテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Result.png", nullptr, m_resultTexture.GetAddressOf());

	//ゲームオーバーテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Over.png", nullptr, m_gameOverTexture.GetAddressOf());

}

ResultScene::~ResultScene()
{
}

bool ResultScene::Update()
{
	return false;
}

void ResultScene::Render()
{
	//タイトル//
	if (m_resultFlag == true)
	{
		if (m_end == 1)
		{
			SpriteResources::GetInstance()->m_sprites->Draw(m_resultTexture.Get(), Vector2(0, 0));
		}
		else if (m_end == 2)
		{
			SpriteResources::GetInstance()->m_sprites->Draw(m_gameOverTexture.Get(), Vector2(0, 0));
		}
	}
}

void ResultScene::SetFlag(bool flag, int end )
{
	m_resultFlag = flag;

	m_end = end;
}

bool ResultScene::GetFlag()
{
	return m_resultFlag;
}
