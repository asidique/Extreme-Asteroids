#include "stdafx.h"
#include "player.h"
#include <string>


using namespace App;

player::player() {
	init();
}

player::player(bool _mouseOn) {
	mouseOn = _mouseOn;
	init();
}

player::~player() {

}

void player::init() {}

void player::init(bool _mouseOn) {
	mouseOn = _mouseOn;
	rotationClock = false;
	position = Vector(512.0f, 350.0f);
	width = 20.0f;
	height = 25.0f;
	playerDrawCoords[0] = Vector(-width, width);
	playerDrawCoords[1] = Vector(-width, -width);
	playerDrawCoords[2] = Vector(height, 0.0f);
	speed = 0.000025f; //ADJUST TO MAKE PLAYER SMOOTHER/FASTER
	rateOfFire = 250.0f;
	rotationAngle = 0.095f;
	maxSpeed = 0.75f;
	pickupTimer = 0.0f;
	displayTimer = 2500.0f;
	lives = 3;
	flamethrower = false;
	invincible = false;
	displayText = "Start!";
	color1 = 1.0f;
	color2 = 1.0f;
	color3 = 1.0f;
}


void player::update(float deltaTime) {
	updateInput(deltaTime);
	position += velocity*deltaTime;
	CheckBoundary(1024, 768);
}


float player::getWidth() {
	return width;
}

void player::updateInput(float deltaTime) {
	direction = Vector::Normalized(Vector(playerDrawCoords[2].x, playerDrawCoords[2].y));

	//go up
	if ((App::IsKeyPressed('W') || App::IsKeyPressed(VK_UP)) && velocity.GetMagnitude() < maxSpeed) {
		velocity += speed*direction*deltaTime*deltaTime;
	}//slow down
	else if((App::IsKeyPressed('S') || App::IsKeyPressed(VK_DOWN)) && velocity.GetMagnitude() > 0) {
		velocity *= 0.94f;
	}

	//go left/right
	if (mouseOn) {
		//Get the angle between direction (player's facing) and the (mouse position - player position).normalized.
		//if the angle between the direction and mouse is > 1, subtract it.
		//If the angle is < -1 than add to it
		//!!Done
		Vector mouse;
		App::GetMousePos(mouse.x, mouse.y);
		Vector worldMousePos = mouse - position;
		worldMousePos.NormalizeThis();
		if (Vector::CrossProduct(direction, worldMousePos).z >= 0) {
			rotationClock = true; //Angle is greater than 180
		}
		else if (Vector::CrossProduct(direction, worldMousePos).z < 0) {
			rotationClock = false; //Angle is less than 180
		}
		if (acos(Vector::DotProduct(worldMousePos, direction) / (direction.GetMagnitude()*worldMousePos.GetMagnitude())) > 0.095f && rotationClock) {
			playerDrawCoords[0] = Vector::rotate_point(0.0f, 0.0f, rotationAngle, Vector(playerDrawCoords[0].x, playerDrawCoords[0].y));
			playerDrawCoords[1] = Vector::rotate_point(0.0f, 0.0f, rotationAngle, Vector(playerDrawCoords[1].x, playerDrawCoords[1].y));
			playerDrawCoords[2] = Vector::rotate_point(0.0f, 0.0f, rotationAngle, Vector(playerDrawCoords[2].x, playerDrawCoords[2].y));
		}
		else if (acos(Vector::DotProduct(worldMousePos, direction) / (direction.GetMagnitude()*worldMousePos.GetMagnitude())) > 0.095f && !rotationClock) {
			playerDrawCoords[0] = Vector::rotate_point(0.0f, 0.0f, -rotationAngle, Vector(playerDrawCoords[0].x, playerDrawCoords[0].y));
			playerDrawCoords[1] = Vector::rotate_point(0.0f, 0.0f, -rotationAngle, Vector(playerDrawCoords[1].x, playerDrawCoords[1].y));
			playerDrawCoords[2] = Vector::rotate_point(0.0f, 0.0f, -rotationAngle, Vector(playerDrawCoords[2].x, playerDrawCoords[2].y));
		}
	}
	else {
		if (App::IsKeyPressed('D') || App::IsKeyPressed(VK_RIGHT)) {
			playerDrawCoords[0] = Vector::rotate_point(0.0f, 0.0f, -rotationAngle, Vector(playerDrawCoords[0].x, playerDrawCoords[0].y));
			playerDrawCoords[1] = Vector::rotate_point(0.0f, 0.0f, -rotationAngle, Vector(playerDrawCoords[1].x, playerDrawCoords[1].y));
			playerDrawCoords[2] = Vector::rotate_point(0.0f, 0.0f, -rotationAngle, Vector(playerDrawCoords[2].x, playerDrawCoords[2].y));
		}
		else if (App::IsKeyPressed('A') || App::IsKeyPressed(VK_LEFT)) {
			playerDrawCoords[0] = Vector::rotate_point(0.0f, 0.0f, rotationAngle, Vector(playerDrawCoords[0].x, playerDrawCoords[0].y));
			playerDrawCoords[1] = Vector::rotate_point(0.0f, 0.0f, rotationAngle, Vector(playerDrawCoords[1].x, playerDrawCoords[1].y));
			playerDrawCoords[2] = Vector::rotate_point(0.0f, 0.0f, rotationAngle, Vector(playerDrawCoords[2].x, playerDrawCoords[2].y));
		}
	}
	if (displayTimer > 0) {
		displayTimer -= deltaTime;
	}

	if (pickupTimer > 0) {
		pickupTimer -= deltaTime;
		if (invincible) {
			color1 += 0.12f;
			color2 += 0.15f;
			color3 += 0.17f;
		}
	}
	else {
		setDefaultValues();
	}
	
}

void player::CheckBoundary(int _width, int _height) {
	if (position.x - width / 2.0f > _width) {
		position.x = 0 - width / 2.0f;
	}
	else if (position.x + width / 2.0f < 0) {
		position.x = _width + width / 2.0f;
	}

	if (position.y - height / 2.0f > _height) {
		position.y = 0 - height / 2.0f;
	}
	else if (position.y + height / 2.0f < 0) {
		position.y = _height + height / 2.0f;
	}
}

Vector player::getDirection() {
	return direction;
}

Vector player::getPosition() {
	return position;
}

float player::getRateOfFire() {
	return rateOfFire;
}

void player::setDefaultValues() {
	rateOfFire = 250.0f;
	invincible = false;
	flamethrower = false;
	color1 = 1.0f;
	color2 = 1.0f;
	color3 = 1.0f;
}

void player::GiveUpgrade(int type) {
	App::PlaySoundW("pickup.wav", false);
	/*
	0-Increase Rate of Fire
	1-Super Armor
	2-One Up
	3-Flamethrower
	*/
	pickupTimer = 7500.0f;
	displayTimer = 2500.0f;
	switch (type) {
	case 0:
		rateOfFire = 100.0f;
		color1 = 1.0f;
		color2 = 1.0f;
		color3 = 0.0f;
		displayText = "You Picked Up: Rapid Fire";
		break;
	case 1:
		invincible = true;
		App::PlaySoundW("star.wav", false);
		displayText = "You Picked Up: Super Armor";
		break;
	case 2:
		lives++;
		displayText = "You Picked Up: 1 Life";
		break;
	case 3:
		flamethrower = true;
		displayText = "You Picked Up: Flamethrower";
		color1 = 1.0f;
		color2 = 0.0f;
		color3 = 0.0f;
		rateOfFire = 50.0f;
		break;
	}
}

void player::draw() {
	if (displayTimer > 0) { //For round
		Print(400, 650, displayText.c_str(), 0.0f, 1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
	}
	//DRAWING PLAYER
	DrawLine(position.x + playerDrawCoords[0].x, position.y + playerDrawCoords[0].y, playerDrawCoords[1].x + position.x, playerDrawCoords[1].y + position.y, color1, color2, color3);
	DrawLine(position.x + playerDrawCoords[0].x, position.y + playerDrawCoords[0].y, playerDrawCoords[2].x + position.x, playerDrawCoords[2].y + position.y, color1, color2, color3);
	DrawLine(position.x + playerDrawCoords[1].x, position.y + playerDrawCoords[1].y, playerDrawCoords[2].x + position.x, playerDrawCoords[2].y + position.y, color1, color2, color3);
	
	//SUPER ARMOR
	if (invincible) {
		DrawLine(position.x + playerDrawCoords[0].x, position.y + playerDrawCoords[0].y, playerDrawCoords[1].x + position.x, playerDrawCoords[1].y + position.y, sin(color1), sin(color2), sin(color3));
		DrawLine(position.x + playerDrawCoords[0].x, position.y + playerDrawCoords[0].y, playerDrawCoords[2].x + position.x, playerDrawCoords[2].y + position.y, sin(color1), sin(color2), sin(color3));
		DrawLine(position.x + playerDrawCoords[1].x, position.y + playerDrawCoords[1].y, playerDrawCoords[2].x + position.x, playerDrawCoords[2].y + position.y, sin(color1), sin(color2), sin(color3));
	}
}