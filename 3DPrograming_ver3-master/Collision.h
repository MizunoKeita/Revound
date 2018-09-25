#pragma once

#include "pch.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

class Collision
{
public:
	// ���̍\����
	struct Sphere 
	{
		// ���̒��S  
		Vector3 center;      

		// ���̔��a
		float radius;      
	};

	// ���Ƌ��̏Փ˔���֐� 
	static bool HitCheck_Sphere2Sphere(Sphere a, Sphere b)
	{
		// ���S�Ԃ̋����̕������v�Z 
		Vector3 d = a.center - b.center;
		float dist2 = d.Dot(d);

		// �������������������������a�̍��v�����������ꍇ�ɋ��͌������Ă���
		float radiusSum = a.radius + b.radius;
		return dist2 <= radiusSum * radiusSum;
	}

};