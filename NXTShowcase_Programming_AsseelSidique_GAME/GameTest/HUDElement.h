#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "App\app.h"

using namespace App;

class Heart {
private:
	Vector coords[8];

public:
	Vector position;
	Heart() {}
	Heart(Vector pos) {
		coords[0] = Vector(0, -10.0f);
		coords[1] = Vector(-7.0f, 0.0f);
		coords[2] = Vector(-2.0f, 5.0f);
		coords[3] = Vector(-0.5f, 2.0f);
		coords[4] = Vector(0.0f, 0.0f);
		coords[5] = Vector(0.5f, 2.0f);
		coords[6] = Vector(2.0f, 5.0f);
		coords[7] = Vector(7.0f, 0.0f);
		position = pos;
	}
	void draw() {
		DrawLine(position.x + coords[0].x, position.y + coords[0].y, position.x + coords[1].x, position.y + coords[1].y, 1.0f, 0.0f, 0.0f);
		DrawLine(position.x + coords[1].x, position.y + coords[1].y, position.x + coords[2].x, position.y + coords[2].y, 1.0f, 0.0f, 0.0f);
		DrawLine(position.x + coords[2].x, position.y + coords[2].y, position.x + coords[3].x, position.y + coords[3].y, 1.0f, 0.0f, 0.0f);
		DrawLine(position.x + coords[3].x, position.y + coords[3].y, position.x + coords[4].x, position.y + coords[4].y, 1.0f, 0.0f, 0.0f);
		DrawLine(position.x + coords[4].x, position.y + coords[4].y, position.x + coords[5].x, position.y + coords[5].y, 1.0f, 0.0f, 0.0f);
		DrawLine(position.x + coords[5].x, position.y + coords[5].y, position.x + coords[6].x, position.y + coords[6].y, 1.0f, 0.0f, 0.0f);
		DrawLine(position.x + coords[6].x, position.y + coords[6].y, position.x + coords[7].x, position.y + coords[7].y, 1.0f, 0.0f, 0.0f);
		DrawLine(position.x + coords[7].x, position.y + coords[7].y, position.x + coords[0].x, position.y + coords[0].y, 1.0f, 0.0f, 0.0f);
	}
	void update(float deltaTime) {}
	void init() {}
};

