#ifndef _PLAYER_H
#define _PLAYER_H

#include <iostream>
#include "Object.h"
#include <vector>
#include <string>

class player : Object
{
private:
	void updateInput(float deltaTime);
	void shoot();
	Vector position;
	Vector playerDrawCoords[3];
	Vector direction;
	Vector acceleration;
	Vector velocity;
	std::vector<Vector> worldCoords;
	int lives;
	float speed;
	float rateOfFire;
	float maxSpeed;
	float rotationAngle;
	float width, height;
	float pickupTimer;
	float displayTimer;
	void CheckBoundary(int _width, int _height);
	void updateWorldCoords();
	void setDefaultValues();
	float color1, color2, color3;
	bool mouseOn, rotationClock;
	std::string displayText;

public:
	void init(bool _mouseOn);
	void init();
	void draw();
	void update(float deltaTime);
	Vector getPosition();
	float getRateOfFire();
	Vector getDirection();
	float getWidth();
	bool invincible, flamethrower;
	void GiveUpgrade(int type);
	player();
	player(bool _mouseOn);
	~player();
	void Clean();
};

#endif