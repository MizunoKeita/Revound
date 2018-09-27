﻿//--------------------------------------------------------------------------------------
// File: DebugCamera.cpp
//
// デバッグ用カメラクラス
//
// Date: 2018.4.15
// Author: Hideyasu Imase
//--------------------------------------------------------------------------------------
#include "pch.h"
#include "DebugCamera.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float DebugCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;

//ゲームビュー行列
DirectX::SimpleMath::Matrix DebugCamera::m_gameView;

// 射影行列
DirectX::SimpleMath::Matrix DebugCamera::m_projection;

//--------------------------------------------------------------------------------------
// コンストラクタ
//--------------------------------------------------------------------------------------
DebugCamera::DebugCamera(int windowWidth, int windowHeight)
	: m_yAngle(0.0f), m_yTmp(0.0f), m_xAngle(0.0f), m_xTmp(0.0f), m_x(0), m_y(0), m_scrollWheelValue(0)
{
	SetWindowSize(windowWidth, windowHeight);
}

//--------------------------------------------------------------------------------------
// 更新
//--------------------------------------------------------------------------------------
void DebugCamera::Update(Vector3 pos)
{
	auto state = Mouse::Get().GetState();

	// 相対モードなら何もしない
	if (state.positionMode == Mouse::MODE_RELATIVE) return;

	m_tracker.Update(state);

	// マウスのフォイール値を取得
	m_scrollWheelValue = state.scrollWheelValue;
	if (m_scrollWheelValue > 0)
	{
		m_scrollWheelValue = 0;
		Mouse::Get().ResetScrollWheelValue();
	}

	// ビュー行列を算出する
	Matrix rotY = Matrix::CreateRotationY(m_yTmp);
	Matrix rotX = Matrix::CreateRotationX(m_xTmp);

	Matrix rt = rotY * rotX;

	Vector3 eye(0.0f, 3.0f, -3.0f);
	Vector3 target(0.0f, 5.0f, 0.0f);
	Vector3 up(0.0f, 1.0f, 0.0f);

	eye = Vector3::Transform(eye, rt.Invert());
	eye *= (DEFAULT_CAMERA_DISTANCE - m_scrollWheelValue / 100);
	up = Vector3::Transform(up, rt.Invert());

	m_eye = eye;
	m_target = target;

	m_view = Matrix::CreateLookAt(eye +pos, target + pos, up);
	
	m_gameView = m_view;

	// ウインドウサイズからアスペクト比を算出する
	RECT size = DX::DeviceResources::GetInstance()->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(fovAngleY, aspectRatio, 0.01f, 1000.0f);

	// デバッグカメラにウインドウのサイズ変更を伝える
	SetWindowSize(size.right, size.bottom);
}

//--------------------------------------------------------------------------------------
// 行列の生成
//--------------------------------------------------------------------------------------
void DebugCamera::Motion(int x, int y)
{
	// マウスポインタの位置のドラッグ開始位置からの変位 (相対値)
	float dx = (x - m_x) * m_sx;
	float dy = (y - m_y) * m_sy;

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float yAngle = dx * XM_PI;
		// Ｘ軸の回転
		float xAngle = dy * XM_PI;

		m_xTmp = m_xAngle + xAngle;
		m_yTmp = m_yAngle + yAngle;
	}
}

DirectX::SimpleMath::Matrix DebugCamera::GetCameraMatrix()
{
	return m_view;
}

DirectX::SimpleMath::Vector3 DebugCamera::GetEyePosition()
{
	return m_eye;
}

DirectX::SimpleMath::Vector3 DebugCamera::GetTargetPosition()
{
	return m_target;
}

void DebugCamera::SetWindowSize(int windowWidth, int windowHeight)
{
	// 画面サイズに対する相対的なスケールに調整
	m_sx = 1.0f / float(windowWidth);
	m_sy = 1.0f / float(windowHeight);
}

void DebugCamera::SetyTmp(float y)
{
	m_yTmp = -y;
}

const DirectX::SimpleMath::Matrix DebugCamera::GetView()
{
	// TODO: return ステートメントをここに挿入します
	return m_gameView;
}

const DirectX::SimpleMath::Matrix DebugCamera::GetProjection()
{
	// TODO: return ステートメントをここに挿入します
	return m_projection; 
}
