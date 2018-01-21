#pragma once

#include "Vector.h"
#include "App\app.h"

class Bullet
{
private:
	float speed;
	float damage;
	float color[3];
	float life;
	bool exists;
	float bulletWidth, bulletHeight;
	Vector position, direction;
	Vector coords[4];

public:
	void fire();
	void update(float deltaTime);
	void draw();
	void init(float _speed, float _damage);
	void fire(Vector _position, Vector _direction);
	void setLife(float life);
	void setColor(float r, float g, float b);
	~Bullet();
	Bullet(float _speed, float _damage, Vector _position, Vector _direction, float _life);
	Vector getPosition();
	float getWidth();
	float getHeight();
	bool isAlive();
	Bullet::Bullet();

};

