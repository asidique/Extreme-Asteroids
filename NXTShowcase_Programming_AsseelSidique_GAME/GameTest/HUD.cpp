#include "stdafx.h"
#include "HUD.h"


HUD::HUD()
{
	init();
}

void HUD::init() {
	score = 0;
	lives = 3;
	astLeft = 0;
	hearts.push_back(Heart(Vector(710, 50)));
	hearts.push_back(Heart(Vector(735, 50)));
	hearts.push_back(Heart(Vector(760, 50)));
	gameOver = false;
}

void HUD::update(float deltaTime) {
	for (auto Heart : hearts) {
		Heart.update(deltaTime);
	}
	if (lives <= 0) {
		gameOver = true;
	}
	if (displayTimer > 0) {
		displayTimer -= deltaTime;
	}
}

void HUD::loseHeart() {
	if (lives > 1) {
		lives--;
		hearts.pop_back();
	}
	else {
		App::PlaySoundW("over.wav", false);
		gameOver = true;
	}
}

void HUD::gainHeart() {
	if (lives <= 4) {
		lives++;
		hearts.push_back(Heart(Vector(710 + ((lives - 1) * 25), 50)));
	}
}

void HUD::draw() {
	for (auto Heart : hearts) {
		Heart.draw();
	}
	Print(650, 40, "LIVES:", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(290, 20, std::to_string(score).c_str() , 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(290, 40, "SCORE:", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(430, 20, std::to_string(astLeft).c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(430, 40, "ASTEROIDS LEFT:", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	if (displayTimer > 0) {
		Print(displayPosition.x, displayPosition.y, displayText.c_str(), 1.0f, 1.0f, 0.0f);
	}
}

void HUD::addScore(int _score, Vector pos) {
	score += _score;
	displayTimer = 1500.0f;
	displayText = "+" + std::to_string(_score);
	displayPosition = pos;
}

void HUD::setAsteroidsLeft(int a) {
	astLeft = a;
}

HUD::~HUD()
{
}

void HUD::Clean() {

}
