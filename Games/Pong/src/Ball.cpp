#include "Ball.h"

Ball::Ball()
	:m_coordinate(Vector2(500,500)),
	m_speed(Vector2(DefaultBallSpeed,DefaultBallSpeed)),
	m_direction(DefaultBallDirection),
	m_color(DefaultBallColor),
	w(10),h(10),
	m_ballinstance(nullptr)
{
	updateInstance();
}

Ball::Ball(Vector2& coord, Vector2& size)
	:m_coordinate(coord),
	m_speed(Vector2(DefaultBallSpeed, DefaultBallSpeed)),
	m_direction(DefaultBallDirection),
	m_color(DefaultBallColor),
	w(size.x), h(size.y),
	m_ballinstance(nullptr)
{
	updateInstance();
}

Ball::Ball(Vector2& coord, Vector2& size, Color& color)
	:m_coordinate(coord),
	m_speed(Vector2(DefaultBallSpeed, DefaultBallSpeed)),
	m_direction(DefaultBallDirection),
	m_color(color),
	w(size.x), h(size.y),
	m_ballinstance(nullptr)
{
	updateInstance();
}

Ball::Ball(Vector2& coord, Vector2& size, Color&& color)
	:m_coordinate(coord),
	m_speed(Vector2(DefaultBallSpeed, DefaultBallSpeed)),
	m_direction(DefaultBallDirection),
	m_color(color),
	w(size.x), h(size.y),
	m_ballinstance(nullptr)
{
	updateInstance();
}

Ball::Ball(float x, float y, float w, float h)
	:m_coordinate(Vector2(x,y)),
	m_speed(Vector2(DefaultBallSpeed, DefaultBallSpeed)),
	m_direction(DefaultBallDirection),
	m_color(DefaultBallColor),
	w(w), h(h),
	m_ballinstance(nullptr)
{
	updateInstance();
}

Ball::Ball(float x, float y, float w, float h, Color& color)
	:m_coordinate(Vector2(x, y)),
	m_speed(Vector2(DefaultBallSpeed, DefaultBallSpeed)),
	m_direction(DefaultBallDirection),
	m_color(color),
	w(w), h(h),
	m_ballinstance(nullptr)
{
	updateInstance();
}

Ball::Ball(float x, float y, float w, float h, Color&& color)
	:m_coordinate(Vector2(x, y)),
	m_speed(Vector2(DefaultBallSpeed, DefaultBallSpeed)),
	m_direction(DefaultBallDirection),
	m_color(color),
	w(w), h(h),
	m_ballinstance(nullptr)
{
	updateInstance();
}

Ball::~Ball()
{
	if (m_ballinstance) 
	{
		delete m_ballinstance;
	}

	m_coordinate.~Vector2();
	m_speed.~Vector2();
	m_direction.~Vector2();

	m_color.~Color();
}

Ball& Ball::operator=(Ball&& other) noexcept
{
	m_coordinate = other.m_coordinate;
	m_speed = other.m_speed;
	m_direction = other.m_direction;
	m_color = other.m_color;
	w = other.w;
	h = other.h;

	updateInstance();

	return *this;
}

Ball& Ball::operator=(const Ball& other)
{
	m_coordinate = other.m_coordinate;
	m_speed = other.m_speed;
	m_direction = other.m_direction;
	m_color = other.m_color;
	w = other.w;
	h = other.h;

	updateInstance();

	return *this;
}

Ball* Ball::move(float delta)
{
	m_coordinate += m_direction.normalize() * m_speed * delta;
	updateInstance();

	return this;
}

Ball* Ball::collision(SDL_Rect* obj)
{
	if ((m_coordinate.y - h / 2) < obj->y + obj->h
		&& (m_coordinate.y - h / 2) > obj->y
		&& m_coordinate.x > obj->x
		&& m_coordinate.x < obj->x + obj->w)
	{
		m_coordinate.y = obj->y + obj->h + h / 2;
		updateInstance();

		m_direction.y = -1 * m_direction.y;
	}

	if ((m_coordinate.y + h / 2) > obj->y
		&& (m_coordinate.y + h / 2) < obj->y + obj->h
		&& m_coordinate.x > obj->x
		&& m_coordinate.x < obj->x + obj->w)
	{
		m_coordinate.y = obj->y - h / 2;
		updateInstance();

		m_direction.y = -1 * m_direction.y;
	}

	if ((m_coordinate.x - w/2) < obj->x + obj->w
		&& (m_coordinate.x - w/2) > obj->x 
		&& m_coordinate.y > obj->y
		&& m_coordinate.y < obj->y + obj->h)
	{
		m_coordinate.x = obj->x + obj->w + w / 2;
		updateInstance();
		m_direction.x = -1 * m_direction.x;
	}

	if ((m_coordinate.x + w/2) > obj->x
		&& (m_coordinate.x + w / 2) < obj->x + obj->w
		&& m_coordinate.y > obj->y
		&& m_coordinate.y < obj->y + obj->h)
	{
		m_coordinate.x = obj->x - w/2;
		updateInstance();
		m_direction.x = -1 * m_direction.x;
	}

	return this;
}

Ball* Ball::collision(Racket* obj)
{
	if ((m_coordinate.y - h / 2) < obj->getSDLDrawInstance()->y + obj->getSDLDrawInstance()->h
		&& (m_coordinate.y - h / 2) > obj->getSDLDrawInstance()->y
		&& m_coordinate.x > obj->getSDLDrawInstance()->x
		&& m_coordinate.x < obj->getSDLDrawInstance()->x + obj->getSDLDrawInstance()->w)
	{
		m_coordinate.y = obj->getSDLDrawInstance()->y + obj->getSDLDrawInstance()->h + h / 2;
		updateInstance();
		m_direction.y = -1 * m_direction.y;
	}

	if ((m_coordinate.y + h / 2) > obj->getSDLDrawInstance()->y
		&& (m_coordinate.y + h / 2) < obj->getSDLDrawInstance()->y + obj->getSDLDrawInstance()->h
		&& m_coordinate.x > obj->getSDLDrawInstance()->x
		&& m_coordinate.x < obj->getSDLDrawInstance()->x + obj->getSDLDrawInstance()->w)
	{
		m_coordinate.y = obj->getSDLDrawInstance()->y - h / 2;
		updateInstance();
		m_direction.y = -1 * m_direction.y;
	}

	if ((m_coordinate.x - w / 2) < obj->getSDLDrawInstance()->x + obj->getSDLDrawInstance()->w
		&& (m_coordinate.x - w / 2) > obj->getSDLDrawInstance()->x
		&& m_coordinate.y > obj->getSDLDrawInstance()->y
		&& m_coordinate.y < obj->getSDLDrawInstance()->y + obj->getSDLDrawInstance()->h)
	{
		m_coordinate.x = obj->getSDLDrawInstance()->x + obj->getSDLDrawInstance()->w + w / 2;
		updateInstance();
		m_direction.x = -1 * m_direction.x;
	}

	if ((m_coordinate.x + w / 2) > obj->getSDLDrawInstance()->x
		&& (m_coordinate.x + w / 2) < obj->getSDLDrawInstance()->x + obj->getSDLDrawInstance()->w
		&& m_coordinate.y > obj->getSDLDrawInstance()->y
		&& m_coordinate.y < obj->getSDLDrawInstance()->y + obj->getSDLDrawInstance()->h)
	{
		m_coordinate.x = obj->getSDLDrawInstance()->x - w / 2;
		updateInstance();
		m_direction.x = -1 * m_direction.x;
	}

	return this;
}

bool Ball::isalive(float max_w, float max_h)
{
	if (m_coordinate.x < 0 ||
		m_coordinate.x > max_w ||
		m_coordinate.y < 0 ||
		m_coordinate.y > max_h)
		return false;

	return true;
}

Color& Ball::getInstnaceColor()
{
	return m_color;
}

SDL_Rect* Ball::getSDLDrawInstance() const
{
	return m_ballinstance;
}

SDL_Rect& Ball::updateInstance()
{
	if (!m_ballinstance)
	{
		m_ballinstance = new SDL_Rect();
	}

	m_ballinstance->x = (int)(m_coordinate.x - w / 2);
	m_ballinstance->y = (int)(m_coordinate.y - h / 2);
	m_ballinstance->w = (int)w;
	m_ballinstance->h = (int)h;

	return *m_ballinstance;
}
