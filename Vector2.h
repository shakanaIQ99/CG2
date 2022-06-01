#pragma once
class Vector2
{
public:
	float x;
	float y;

public:
	//コンストラクタ
	Vector2();					//零ベクトル生成
	Vector2(float x, float y);	//x,y成分を指定して生成

	//関数
	float length()const;				//ノルムを求める
	Vector2& normalize();				//正規化
	float dot(const Vector2& v)const;	//内積
	float cross(const Vector2& v)const;	//外積

	Vector2 operator+()const;
	Vector2 operator-()const;

	Vector2& operator+=(const Vector2& v);
	Vector2& operator-=(const Vector2& v);
	Vector2& operator*=(float s);
	Vector2& operator/=(float s);
};
const Vector2 operator+(const Vector2& v1, const Vector2& v2);
const Vector2 operator-(const Vector2& v1, const Vector2& v2);
const Vector2 operator*(const Vector2& v, float s);
const Vector2 operator*(float s, const Vector2& v);
const Vector2 operator/(const Vector2& v, float s);
