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

    /*m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);*/
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	// キーボードの作成
	m_keyboard = std::make_unique<Keyboard>();

	// マウスの作成
	m_mouse = std::make_unique<Mouse>();
	m_mouse->SetWindow(window);

	// デバッグカメラの作成
	m_debugCamera = std::make_unique<DebugCamera>(width, height);

	DX::DeviceResources::GetInstance()->SetWindow(window, width, height);
	DX::DeviceResources::GetInstance()->CreateDeviceResources();
    CreateDeviceDependentResources();
    DX::DeviceResources::GetInstance()->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:

	//タイトルフラグをオン
	m_titleFlag = true;
	//リザルトフラグをオフ
	m_resultFlag = false;
	//タイムを初期化
	m_gameTime = 60;

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
	static int Count = 0;
	Count++;
	if (m_titleFlag == false)
	{
		if (Count == 60)
		{
			m_gameTime--;
			Count = 0;
		}
		if (m_gameTime <= 0)
		{
			m_resultFlag = true;
			m_gameTime = 0;
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
		m_titleFlag = false;
	}

	//プレイヤーの更新
	m_player->Update(elapsedTime);

	//弾の更新
	m_barrett->Update(m_player->GetRotation(), m_player->getPos(), m_player->Getdirection());

	//敵の更新
	m_tsit->Update(elapsedTime);

	//雑魚敵の更新
	for (int i = 0; i < 10; i++)
	{
		m_tsits[i]->Update(elapsedTime);
	}

	m_hitFlag = false;

	//Playerとボスの当たり判定
	if (Collision::HitCheck_Sphere2Sphere(m_player->GetCollision(), m_tsit->GetCollision()) == true)
	{
		m_hitFlag = true;
	}

	//弾とボスの当たり判定
	if (Collision::HitCheck_Sphere2Sphere(m_barrett->GetCollision(), m_tsit->GetCollision()) == true)
	{
		//ボスの表示を消す
		m_tsit->state(0);
	}

	//Playerと雑魚敵の当たり判定
	for (int i = 0; i < 10; i++)
	{
		if (Collision::HitCheck_Sphere2Sphere(m_player->GetCollision(), m_tsits[i]->GetCollision()) == true)
		{
			//PlayerのHPを減らす
			m_player->SubHp(0.2f);
		} 
		if (Collision::HitCheck_Sphere2Sphere(m_barrett->GetCollision(), m_tsits[i]->GetCollision()) == true)
		{
			//雑魚の表示を消す
			m_tsits[i]->state(0);
		}
	}
	
	//リザルトシーンでBが押されたらタイトルに移行
	if (GetKeyState('B') & 0x8000 && m_resultFlag == true)
	{
		//初期化する
		m_resultFlag = false;
		m_titleFlag = true;
		m_player->SetStatus();
		m_tsit->state(1);
		m_gameTime = 60;
		for (int i = 0; i < 10; i++)
		{
			m_tsits[i]->state(1);
		}	
	}

	if (m_player->GetHp() <= 0 || m_tsit->GetState() == 0)
	{
		//リザルトシーンに移行
		m_resultFlag = true;
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

	// ビュー行列の作成
	m_view = m_debugCamera->GetCameraMatrix();
	Matrix world;
	
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

	world = Matrix::CreateTranslation(Vector3(0.0f, 0.0f, 0.0f));

	//スカイボックスの描画
	m_sky->Draw(context, *m_states.get(), world, m_view, m_projection);

	//フィールドの描画
	field->Draw(context, *m_states.get(), world, m_view, m_projection);

	//プレイヤーの描画
	m_player->Render();

	//弾の描画
	m_barrett->Render();

	//ボスの描画
	if (m_tsit->GetState() == 1)
	{
		m_tsit->Render();
		//m_tsit->DrawCollision();
	}

	//雑魚敵の描画
	for (int i = 0; i < 10; i++)
	{
		if (m_tsits[i]->GetState() == 1)
		{
			m_tsits[i]->Render();
		}
	}
	
	//スプライトの描画はここから
	//m_sprites->Begin();
	//Begin 関数にアルファブレンドのステートを設定します
	m_sprites->Begin(SpriteSortMode_Deferred, m_states->NonPremultiplied());

	//UIの描画
	if (m_hitFlag == true)
	{
		if (m_player->GetMoveCount() == 1)
		{
			m_font->DrawString(m_sprites.get(), L"Attack!!!", Vector2(0.0f, 0.0f));
		}
		else
		{
			m_font->DrawString(m_sprites.get(), L"Hit!", Vector2(0.0f, 0.0f));
		}
	}

	world = Matrix::CreateBillboard(m_player->getPos() + Vector3(0.0f, 6.0f,0.0f), m_debugCamera->GetEyePosition() + m_player->getPos(), Vector3::Up);

	//スプライトの描画
	DrawSprite3D(world,m_texture,m_player->GetHp());

	//world = Matrix::CreateBillboard(Vector3(0.0f, 0.0f, 0.0f), m_debugCamera->GetEyePosition(), Vector3::Up);
	//スプライトの描画
	//DrawSprite3D(world, m_timeUiTexture, 100.0f);

	//タイトル//
	if (m_titleFlag == true)
	{
		//RECT a{ 100,100,300,300 };
		m_sprites->Draw(m_titleTexture.Get(), Vector2(0, 0));
	}
	else
	{
		//ステージ選択画面//
		m_sprites->Draw(m_timeUiTexture.Get(), Vector2(0, 0));
		//残り時間
		int hundredTime = m_gameTime / 100;
		int tenTime = (m_gameTime - hundredTime * 100)  / 10;
		int oneTime = (m_gameTime - (hundredTime * 100 + tenTime * 10));

		m_sprites->Draw(m_timeTexture[hundredTime].Get(), Vector2(300, 0));
		m_sprites->Draw(m_timeTexture[tenTime].Get(), Vector2(400, 0));
		m_sprites->Draw(m_timeTexture[oneTime].Get(), Vector2(500, 0));
	}

	//リザルト//
	if (m_resultFlag == true)
	{
		m_sprites->Draw(m_resultTexture.Get(), Vector2(0, 0));
	}
	if (m_gameTime == 0)
	{
		m_sprites->Draw(m_gameOverTexture.Get(), Vector2(0, 0));
	}

	//Playerの攻撃表示
	if (m_player->GetMoveCount() == 1 && m_resultFlag == false)
	{
		m_sprites->Draw(m_attackTexture.Get(), Vector2(0, 0));
	}

	//スプライトの描画はここまで
	m_sprites->End();

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
	m_sprites = std::make_unique<SpriteBatch>(context);

	// スプライトフォントの作成
	m_font = std::make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");

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
	
	//タイトルテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Title.png", nullptr, m_titleTexture.GetAddressOf());
	
	//時間のテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Zero.png" , nullptr, m_timeTexture[0].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\One.png"  , nullptr, m_timeTexture[1].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Two.png"  , nullptr, m_timeTexture[2].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Three.png", nullptr, m_timeTexture[3].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Four.png" , nullptr, m_timeTexture[4].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Five.png" , nullptr, m_timeTexture[5].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Six.png  ", nullptr, m_timeTexture[6].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Seven.png", nullptr, m_timeTexture[7].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Eight.png", nullptr, m_timeTexture[8].GetAddressOf());
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Nine.png" , nullptr, m_timeTexture[9].GetAddressOf());

	//タイムUIテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\timeB.png", nullptr, m_timeUiTexture.GetAddressOf());

	//リザルトテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Result.png", nullptr, m_resultTexture.GetAddressOf());
	
	//ゲームオーバーテクスチャ
	CreateWICTextureFromFile(device, L"Resources\\Textures\\Over.png", nullptr, m_gameOverTexture.GetAddressOf());

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
	
	//時間
	CreateWICTextureFromFile(device, L"Resources\\Textures\\timeB.png", nullptr, m_Timetexture.GetAddressOf());
	
	//プレイヤーモデル
	m_playerModel = Model::CreateFromCMO(device, L"Resources\\Models\\redmen.cmo", fx);

	//Monsterモデル
	m_tsitModel = Model::CreateFromCMO(device, L"Resources\\Models\\Monster1.cmo", fx);
	
	//弾モデル
	m_barrettModel = Model::CreateFromCMO(device, L"Resources\\Models\\shoting.cmo", fx);

	//スフィアの設定
	Collision::Sphere sphere;

	//当たり判定の位置の変更
	sphere.center = Vector3(0.0f, 1.0f, 1.5f);

	//当たり判定の大きさを決める
	sphere.radius = 2.0f;

	//プレイヤー
	m_player = std::make_unique<tsitPlayer>();
	m_player->SetGame(this);
	m_player->SetModel(m_playerModel.get());
	m_player->SetCollision(sphere);

	//弾
	m_barrett = std::make_unique<Barrett>();
	m_barrett->SetGame(this);
	m_barrett->SetModel(m_barrettModel.get());
	m_barrett->SetCollision(sphere);

	//ボス敵
	m_tsit = std::make_unique<CollisionSphere>();
	m_tsit->SetGame(this);
	m_tsit->SetModel(m_tsitModel.get());

	//移動
	m_tsit->SetPosirion(Vector3(6.0f, 0.0f, 0.0f));
	m_tsit->SetCollision(sphere);

	//雑魚敵
	for (int i = 0; i < 10; i++)
	{
		m_tsits[i] = std::make_unique<CollisionSphere>();
		m_tsits[i]->SetGame(this);
		m_tsits[i]->SetModel(m_tsitModel.get());
		//移動
		m_tsits[i]->SetPosirion(Vector3(rand() % 50 - 25.0f, 0.0f, rand() % 50 - 25.0f));
		m_tsits[i]->SetCollision(sphere);
	}

	// TODO: Initialize device dependent objects here (independent of window size).
	device;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

	// ウインドウサイズからアスペクト比を算出する
	RECT size = DX::DeviceResources::GetInstance()->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// 画角を設定
	float fovAngleY = XMConvertToRadians(45.0f);

	// 射影行列を作成する
	m_projection = Matrix::CreatePerspectiveFieldOfView(fovAngleY, aspectRatio, 0.01f, 1000.0f);

	// デバッグカメラにウインドウのサイズ変更を伝える
	m_debugCamera->SetWindowSize(size.right, size.bottom);
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
	m_batchEffect->SetView(m_view);
	m_batchEffect->SetProjection(m_projection);
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

	// コモンステートの解放
	m_states.reset();

	// スプライトバッチの解放
	m_sprites.reset();

	// スプライトフォントの解放
	m_font.reset();

	//DeviceResourcesの破棄
	DX::DeviceResources::Destroy();
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
