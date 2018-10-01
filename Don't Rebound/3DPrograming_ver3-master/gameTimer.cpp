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

	//�f�o�C�X�̎擾
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	//���Ԃ̃e�N�X�`��
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

	//�^�C��UI�e�N�X�`��
	CreateWICTextureFromFile(device, L"Resources\\Textures\\timeB.png", nullptr, m_timeUiTexture.GetAddressOf());

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

	return true;
}

void GameTimer::Render()
{
	//�X�e�[�W�I�����//
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeUiTexture.Get(), Vector2(0, 0));

	//�c�莞��
	int hundredTime = m_TimeLimit / 100;
	int tenTime = (m_TimeLimit - hundredTime * 100) / 10;
	int oneTime = (m_TimeLimit - (hundredTime * 100 + tenTime * 10));

	//�`��
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[hundredTime].Get(), Vector2(300, 0));
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[tenTime].Get(), Vector2(400, 0));
	SpriteResources::GetInstance()->m_sprites->Draw(m_timeTexture[oneTime].Get(), Vector2(500, 0));

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
