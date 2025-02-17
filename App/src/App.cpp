#include "Color/Color.h"
#include "Vector/Vector.h"
#include <stdint.h>
#include <iostream>
#include <vector>

class EA
{
public:
	EA(Vector3 pos)
		:m_pos(pos)
	{

	}

	Vector3 m_pos;
};

int main(int argc, char** argv)
{
	EA a(Vector3(1.0f, 2.0f, 3.0f));

	std::cout << a.m_pos << std::endl;
}