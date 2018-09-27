#include "pch.h"
#include "gameTimer.h"

GameTimer::GameTimer()
{
	m_Count = 0;

	m_Time = 0;

	m_TimeLimit = 60;
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

	m_TimeLimit = 60;
}
