#pragma once

#include "SDL.h"
#include "Math/Vector.h"
#include "Racket.h"
#include "Math/Color.h"

#define BallDebug

#define DefaultBallSpeed 200
#define DefaultBallColor Color(1.0f,0.6f,0.1f,1.0f)
#define DefaultBallDirection Vector2(0.2f,0.3f)

using namespace MultiExtend;

class Ball
{
public:
	Ball();
	Ball(Vector2& coord, Vector2& size);
	Ball(Vector2& coord, Vector2& size, Color& color);
	Ball(Vector2& coord, Vector2& size, Color&& color);
	Ball(float x, float y, float w, float h);
	Ball(float x, float y, float w, float h, Color& color);
	Ball(float x, float y, float w, float h, Color&& color);
	~Ball();

	Ball& operator=(Ball&& other) noexcept;
	Ball& operator=(const Ball& other);

	Ball* move(float delta);

	Ball* collision(SDL_Rect * obj);
	Ball* collision(Racket* obj);

	bool isalive(float max_w,float max_h);

	Color& getInstnaceColor();
	SDL_Rect* getSDLDrawInstance() const;

private:
	SDL_Rect& updateInstance();

private:
	Vector2 m_coordinate;
	Vector2 m_speed;
	Vector2 m_direction;
	Color m_color;
	float w, h;

	SDL_Rect* m_ballinstance;
};