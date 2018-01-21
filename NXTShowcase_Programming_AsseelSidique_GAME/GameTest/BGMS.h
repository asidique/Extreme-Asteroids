#pragma once
#include "Vector.h"
#include "App\app.h"
#include <vector>

using namespace App;

class cloud {
public:
	~cloud() {
	}
	float color1, color2, color3;
	float width = 5.0f;
	float scrollSpeed = 0.5f;
	int lines = 10;

	cloud() {
		width = 5.0f;
		scrollSpeed = 0.5f;
		color1 = 0.2f;
		color2 = 0.2f;
		color3 = 1.2f;
	}
	void init(float _width, float _scrollSpeed) {
		width = _width;
		scrollSpeed = _scrollSpeed;
		color1 = 0.2f;
		color2 = 0.2f;
		color3 = 1.2f;
		setCoords();
		lines = 0;
	}
	Vector position = Vector(0,0);
	Vector coords[4] = {
		Vector(-width, -width*5),
		Vector(-width, width*5),
		Vector(width, width*5),
		Vector(width, -width*5)
	};
	void setCoords() {
		coords[0] = Vector(-width, -width * 5);
		coords[1] = Vector(-width, width * 5);
		coords[2] = Vector(width, width * 5);
		coords[3] = Vector(width, -width * 5);

	}
	void setColor(float _color1, float _color2, float _color3) {
		color1 = _color1;
		color2 = _color2;
		color3 = _color3;
	}
	void draw() {
		DrawLine(position.x + coords[0].x, position.y + coords[0].y, position.x + coords[1].x, position.y + coords[1].y, color1, color2, color3);
		for (int i = 0; i < lines; i++) {
			DrawLine(position.x + coords[0].x + i, position.y + coords[0].y, position.x + coords[1].x + i, position.y + coords[1].y, color1, color2, color3);
		}
		DrawLine(position.x + coords[1].x, position.y + coords[1].y, position.x + coords[2].x, position.y + coords[2].y, color1, color2, color3);
		DrawLine(position.x + coords[2].x, position.y + coords[2].y, position.x + coords[3].x, position.y + coords[3].y, color1, color2, color3);
		DrawLine(position.x + coords[3].x, position.y + coords[3].y, position.x + coords[0].x, position.y + coords[0].y, color1, color2, color3);
	}
	void update(float deltaTime) {
		position.y += deltaTime*scrollSpeed;
	}
};

class BGMS
{
private:
	std::vector<cloud*> clouds;
	std::vector<cloud*> clouds2;
	float width;
	float scrollSpeed;
	Vector position;
	void CheckBoundry();
	float numberOfStars;
	float timer;

public:
	BGMS();
	void update(float deltaTime);
	void draw();
	void init();
	void Clean();
	void changeColor(float r, float g, float b);
	~BGMS();
};

