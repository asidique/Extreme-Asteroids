#pragma once
#include "stdafx.h"
#include "Object.h"
#include "App\app.h"
using namespace App;

class MenuObject {
private:
	Vector coords[4];
	char* name;
	Vector position;
	bool toggle;

public:
	bool isSelected;

	MenuObject(char* _name, Vector pos) {
		name = _name;
		position = pos;
		init();
		isSelected = false;
	}
	void draw() {
		if (isSelected) {
			DrawLine(position.x + coords[0].x, position.y + coords[0].y, position.x + coords[1].x, position.y + coords[1].y, 1.0f, 0.0f, 1.0f);
			DrawLine(position.x + coords[1].x, position.y + coords[1].y, position.x + coords[3].x, position.y + coords[3].y, 1.0f, 0.0f, 1.0f);
			DrawLine(position.x + coords[3].x, position.y + coords[3].y, position.x + coords[2].x, position.y + coords[2].y, 1.0f, 0.0f, 1.0f);
			DrawLine(position.x + coords[2].x, position.y + coords[2].y, position.x + coords[0].x, position.y + coords[0].y, 1.0f, 0.0f, 1.0f);
		}
		else {
			DrawLine(position.x + coords[0].x, position.y + coords[0].y, position.x + coords[1].x, position.y + coords[1].y, 1.0f, 1.0f, 1.0f);
			DrawLine(position.x + coords[1].x, position.y + coords[1].y, position.x + coords[3].x, position.y + coords[3].y, 1.0f, 1.0f, 1.0f);
			DrawLine(position.x + coords[3].x, position.y + coords[3].y, position.x + coords[2].x, position.y + coords[2].y, 1.0f, 1.0f, 1.0f);
			DrawLine(position.x + coords[2].x, position.y + coords[2].y, position.x + coords[0].x, position.y + coords[0].y, 1.0f, 1.0f, 1.0f);
		}

		if (strcmp(name, "Play") == 0) {
			Print(position.x - 20.0f, position.y, "PLAY", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
		}
		else if (strcmp(name, "Quit") == 0) {
			Print(position.x - 20.0f, position.y, "QUIT", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
		}
		else if (strcmp(name, "Controls") == 0) {
			Print(position.x - 35.0f, position.y, "CONTROLS", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
			char* on; 
			if (toggle) {
				on= "MOUSE OFF";
			}
			else {
				on = "MOUSE ON";
			}
			Print(position.x - 35.0f, position.y-20.0f, on, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
		}
		else if (strcmp(name, "Difficulty") == 0) {
			Print(position.x - 35.0f, position.y, "DIFFICULTY", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
			char* on;
			if (toggle) {
				on = "HARD";
			}
			else {
				on = "EASY";
			}
			Print(position.x - 35.0f, position.y - 20.0f, on, 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
		}
	}
	void update(float deltaTime) {
		if (App::IsKeyPressed(VK_RIGHT) || App::IsKeyPressed('D')) {
			if (isSelected) {
				if (!toggle) {
					toggle = true;
				}
			}
		}
		else if (App::IsKeyPressed(VK_LEFT) || App::IsKeyPressed('A')) {
			if (isSelected) {
				toggle = false;
			}
		}
	};
	void init() {
		coords[0] = Vector(-200, 35);
		coords[1] = Vector(-200, -35);
		coords[2] = Vector(200, 35);
		coords[3] = Vector(200, -35);
	}
	void setPosition(Vector pos) {
		position = pos;
	}
	const char* getName() {
		return name;
	}
	void setName(char* _name) {
		name = _name;
	}
};

