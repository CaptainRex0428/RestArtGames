#include "Racket.h"

#include <iostream>
#include <utility>

Racket::Racket()
	:m_coordinate(0, 0),
	m_speed(DefaultRacketSpeed, DefaultRacketSpeed), 
	w(0), h(0),
	m_racketinstance(nullptr),
	m_color(DefaultRacketColor)
{
	updateInstance();
}

Racket::Racket(Vector2& coord, Vector2& size)
	:m_coordinate(coord),
	m_speed(DefaultRacketSpeed, DefaultRacketSpeed),
	w(size.x), h(size.y),
	m_racketinstance(nullptr),
	m_color(DefaultRacketColor)
{
	updateInstance();
}

Racket::Racket(Vector2& coord, Vector2& size, Color& color)
	:m_coordinate(coord),
	m_speed(DefaultRacketSpeed, DefaultRacketSpeed),
	w(size.x), h(size.y),
	m_racketinstance(nullptr),
	m_color(color)
{
	updateInstance();
}

Racket::Racket(Vector2& coord, Vector2& size, Color&& color)
	:m_coordinate(coord),
	m_speed(DefaultRacketSpeed, DefaultRacketSpeed),
	w(size.x), h(size.y),
	m_racketinstance(nullptr),
	m_color(color)
{
	updateInstance();
}

Racket::Racket(float x, float y, float w, float h)
	:m_coordinate(x,y),
	m_speed(DefaultRacketSpeed, DefaultRacketSpeed),
	w(w), h(h),
	m_racketinstance(nullptr),
	m_color(DefaultRacketColor)
{
	updateInstance();
}

Racket::Racket(float x, float y, float w, float h, Color& color)
	:m_coordinate(x, y),
	m_speed(DefaultRacketSpeed, DefaultRacketSpeed),
	w(w), h(h),
	m_racketinstance(nullptr),
	m_color(color)
{
	updateInstance();
}

Racket::Racket(float x, float y, float w, float h, Color&& color)
	:m_coordinate(x, y),
	m_speed(DefaultRacketSpeed, DefaultRacketSpeed),
	w(w), h(h),
	m_racketinstance(nullptr),
	m_color(color)
{
	updateInstance();
}

Racket::~Racket() 
{
	delete m_racketinstance;

	m_coordinate.~Vector2();
	m_speed.~Vector2();

	m_color.~Color();
}

Racket* Racket::move(Vector2& direct, float delta)
{
	return move(std::move(direct), delta);
}

Racket* Racket::move(Vector2&& direct, float delta) noexcept
{
#ifdef RacketDebug
	std::cout << direct.normalize() * m_speed * delta << std::endl;
#endif
	m_coordinate += direct.normalize() * m_speed * delta;

	updateInstance();

	return this;
}

Racket* Racket::collision(SDL_Rect* obj)
{
	if((m_coordinate.y-h/2) < obj->y + obj->h
		&& (m_coordinate.y - h/2) > obj->y
		&& m_coordinate.x > obj->x 
		&& m_coordinate.x < obj->x+obj->w)
	{
		m_coordinate.y = obj->y + obj->h + h/2;
		updateInstance();
	}

	if((m_coordinate.y+h/2) > obj->y
		&& (m_coordinate.y+h/2) < obj->y + obj->h
		&& m_coordinate.x > obj->x 
		&& m_coordinate.x < obj->x + obj->w)
	{
		m_coordinate.y = obj->y - h/2;
		updateInstance();
	}

	if ((m_coordinate.x - w / 2) < obj->x + obj->w
		&& (m_coordinate.x - w / 2) > obj->x
		&& m_coordinate.y > obj->y
		&& m_coordinate.y < obj->y + obj->h)
	{
		m_coordinate.x = obj->x + obj->w + w / 2;
		updateInstance();
	}

	if ((m_coordinate.x + w / 2) > obj->x
		&& (m_coordinate.x + w / 2) < obj->x + obj->w
		&& m_coordinate.y > obj->y
		&& m_coordinate.y < obj->y + obj->h)
	{
		m_coordinate.x = obj->x - w / 2;
		updateInstance();
	}

	return this;
}

Color& Racket::getInstanceColor()
{
	return m_color;
}


SDL_Rect& Racket::updateInstance()
{
	if (! m_racketinstance)
	{
		m_racketinstance = new SDL_Rect();
	}

	m_racketinstance->x = (int)(m_coordinate.x - w/2) ;
	m_racketinstance->y = (int)(m_coordinate.y - h/2);
	m_racketinstance->w = (int)w;
	m_racketinstance->h = (int)h;

	return *m_racketinstance;
}

SDL_Rect * Racket::getSDLDrawInstance() const
{
	return m_racketinstance;
}

const Vector2& Racket::getInstanceCoordinate()
{
	return m_coordinate;
}

Racket* Racket::setCoordinate(Vector2& coordinate)
{
	m_coordinate = std::move(coordinate);
	updateInstance();
	return this;
}

Racket& Racket::operator=(Racket && other) noexcept
{
	m_coordinate = other.m_coordinate;
	m_color = other.m_color;
	m_speed = other.m_speed;
	w = other.w;
	h = other.h;

	updateInstance();

	return *this;
}


Racket& Racket::operator=(const Racket & other)
{
	m_coordinate = other.m_coordinate;
	m_color = other.m_color;
	m_speed = other.m_speed;
	w = other.w;
	h = other.h;

	updateInstance();

	return *this;
}

