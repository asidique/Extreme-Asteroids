#pragma once
#include "Vector.h"
#include "App\app.h"

class Object {
protected:
	Vector position;

public:
	virtual void draw() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void init() = 0;

};