﻿//
// Game.h
//

#pragma once

#include "DeviceResources.h"
#include "StepTimer.h"

#include "DebugCamera.h"
#include "GridFloor.h"
#include "ModelPart.h"

#include "Obj3D.h"
#include "CollisionSphere.h"
#include "tsitPlayer.h"
#include "Barrett.h"
#include "SpriteResources.h"
#include "Monster.h"
#include "gameTimer.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
public:

	//コンストラクタ
    Game();

    // Initialization and management
    void Initialize(HWND window, int width, int height);

    // Basic game loop
    void Tick();

    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;

    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowSizeChanged(int width, int height);

    // Properties
    void GetDefaultSize( int& width, int& height ) const;

	//取得関数
	//デバイスを取得する
	ID3D11Device* GetDevice() { return DX::DeviceResources::GetInstance()->GetD3DDevice(); }

	//コンテキストを取得する
	ID3D11DeviceContext* GetContext() { return DX::DeviceResources::GetInstance()->GetD3DDeviceContext(); }

	//コモンステートを取得する
	DirectX::CommonStates* GetStates() { return m_states.get(); }

private:

	//更新
    void Update(DX::StepTimer const& timer);

	//描画
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

	void DrawSprite3D(DirectX::SimpleMath::Matrix & world, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, float HP);

    // Rendering loop timer.
    DX::StepTimer                           m_timer;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates> m_states;

	// ワールド行列
	DirectX::SimpleMath::Matrix m_world;

	// デバッグカメラ
	std::unique_ptr<DebugCamera> m_debugCamera;

	//影
	std::unique_ptr<DirectX::Model> m_Shadow;

	//スカイブロック
	std::unique_ptr<DirectX::Model> m_sky;
	
	//フィールド
	std::unique_ptr<DirectX::Model> field;

	//入力レイアウト
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	//エフェクト
	std::unique_ptr<DirectX::AlphaTestEffect> m_batchEffect;

	//プリミティブパッチ
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionTexture>> m_batch;

	//テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	//時間テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_Timetexture;

	//タイトルテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_titleTexture;

	//リザルトテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resultTexture;

	//ゲームオーバーテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_gameOverTexture;

	//時間のテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeTexture[10];

	//タイムUIのテクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_timeUiTexture;

	//攻撃表示テクスチャハンドル
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_attackTexture;

	//プレイヤー
	std::unique_ptr<tsitPlayer> m_player;

	//弾
	std::unique_ptr<Barrett> m_barrett;

	//敵
	std::unique_ptr<Monster> m_Bos;

	//敵群
	std::unique_ptr<Monster> m_Enemy[10];

	//衝突判定フラグ
	bool m_hitFlag;

	//タイトルフラグ
	bool m_titleFlag;

	//ステージ選択フラグ
	bool m_StageFlag;

	//リザルトフラグ
	bool m_resultFlag;

	//ゲーム時間クラス
	std::unique_ptr<GameTimer> m_GameTime;
};