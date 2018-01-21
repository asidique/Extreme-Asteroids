#include "stdafx.h"
#include "Bullet.h"

using namespace App;

Bullet::Bullet() {};

Bullet::Bullet(float _speed, float _damage, Vector _position, Vector _direction, float _life)
{
	init(_speed, _damage);
	position = _position;
	direction = _direction;
	setLife(_life);
	fire();
}

void Bullet::init(float _speed, float _damage) {
	speed = _speed;
	damage = _damage;
	color[0] = 1.0f; color[1] = 1.0f; color[2] = 1.0f;
	position = Vector(0, 0);
	life = 2000.0f;
	exists = false;
	bulletWidth = 20.0f;
	bulletHeight = 2.0f;
	coords[0] = Vector(bulletWidth / 2.0f, bulletHeight / 2.0f);
	coords[1] = Vector(bulletWidth / 2.0f, -bulletHeight / 2.0f);
	coords[2] = Vector(-bulletWidth / 2.0f, -bulletHeight / 2.0f);
	coords[3] = Vector(-bulletWidth / 2.0f, bulletHeight / 2.0f);
}

void Bullet::fire() {
	exists = true;
	coords[0] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[0]);
	coords[1] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[1]);
	coords[2] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[2]);
	coords[3] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[3]);

}

void Bullet::fire(Vector _position, Vector _direction) {
	exists = true;
	position = _position;
	direction = _direction;
	coords[0] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[0]);
	coords[1] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[1]);
	coords[2] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[2]);
	coords[3] = Vector::rotate_point(0.0f, 0.0f, atan(direction.y / direction.x), coords[3]);

}

void Bullet::draw() {
	if (exists) {
		DrawLine(position.x + coords[0].x, position.y + coords[0].y, coords[1].x + position.x, coords[1].y + position.y, color[0], color[1], color[2]);
		DrawLine(coords[1].x + position.x, coords[1].y + position.y, coords[2].x + position.x, coords[2].y + position.y, color[0], color[1], color[2]);
		DrawLine(coords[2].x + position.x, coords[2].y + position.y, coords[3].x + position.x, coords[3].y + position.y, color[0], color[1], color[2]);
		DrawLine(coords[3].x + position.x, coords[3].y + position.y, coords[1].x + position.x, coords[1].y + position.y, color[0], color[1], color[2]);
	}
}

void Bullet::update(float deltaTime) {
	if (exists) {
		if (life < 0) {
			exists = false;
		}
		else {
			life -= deltaTime;
			position.y += direction.y * deltaTime * speed;
			position.x += direction.x * deltaTime * speed;
		}
	}
}

Vector Bullet::getPosition() {
	return position;
}

float Bullet::getWidth() {
	return bulletWidth;
}

float Bullet::getHeight() {
	return bulletHeight;
}

bool Bullet::isAlive() {
	return exists;
}

void Bullet::setLife(float _life) {
	life = _life;
}

void Bullet::setColor(float r, float g, float b) {
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

Bullet::~Bullet()
{

}
