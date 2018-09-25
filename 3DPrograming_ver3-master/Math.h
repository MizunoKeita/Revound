#pragma once
class Math
{
public:

	//���������߂�
	template<typename T>
	static T Distance(T pint1, T pint2)
	{
		auto length = pint1 - pint2;
		return Abs<T>(length);
	}

	//��Βl�����߂�
	template<typename T>
	static T Abs(T num)
	{
		if (num < 0)
		{
			num *= -1;
		}
		return num;
	}

};

