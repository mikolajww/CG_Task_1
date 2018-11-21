#pragma once

#include "glut.h"


class Triangle
{
public:
	Triangle(GLfloat initialTranslationX, GLfloat initialTranslationY, GLfloat initialAngle);
	~Triangle();
	void spread(GLfloat translationAmnt);
	void rotate(GLfloat rotationAngle);
	void render();
	void setColor(GLfloat r, GLfloat g, GLfloat b);
	void setOpacity(GLfloat alpha);

private:
	GLfloat initialX = 0.0f;
	GLfloat initialY = 0.0f;
	GLfloat spreadAmnt = 0.0f;
	GLfloat initialRotationAngle = 0.0f;
	GLfloat rotationAngle = 0.0f;
	const GLfloat points[3][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 0.0f, 1.0f } };
	GLfloat color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	bool expanding = true;

	void setGLVertices() const;
	void setInitialPosition() const;
	void undoInitialPosition() const;
	void rotateAroundCentreOfMass() const;
	void expand() const;
};

