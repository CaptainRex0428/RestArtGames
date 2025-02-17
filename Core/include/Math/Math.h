#pragma once

#include <stdint.h>

class Math
{
public:
	Math(Math&) = delete;

	static int Clamp(int src, int min = 0, int max = 1);
	static float Clamp(float src, float min = 0, float max = 1);
	static uint8_t Clamp(uint8_t src, uint8_t min = 0, uint8_t max = 1);

	static double& limit_min(double& src, double min);
	static float& limit_min(float& src, float min);
	static int& limit_min(int& src, int min);

	static double& limit_max(double& src, double max);
	static float& limit_max(float& src, float max);
	static int& limit_max(int& src, int max);

private:
	Math();
	~Math();

	static Math& Get();

private:
};