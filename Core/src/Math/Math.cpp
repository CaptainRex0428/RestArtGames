#include "Math/Math.h"

Math::Math() = default;

Math::~Math() = default;

Math& Math::Get()
{
	static Math instance;
	return instance;
}

int Math::Clamp(int src, int min, int max)
{
	if (src <= min)
	{
		return min;
	}

	if (src >= max)
	{
		return max;
	}

	return src;
}

float Math::Clamp(float src, float min, float max)
{
	if (src <= min)
	{
		return min;
	}

	if (src >= max)
	{
		return max;
	}

	return src;
}

uint8_t Math::Clamp(uint8_t src, uint8_t min, uint8_t max)
{
	if (src <= min)
	{
		return min;
	}

	if (src >= max)
	{
		return max;
	}

	return src;
}

double& Math::limit_min(double& src, double min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

float& Math::limit_min(float& src, float min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

int& Math::limit_min(int& src, int min)
{
	if (src < min)
	{
		src = min;
	}

	return src;
}

double& Math::limit_max(double& src, double max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

float& Math::limit_max(float& src, float max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}

int& Math::limit_max(int& src, int max)
{
	if (src > max)
	{
		src = max;
	}

	return src;
}