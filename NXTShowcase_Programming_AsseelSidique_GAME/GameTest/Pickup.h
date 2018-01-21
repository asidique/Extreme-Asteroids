#pragma once
#include "stdafx.h"
#include "Vector.h"
#include "App\app.h"

using namespace App;

/*
0-Increase Rate of Fire
1-Super Armor
2-One Up
3-Flamethrower
*/
class Pickup {
public:
	int type;
	float life, width, height;
	float r = 1.0f;
	float g = 2.0f;
	float b = 3.0f;
	bool isScorePickup = false;
	Vector position;
	Vector coords[4];
	void Update(float deltaTime) {
		if (!isScorePickup) {
			r += 0.002f;
			g += 0.003f;
			b += 0.004f;
		}
		life -= deltaTime;
	}
	Pickup(Vector pos, float _life, int _type) {
		if (_life > 8000.0f) {
			isScorePickup = true;
			r = 0.0f;
			g = 3.14f/2.0f;
			b = 0.0f;
		}
		width = height = 10.0f;
		position = pos;
		life = _life;
		type = _type;
		coords[0] = Vector(-10.0f, 10.0f);
		coords[1] = Vector(-10.0f, -10.0f);
		coords[2] = Vector(10.0f, 10.0f);
		coords[3] = Vector(10.0f, -10.0f);
	}
	void Draw() {
		DrawLine(position.x + coords[0].x, position.y + coords[0].y, position.x + coords[1].x, position.y + coords[1].y, sin(r), sin(g), sin(b));
		DrawLine(position.x + coords[1].x, position.y + coords[1].y, position.x + coords[2].x, position.y + coords[2].y, sin(r), sin(g), sin(b));
		DrawLine(position.x + coords[2].x, position.y + coords[2].y, position.x + coords[3].x, position.y + coords[3].y, sin(r), sin(g), sin(b));
		DrawLine(position.x + coords[3].x, position.y + coords[3].y, position.x + coords[0].x, position.y + coords[0].y, sin(r), sin(g), sin(b));
	}


};