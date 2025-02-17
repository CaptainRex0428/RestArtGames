#pragma once

#include "Math/Vector.h"
#include "Math/Color.h"

#include "SDL.h"

#define RacketNDebug

#define DefaultRacketSpeed 200
#define DefaultRacketColor Color(1.0f,1.0f,1.0f,1.0f)

class Racket
{
public:
	Racket();
	Racket(Vector2& coord,Vector2& size);
	Racket(Vector2& coord, Vector2& size, Color& color);
	Racket(Vector2& coord, Vector2& size, Color&& color);
	Racket(float x, float y, float w, float h);
	Racket(float x, float y, float w, float h, Color& color);
	Racket(float x, float y, float w, float h, Color&& color);
	~Racket();

	
	Racket& operator=(Racket&& other) noexcept;
	Racket& operator=(const Racket& other);

	Racket* move(Vector2&& direct, float delta = 0.001) noexcept;
	Racket* move(Vector2& direct, float delta = 0.001);

	Racket* collision(SDL_Rect* obj);

	Color& getInstanceColor();
	SDL_Rect* getSDLDrawInstance() const;
	const Vector2& getInstanceCoordinate();

	Racket* setCoordinate(Vector2& coordinate);

private:
	SDL_Rect& updateInstance();

private:
	Vector2 m_coordinate;
	Vector2 m_speed;
	Color m_color;
	float w, h;
	
	SDL_Rect * m_racketinstance;
};