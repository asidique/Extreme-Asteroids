#pragma once
#include "Object.h"
#include <vector>

class Enemy : Object
{
private:
	Vector enemyDrawCoords[4];
	float rateOfFire;
	float width, height;
	void CheckBoundary(int _width, int height);
	std::vector<Vector> worldCoords;
	bool eliteEnemies;


public:
	Enemy();
	Enemy(Vector pos, float width, float height, int _phase);
	void makeElite();
	void draw();
	void update(float deltaTime);
	void init();
	float getWidth();
	float getHeight();
	Vector getPosition();
	float speed;
	int phase;
	void setPosition(Vector pos);
	~Enemy();
};

