#include "pch.h"
#include "Triangle.h"


Triangle::Triangle(GLfloat initialTranslationX = 0.0f, GLfloat initialTranslationY = 0.0f, GLfloat initialAngle = 0.0f)
{
	this->initialX = initialTranslationX;
	this->initialY = initialTranslationY;
	this->initialRotationAngle = initialAngle;
}

Triangle::~Triangle()
{
}

void Triangle::spread(GLfloat spreadAmnt)
{
	if (expanding) {
		this->spreadAmnt += spreadAmnt;
	}
	else {
		this->spreadAmnt -= spreadAmnt;
	}

	if (expanding && this->spreadAmnt >= 1.0f) {
		this->expanding = false;
	}
	if (!expanding && this->spreadAmnt <= 0.0f) {
		this->expanding = true;
	}
}

void Triangle::rotate(GLfloat rotationAngle)
{
	if (this->rotationAngle >= 360.0f) {
		this->rotationAngle = 0.0f;
	}
	this->rotationAngle += rotationAngle;
}

void Triangle::render()
{
	glPushMatrix();
	this->expand();
	this->rotateAroundCentreOfMass();
	this->setInitialPosition();
	this->setGLVertices();
	glPopMatrix();
}

void Triangle::setColor(GLfloat r, GLfloat g, GLfloat b)
{
	this->color[0] = r;
	this->color[1] = g;
	this->color[2] = b;
}

void Triangle::setOpacity(GLfloat alpha)
{
	this->color[3] = alpha;
}

void Triangle::setGLVertices() const
{
	glBegin(GL_POLYGON);
	glColor4fv(this->color);
	glVertex2fv(points[0]);
	glVertex2fv(points[1]);
	glVertex2fv(points[2]);
	glEnd();
}

void Triangle::setInitialPosition() const
{
	glScalef(0.2f, 0.2f, 1.0f);								// ^ 3
	glRotatef(initialRotationAngle, 0.0f, 0.0f, 1.0f);		// | 2 Order of operations
	glTranslatef(initialX, initialY, 0.0f);					// | 1
}

void Triangle::undoInitialPosition() const
{
	glTranslatef(-initialX, -initialY, 0.0f);
	glRotatef(-initialRotationAngle, 0.0f, 0.0f, 1.0f);
	glScalef(1.0f/0.2f, 1.0f/0.2f, 1.0f);
}

void Triangle::rotateAroundCentreOfMass() const
{
	setInitialPosition();
	GLfloat xavg = (points[0][0] + points[1][0] + points[2][0]) / 3.0f;
	GLfloat yavg = (points[0][1] + points[1][1] + points[2][1]) / 3.0f;
	glTranslatef(xavg, yavg, 0.0f);
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glTranslatef(-xavg, -yavg, 0.0f);
	undoInitialPosition();
}

void Triangle::expand() const
{
	glScalef(1.0f + spreadAmnt, 1.0f + spreadAmnt, 1.0f);
	setInitialPosition();
	glScalef(1/ (1.0f + spreadAmnt), 1/(1.0f + spreadAmnt), 1.0f);
	undoInitialPosition();
}
