#pragma once

extern GLfloat window_width;
extern GLfloat window_height;

class Rect
{
public:
	Rect();
	Rect(GLfloat _x, GLfloat _y, GLsizei _rsize);

	~Rect();

	void Update(float dt);
	void Render();
	void SetColor(float r, float g, float b);
	void SetSpeed(float _xstep, float _ystep);

	GLfloat x = 0.0f;
	GLfloat y = 0.0f;
	GLsizei rsize = 50.0f;

	GLfloat xstep = 0.0f;
	GLfloat ystep = 0.0f;
	float prevxStep = 0.0f;
	float prevyStep = 0.0f;

private:
	GLfloat r = 0.0f;
	GLfloat g = 0.0f;
	GLfloat b = 0.0f;

};

