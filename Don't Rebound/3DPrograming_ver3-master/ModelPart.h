#pragma once
#include "pch.h"

// モデルパーツ構造体
struct ModelPart
{
	// モデルハンドル
	DirectX::Model* model = nullptr;

	// ワールド行列
	DirectX::SimpleMath::Matrix world;

	// 変換行列
	DirectX::SimpleMath::Matrix transform;

	// 初期位置行列
	DirectX::SimpleMath::Matrix initial;

	// 子へのポインタ
	ModelPart* child = nullptr;

	// 兄弟へのポインタ
	ModelPart* sibling = nullptr;

	// 各パーツの初期位置行列を親の座標系に変換する関数
	static void SetupMatrix(ModelPart* parts, DirectX::SimpleMath::Matrix* offset)
	{
		if (parts->child) SetupMatrix(parts->child, &parts->initial.Invert());
		if (parts->sibling) SetupMatrix(parts->sibling, offset);
		if (offset) parts->initial *= *offset;
	}

	// 各パーツのワールド行列を更新する関数
	static void UpdateMatrix(ModelPart* parts, DirectX::SimpleMath::Matrix* parent)
	{
		parts->world = parts->transform * parts->initial;
		parts->world *= *parent;
		if (parts->child) UpdateMatrix(parts->child, &parts->world);
		if (parts->sibling) UpdateMatrix(parts->sibling, parent);
	}
};
