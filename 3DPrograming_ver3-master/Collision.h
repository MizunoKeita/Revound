#pragma once

#include "pch.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Collision
{
public:
	// 球の構造体
	struct Sphere 
	{
		// 球の中心  
		Vector3 center;      

		// 球の半径
		float radius;      
	};

	// 球と球の衝突判定関数 
	static bool HitCheck_Sphere2Sphere(Sphere a, Sphere b)
	{
		// 中心間の距離の平方を計算 
		Vector3 d = a.center - b.center;
		float dist2 = d.Dot(d);

		// 平方した距離が平方した半径の合計よりも小さい場合に球は交差している
		float radiusSum = a.radius + b.radius;
		return dist2 <= radiusSum * radiusSum;
	}

};