#pragma once

#include <iostream>

#include "Math/Math.h"

class Vector3
{
public:
	Vector3();
	Vector3(float num);
	Vector3(float i_x, float i_y,float i_z);
	Vector3(Vector3&& other) noexcept;
	Vector3(const Vector3 & other);
	~Vector3();

	Vector3& operator=(Vector3&& other) noexcept;
	Vector3& operator=(const Vector3& other);

public:
	float x, y, z;

};

class Vector2
{
public:
	Vector2();
	Vector2(float num);
	Vector2(float i_x, float i_y);
	~Vector2();

	Vector2(const Vector2& other);
	Vector2(Vector2&& other) noexcept;

	Vector2& operator=(const Vector2& other);

	Vector2 operator+(Vector2& other);
	Vector2 operator+(float num);

	Vector2 operator-(Vector2& other);
	Vector2 operator-(float num);

	Vector2 operator*(Vector2& other);
	Vector2 operator*(float num);

	Vector2& operator+=(Vector2&& other);
	Vector2& operator+=(Vector2& other);
	Vector2& operator+=(float num);

	float length();
	Vector2 normalize();

	static float dot(Vector2& va, Vector2& vb);
	static Vector3 cross(Vector2& va, Vector2& vb);

public:
	float x, y;

};

class Vector4
{

};

std::ostream& operator<<(std::ostream& out, const Vector2& vector);
std::ostream& operator<<(std::ostream& out, const Vector3& vector);