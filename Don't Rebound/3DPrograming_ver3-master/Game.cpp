//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

extern void ExitGame();

using namespace DirectX;
using namespace DirectX::SimpleMath;

using Microsoft::WRL::ComPtr;

Game::Game()
{
	//DeviceResourcesの作成
	DX::DeviceResources::Create();

	//Keyboardの作成
	Keyboard::Create();

	//Mouseの作成
	Mouse::Create();

	//SpriteResourcesの作成
	SpriteResources::Create();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// マウスの稼働できるウィンドウの設定
	Mouse::Get().SetWindow(window);

	// デバッグカメラの作成
	m_debugCamera = std::make_unique<DebugCamera>(width, height);

	DX::DeviceResources* deviceResources = DX::DeviceResources::GetInstance();

	deviceResources->SetWindow(window, width, height);
	deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();
	deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:

	//タイトルフラグをオン
	m_TitleScene->SetFlag(true);

	//リザルトフラグをオフ
	m_ResultScene->SetFlag(false);

}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });
    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    int elapsedTime = float(timer.GetElapsedSeconds());

	static float moveX = 0.0f;
	static float moveZ = 0.0f;

	if (m_TitleScene->GetFlag() == false)
	{
		m_GameTime->Update();

		if (m_player->GetHp() <= 0 || m_GameTime->GetTimeLimit() <= 0)
		{
			m_ResultScene->SetFlag(true,2);
		}
	}
	
    // TODO: Add your game logic here.
    elapsedTime;
	
	// デバッグカメラの更新
	m_debugCamera->Update(m_player->getPos());
	
	if (GetKeyState('A') & 0x8000) {
		//左に旋回
		moveX +=0.1f;
		m_player->Move(tsitPlayer::LEFT_TURN);
	}
	else if (GetKeyState('D') & 0x8000) {
		//右に旋回
		moveX -= 0.1f;
		m_player->Move(tsitPlayer::RIGHT_TURN);
	}
	else if (GetKeyState('W') & 0x8000) {
		//前進
		moveZ += 0.1f;
		m_player->Move(tsitPlayer::FORWARD);
	}
	else if (GetKeyState('S') & 0x8000) {
		//後退
		moveZ -= 0.1f;
		m_player->Move(tsitPlayer::BACK);
	}
	else if (GetKeyState(' ') & 0x8000) {
		m_barrett->setAttack(true);
	}
	else {
		//止まる
		m_player->Move(tsitPlayer::STOP);
	}

	//デバック用PlayerのHPを減らす
	if (GetKeyState('R') & 0x8000) 
	{
		m_player->SubHp(9.0f);
	}

	//タイトルからプレイシーンに移動
	if (GetKeyState(' ') & 0x8000)
	{
		m_TitleScene->SetFlag(false);
	}

	//プレイヤーの更新
	m_player->Update(elapsedTime);

	//弾の更新
	m_barrett->Update(m_player->GetRotation(), m_player->getPos(), m_player->Getdirection());

	//敵の更新
	m_Bos->Update(elapsedTime);

	//雑魚敵の更新
	//for (int i = 0; i < 10; i++)
	//{
	//	m_Enemy[i]->Update(elapsedTime);
	//}

	for each (auto enemy in m_Enemys)
	{
		enemy->Update(elapsedTime);
	}

	m_hitFlag = false;

	//Playerとボスの当たり判定
	if (Collision::HitCheck_Sphere2Sphere(m_player->GetCollision(), m_Bos->GetCollision()) == true)
	{
		m_hitFlag = true;
	}

	//弾とボスの当たり判定
	if (Collision::HitCheck_Sphere2Sphere(m_barrett->GetCollision(), m_Bos->GetCollision()) == true)
	{
		//ボスの表示を消す
		m_Bos->state(0);
	}

	//Playerと雑魚敵の当たり判定
	//for (int i = 0; i < 10; i++)
	//{
	//	if (Collision::HitCheck_Sphere2Sphere(m_player->GetCollision(), m_Enemy[i]->GetCollision()) == true)
	//	{
	//		//PlayerのHPを減らす
	//		m_player->SubHp(0.2f);
	//	} 
	//	if (Collision::HitCheck_Sphere2Sphere(m_barrett->GetCollision(), m_Enemy[i]->GetCollision()) == true)
	//	{
	//		//雑魚の表示を消す
	//		m_Enemy[i]->state(0);
	//	}
	//}

	for each (auto enemy in m_Enemys)
	{
		if (Collision::HitCheck_Sphere2Sphere(m_player->GetCollision(), enemy->GetCollision()) == true)
		{
			//PlayerのHPを減らす
			m_player->SubHp(0.2f);
		}
		if (Collision::HitCheck_Sphere2Sphere(m_barrett->GetCollision(), enemy->GetCollision()) == true)
		{
			//雑魚の表示を消す
			enemy->state(0);
		}
	}
	
	//リザルトシーンでBが押されたらタイトルに移行
	if (GetKeyState('B') & 0x8000 && m_ResultScene->GetFlag() == true)
	{
		//初期化する
		m_ResultScene->SetFlag(false);
		m_TitleScene->SetFlag(true);
		m_player->SetStatus();
		m_Bos->state(1);
		m_GameTime->ResetGameTime();

		for each (auto enemy in m_Enemys)
		{
			enemy->state(1);
		}	
	}

	if (m_Bos->GetState() == 0)
	{
		//リザルトシーンに移行
		m_ResultScene->SetFlag(true, 1);
	}

	m_debugCamera->SetyTmp(m_player->Getdirection());
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
	// Don't try to render anything before the first Update.
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	DX::DeviceResources::GetInstance()->PIXBeginEvent(L"Render");
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
	
	//ライト
	auto SetLight = [&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			lights->SetAmbientLightColor(Vector3(0.3f, 0.3f, 0.3f));    // アンビエント色を設定する
			lights->SetLightEnabled(0, true);							// １番のライトON
			lights->SetLightEnabled(1, false);							// ２番のライトOFF
			lights->SetLightEnabled(2, false);							// ３番のライトOFF
			lights->SetLightDiffuseColor(0, Colors::White);				// ライトの色
			Vector3 light_dir(1, -1, 0);								// ライトの方向ベクトル
			light_dir.Normalize();										// ライトの方向ベクトルを正規化する
			lights->SetLightDirection(0, light_dir);					// １番のライトの方向を設定する
			lights->SetPerPixelLighting(true);							//ピクセルシェーダーで光の影響を計算する
		}
	};
	
	auto SetCustomShadowState = [&]() 
	{
		//半透明をオン
		context->OMSetBlendState(m_states->AlphaBlend(), nullptr, 0xFFFFFFFF);

		//震度バッファーは使用せず必ず描画する設定
		context->OMSetDepthStencilState(m_states->DepthNone(), 0);
	};

	m_sky->UpdateEffects([&](IEffect* effect)
	{
		IEffectLights* lights = dynamic_cast<IEffectLights*>(effect);
		if (lights)
		{
			// ライトの影響をなくす
			lights->SetAmbientLightColor(Vector3(0.0f, 0.0f, 0.0f));
			lights->SetLightEnabled(0, false);
			lights->SetLightEnabled(1, false);
			lights->SetLightEnabled(2, false);
		}
		BasicEffect* basicEffect = dynamic_cast<BasicEffect*>(effect);
		if (basicEffect)
		{
			// エミッション色を白に設定する
			basicEffect->SetEmissiveColor(Vector3(1.0f, 1.0f, 1.0f));
		}
	});

	Matrix world = Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));

	// ビュー行列の作成
	DirectX::SimpleMath::Matrix view = m_debugCamera->GetView();

	// プロジェクション行列の作成
	DirectX::SimpleMath::Matrix projection = m_debugCamera->GetProjection();

	//スカイボックスの描画
	m_sky->Draw(context, *m_states.get(), world, view, projection);

	//フィールドの描画
	field->Draw(context, *m_states.get(), world, view, projection);

	//プレイヤーの描画
	m_player->Render();

	//弾の描画
	m_barrett->Render();

	//ボスの描画
	if (m_Bos->GetState() == 1)
	{
		m_Bos->Render();
		//m_tsit->DrawCollision();
	}

	//雑魚敵の描画
	for each (auto enemy in m_Enemys)
	{
		if (enemy->GetState() == 1)
		{
			enemy->Render();
		}
	}
	
	//スプライトの描画はここから
	//m_sprites->Begin();
	//Begin 関数にアルファブレンドのステートを設定します
	SpriteResources::GetInstance()->m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	//UIの描画
	if (m_hitFlag == true)
	{
		if (m_player->GetMoveCount() == 1)
		{
			SpriteResources::GetInstance()->m_font->DrawString(SpriteResources::GetInstance()->m_sprites.get(), L"Attack!!!", Vector2(0.0f, 0.0f));
		}
		else
		{
			SpriteResources::GetInstance()->m_font->DrawString(SpriteResources::GetInstance()->m_sprites.get(), L"Hit!", Vector2(0.0f, 0.0f));
		}
	}

	world = Matrix::CreateBillboard(m_player->getPos() + Vector3(0.0f, 6.0f,0.0f), m_debugCamera->GetEyePosition() + m_player->getPos(), Vector3::Up);

	//スプライトの描画
	DrawSprite3D(world,m_texture,m_player->GetHp());

	//world = Matrix::CreateBillboard(Vector3(0.0f, 0.0f, 0.0f), m_debugCamera->GetEyePosition(), Vector3::Up);
	//スプライトの描画
	//DrawSprite3D(world, m_timeUiTexture, 100.0f);

	//タイトル//
	if (m_TitleScene->GetFlag() != true)
	{
		m_GameTime->Render();
	}

	//Playerの攻撃表示
	if (m_player->GetMoveCount() == 1 && m_ResultScene->GetFlag() == false)
	{
		SpriteResources::GetInstance()->m_sprites->Draw(m_attackTexture.Get(), Vector2(0, 0));
	}

	//タイトル
	m_TitleScene->Render();

	//リザルト
	m_ResultScene->Render();

	//スプライトの描画はここまで
	SpriteResources::GetInstance()->m_sprites->End();

	// ここまで
	DX::DeviceResources::GetInstance()->PIXEndEvent();

    // Show the new frame.
	DX::DeviceResources::GetInstance()->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	DX::DeviceResources::GetInstance()->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();
    auto renderTarget = DX::DeviceResources::GetInstance()->GetRenderTargetView();
    auto depthStencil = DX::DeviceResources::GetInstance()->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, Colors::SkyBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = DX::DeviceResources::GetInstance()->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

	DX::DeviceResources::GetInstance()->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!DX::DeviceResources::GetInstance()->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 800;
    height = 600;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();
	ID3D11DeviceContext* context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// コモンステートの作成
	m_states = std::make_unique<CommonStates>(device);

	// スプライトバッチの作成
	SpriteResources::GetInstance()->m_sprites = std::make_unique<SpriteBatch>(context);

	// スプライトフォントの作成
	SpriteResources::GetInstance()->m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");

	// エフェクトファクトリー
	EffectFactory fx(device);

	// モデルのテクスチャの入っているフォルダを指定する
	fx.SetDirectory(L"Resources\\Models");

	// モデルをロードしてモデルハンドルを取得する
	//影
	m_Shadow = Model::CreateFromCMO(device, L"Resources\\Models\\Shadow.cmo", fx);

	//スカイドーム
	m_sky = Model::CreateFromCMO(device, L"Resources\\Models\\sky2.cmo", fx);

	//ここから
	field =   Model::CreateFromCMO(device, L"Resources\\Models\\fool.cmo", fx);

	// テクスチャのロード
	CreateWICTextureFromFile(device, L"Resources\\Textures\\UI0611.png", nullptr, m_texture.GetAddressOf());
	
	// エフェクトの作成
	m_batchEffect = std::make_unique<AlphaTestEffect>(device);
	m_batchEffect->SetAlphaFunction(D3D11_COMPARISON_EQUAL);
	m_batchEffect->SetReferenceAlpha(255);

	// 入力レイアウト生成
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	device->CreateInputLayout(VertexPositionTexture::InputElements, VertexPositionTexture::InputElementCount,
		shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());

	// プリミティブバッチの作成
	m_batch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	//プレイヤーHP
	CreateWICTextureFromFile(device, L"Resources\\Textures\\HPUI.png", nullptr, m_texture.GetAddressOf());
	
	//スフィアの設定
	Collision::Sphere sphere;

	//当たり判定の位置の変更
	sphere.center = Vector3(0.0f, 1.0f, 1.5f);

	//当たり判定の大きさを決める
	sphere.radius = 2.0f;

	//プレイヤー
	m_player = std::make_unique<tsitPlayer>();
	m_player->SetGame(this);
	m_player->SetCollision(sphere);

	//弾
	m_barrett = std::make_unique<Barrett>();
	m_barrett->SetGame(this);
	m_barrett->SetCollision(sphere);

	//ボス敵
	m_Bos = std::make_unique<Monster>();
	m_Bos->SetGame(this);

	//移動
	m_Bos->SetPosirion(Vector3(6.0f, 0.0f, 0.0f));
	m_Bos->SetCollision(sphere);

	//雑魚敵
	for (int i = 0; i<POP_ENEMY_NUM; i++)
	{
		Monster* monster = new Monster();
		m_Enemys.push_back(monster);
		monster->SetGame(this);

		//移動
		monster->SetPosirion(Vector3(rand() % 50 - 25.0f, 0.0f, rand() % 50 - 25.0f));
		monster->SetCollision(sphere);
	}

	//ゲームタイムを作成
	m_GameTime = std::make_unique<GameTimer>();

	//タイトルシーンを作成
	m_TitleScene = std::make_unique<TitleScene>();

	//リザルトシーンを作成
	m_ResultScene = std::make_unique<ResultScene>();

	// TODO: Initialize device dependent objects here (independent of window size).
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.
}

void Game::DrawSprite3D(Matrix & world, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture, float HP)
{
	float hp = HP / 100.0f;

	// 頂点情報（ここは自分で設定してください。）
	VertexPositionTexture vertex[4] =
	{
		VertexPositionTexture(Vector3( 4.0f* hp ,  0.6f, 0.0f), Vector2(0.0f,     0.0f)),
		VertexPositionTexture(Vector3(-4.0f* hp ,  0.6f, 0.0f), Vector2(1.0f* hp, 0.0f)),
		VertexPositionTexture(Vector3(-4.0f* hp , -0.6f, 0.0f), Vector2(1.0f* hp, 1.0f)),
		VertexPositionTexture(Vector3( 4.0f* hp , -0.6f, 0.0f), Vector2(0.0f,     1.0f)),
	};

	//コンテキスト
	auto context = DX::DeviceResources::GetInstance()->GetD3DDeviceContext();

	// 不透明に設定
	context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	// NonPremultiplied()

	// 深度バッファに書き込み参照する
	context->OMSetDepthStencilState(m_states->DepthDefault(), 0);

	// カリングは左周り
	context->RSSetState(m_states->CullCounterClockwise());

	//// 不透明のみ描画する設定
	m_batchEffect->SetWorld(world);
	m_batchEffect->SetView(m_debugCamera->GetView());
	m_batchEffect->SetProjection(m_debugCamera->GetProjection());
	m_batchEffect->SetTexture(texture.Get());
	m_batchEffect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	// 半透明で描画
	context->OMSetBlendState(m_states->NonPremultiplied(), nullptr, 0xFFFFFFFF);

	// 深度バッファに書き込まないが参照だけする
	context->OMSetDepthStencilState(m_states->DepthRead(), 0);

	// 半透明部分を描画
	m_batch->Begin();
	m_batch->DrawQuad(vertex[0], vertex[1], vertex[2], vertex[3]);
	m_batch->End();

}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.

	for each (auto enemy in m_Enemys)
	{
		delete enemy;
	}

	// コモンステートの解放
	m_states.reset();

	// スプライトバッチの解放
	SpriteResources::GetInstance()->m_sprites.reset();

	// スプライトフォントの解放
	SpriteResources::GetInstance()->m_font.reset();

	//DeviceResourcesの破棄
	DX::DeviceResources::Destroy();

	//Keyboard::Destroy();

	//Mouse::Destroy();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
