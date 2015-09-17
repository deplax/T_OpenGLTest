#include "pch.h"
#include "Rect.h"

Rect::Rect()
{
}

Rect::Rect(GLfloat _x, GLfloat _y)
{
	x = _x;
	y = _y;
}

Rect::~Rect()
{
}

void Rect::SetColor(float _r, float _g, float _b){
	r = _r;
	g = _g;
	b = _b;
}

void Rect::SetSpeed(float _xstep, float _ystep){
	xstep = _xstep;
	ystep = _ystep;
};

void Rect::Update(float dt)
{
	if (dt <= 0)
		return;
	if (x > window_width - rsize || x < -window_width)
		xstep = -xstep;
	if (y > window_height - rsize || y < -window_height)
		ystep = -ystep;
	if (x > window_width - rsize)
		x = window_width - rsize - 1;
	if (y > window_height - rsize)
		y = window_height - rsize - 1;

	x += xstep * dt;
	y += ystep * dt;

	prevxStep = xstep * dt;
	prevyStep = ystep * dt;

}

void Rect::Render()
{
	glColor3f(r, g, b);
	glRectf(x, y, x + rsize, y + rsize);
}
