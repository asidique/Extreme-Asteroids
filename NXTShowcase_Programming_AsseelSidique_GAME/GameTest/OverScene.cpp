#include "stdafx.h"
#include "OverScene.h"

OverScene::OverScene() {
}

void OverScene::OnCreate() {
	nextScene = 0;
	timer = 7500.0f;
	quit = false;
	isSceneRunning = true;
}

void OverScene::OnDestroy() {

}
void OverScene::Update(float deltaTime) {
	if (timer < 0) {
		isSceneRunning = false;
	}
	else {
		timer -= deltaTime;
	}
}


void OverScene::Render() {
	Print((1024 / 2) - 100, 450, "Back to Main Menu...Please Wait!", 1.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
	Print((1024 / 2) - 100, 400, std::to_string((int)timer/1000).c_str(), 1.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
	Print((1024 / 2) - 100, 600, "GAME OVER!", 1.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
	Print((1024 / 2) - 100, 550, "THANKS FOR PLAYING!", 1.0f, 0.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);
	Print((1024 / 2) - 100, 500, "Made By: Asseel Sidique", 1.0f, 1.0f, 0.0f, GLUT_BITMAP_HELVETICA_18);

	//Draw something nice here
}

OverScene::~OverScene() {
}
