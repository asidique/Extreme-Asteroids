#pragma once

#include <vector>
#include "Bullet.h"

class BMS
{
private: 
	std::vector<Bullet*> bullets;
	float rateOfFire, currentRate;
	int currentBullets;

public:
	void fire(float _speed, float _damage, Vector _position, Vector _direction, bool flamethrower, float rOF);
	void update(float deltaTime);
	void draw();
	void BMS::init(float rateOfFire);
	std::vector<Bullet*> getBulletVector();
	void removeBullet(Bullet*);
	~BMS();
	BMS();
	void Clean();
	BMS(float rateOfFire);
};

