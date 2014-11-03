#ifndef VEC2_H
#define VEC2_H

struct Vec2
{
	int x;
	int y;
	Vec2()
	{

	}
	Vec2(int initX,int initY)
	{
		x = initX;
		y = initY;
	}
	
	//Operator Overloading

	Vec2* operator += (Vec2 b)
	{
		x += b.x;
		y += b.y;
		return this;
	}
	Vec2* operator -= (Vec2 b)
	{
		x -= b.x;
		y -= b.y;
		return this;
	}
	
};

inline Vec2 operator + (Vec2 a, Vec2 b)
{
	Vec2 result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	return result;
}
inline Vec2 operator - (Vec2 a, Vec2 b)
{
	Vec2 result;
	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return result;
}

#endif