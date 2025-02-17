#pragma once

#include <stdint.h>

enum ColorFloatIndex
{
	r, g, b, a,
	x, y, z, w
};

enum ColorByteIndex
{
	R, G, B, A,
	X, Y, Z, W
};

class Color
{
public:
	Color();
	Color(float r,float g,float b, float a);
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
	Color(int r, int g, int b, int a);

	Color(Color& other);
	Color(Color&& other) noexcept;

	float operator[](ColorFloatIndex index);
	int operator[](ColorByteIndex index);

	Color& operator=(const Color& other);

private:

private:
	float m_r, m_g, m_b, m_a;


};