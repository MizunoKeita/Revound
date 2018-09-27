#include "pch.h"
#include "Monster.h"
#include "DebugCamera.h"
#include "Game.h"
#include "Math.h"

Monster::Monster()
{
	//デバイスの取得
	ID3D11Device* device = DX::DeviceResources::GetInstance()->GetD3DDevice();

	// エフェクトファクトリー
	EffectFactory fx(device);

	//モデルを取得
	m_model = Model::CreateFromCMO(device, L"Resources\\Models\\Monster1.cmo", fx);
}

void Monster::Render()
{
	if (m_game&&m_model)
	{
		//モデルを描画
		m_model->Draw(m_game->GetContext(), *m_game->GetStates(), m_world, DebugCamera::GetView(), DebugCamera::GetProjection());
	}
}