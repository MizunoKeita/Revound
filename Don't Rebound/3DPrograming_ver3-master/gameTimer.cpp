#include "pch.h"
#include "gameTimer.h"
#include "SpriteResources.h"
#include "DeviceResources.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

GameTimer::GameTimer()
{
	m_Count = 0;

	m_Time = 0;

	m_TimeLimit = MAX_TIME;

	//デバイスの取得
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	//FPSを作成
	m_FpsInspection= std::make_unique<FpsIns>();

	//時間のテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Zero.png",  nullptr, m_timeTexture[0].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\One.png",   nullptr, m_timeTexture[1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Two.png",   nullptr, m_timeTexture[2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Three.png", nullptr, m_timeTexture[3].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Four.png",  nullptr, m_timeTexture[4].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Five.png",  nullptr, m_timeTexture[5].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Six.png  ", nullptr, m_timeTexture[6].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Seven.png", nullptr, m_timeTexture[7].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Eight.png", nullptr, m_timeTexture[8].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Nine.png",  nullptr, m_timeTexture[9].GetAddressOf());

	//タイムUIテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\time.png", nullptr, m_timeUiTexture.GetAddressOf());

	//FPSUIテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\fps.png", nullptr, m_FpsUiTexture.GetAddressOf());

}

GameTimer::~GameTimer()
{
}

bool GameTimer::Update()
{
	m_Count++;

	if (m_Count == 60)
	{
		m_Time++;
		m_TimeLimit--;
		m_Count = 0;
	}
	
	if (m_TimeLimit <= 0)
	{
		m_TimeLimit = 0;
	}

	m_FpsInspection->Update();

	return true;
}

void GameTimer::Render()
{
	//時間//
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeUiTexture.Get(), Vector2(FONT_SIZE * 0, 0));

	//fps
	SpriteResources::GetInstance()->m_sprites->Draw(m_FpsUiTexture.Get(), Vector2(FONT_SIZE * 6, 0));

	//残り時間
	int hundredTime = m_TimeLimit / 100;
	int tenTime = (m_TimeLimit - hundredTime * 100) / 10;
	int oneTime = (m_TimeLimit - (hundredTime * 100 + tenTime * 10));

	//描画
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[hundredTime].Get(), Vector2(FONT_SIZE*3, 0));
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[tenTime].Get()    , Vector2(FONT_SIZE * 4, 0));
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[oneTime].Get()    , Vector2(FONT_SIZE * 5, 0));

	//残り時間
	hundredTime = m_FpsInspection->GetFrame() / 100;
	tenTime = (m_FpsInspection->GetFrame() - hundredTime * 100) / 10;
	oneTime = (m_FpsInspection->GetFrame() - (hundredTime * 100 + tenTime * 10));

	//描画
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[hundredTime].Get(), Vector2(FONT_SIZE * 9, 0));
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[tenTime].Get(), Vector2(FONT_SIZE * 10, 0));
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[oneTime].Get(), Vector2(FONT_SIZE * 11, 0));

}

int GameTimer::GetCount()
{
	return m_Count;
}

int GameTimer::GetTime()
{
	return m_Time;
}

int GameTimer::GetTimeLimit()
{
	return m_TimeLimit;
}

void GameTimer::ResetGameTime()
{
	m_Count = 0;

	m_Time = 0;

	m_TimeLimit = MAX_TIME;
}

int GameTimer::GetMaxTime()
{
	return MAX_TIME;
}
