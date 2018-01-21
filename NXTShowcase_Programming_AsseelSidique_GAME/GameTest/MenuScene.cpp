#pragma once

#include "stdafx.h"
#include "MenuScene.h"
#include <string>
#include "App\app.h"

using namespace App;

MenuScene::MenuScene() {
	isSceneRunning = true;
	musicOn = true;
	quit = false;
	mouseOn = true;
	App::PlaySoundW("Menu.wav", true);
	OnCreate();
	backgroundManagementSys = BGMS();
	backgroundManagementSys.init();
}
MenuScene::~MenuScene() {}

void MenuScene::OnCreate() {
	menuObjects.clear();
	menuObjects.push_back(new MenuObject("Difficulty", Vector(500, 200)));
	menuObjects.push_back(new MenuObject("Controls", Vector(500, 300)));
	menuObjects.push_back(new MenuObject("Quit", Vector(500, 400)));
	menuObjects.push_back(new MenuObject("Play", Vector(500, 500)));
	currentOptionSelected = 0;
	SelectOption((int)floor(currentOptionSelected));
}
void MenuScene::OnDestroy() {
	//delete backgroundMusic;
	menuObjects.clear();
	backgroundManagementSys.Clean();
}

void MenuScene::Update(float deltaTime) {
	SelectOption((int)floor(currentOptionSelected));
	r += 0.02f;
	b += 0.01f;
	b += 0.03f;
	backgroundManagementSys.update(deltaTime);
	if ((App::IsKeyPressed('W') || App::IsKeyPressed(VK_UP)) && currentOptionSelected < 3.0f) {
		currentOptionSelected += 0.1f;
	}
		
	if ((App::IsKeyPressed('S') || App::IsKeyPressed(VK_DOWN)) && currentOptionSelected > 0.2f) {
		currentOptionSelected -= 0.1f;
	}
	
	for (auto MenuObject : menuObjects) {
		MenuObject->update(deltaTime);
		if (App::IsKeyPressed(VK_SPACE) || App::IsKeyPressed(VK_RETURN)) {
			if (MenuObject->isSelected) {
				if (strcmp(MenuObject->getName(), "Play") == 0) {
					nextScene = 1;
					isSceneRunning = false;
				}
				else if (strcmp(MenuObject->getName(), "Quit") == 0) {
					quit = true;
				}
			}
		}

		if (App::IsKeyPressed('D') || App::IsKeyPressed(VK_RIGHT)) {
			for (auto MenuObject : menuObjects) {
				if (MenuObject->isSelected) {
					if (strcmp(MenuObject->getName(), "Controls") == 0) {
						mouseOn = false;
						//App::StopSound("Menu");
					}
					else if (strcmp(MenuObject->getName(), "Difficulty") == 0) {
						difficulty = true;
					}
				}
			}
		}
		else if (App::IsKeyPressed('A') || App::IsKeyPressed(VK_LEFT)) {
			for (auto MenuObject : menuObjects) {
				if (MenuObject->isSelected) {
					if (strcmp(MenuObject->getName(), "Controls") == 0) {
						mouseOn = true;
					}
					else if (strcmp(MenuObject->getName(), "Difficulty") == 0) {
						difficulty = false;
					}
				}
			}
		}
	}
}

void MenuScene::SelectOption(int a) {
	for (auto MenuObject : menuObjects) {
		MenuObject->isSelected = false;
		menuObjects.at(a)->isSelected = true;
	}
}

void MenuScene::Render() {
	backgroundManagementSys.draw();

	for (auto MenuObject : menuObjects) {
		MenuObject->draw();
	}
	//Print(50, 500, std::to_string((int)floor(currentOptionSelected)).c_str(), 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(50, 600, "MENU CONTROLS", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(50, 500, "UP/DOWN ARROWS TO NAVIGATE", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(50, 450, "LEFT/RIGHT ARROWS TO TOGGLE", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);

	Print(750, 600, "GAME CONTROLS", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(750, 500, "UP/W KEYS TO ACCELERATE", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(750, 450, "LEFT/RIGHT KEYS TO ROTATE", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(750, 400, "DOWN/S KEY TO SLOW DOWN", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(750, 350, "MOVE MOUSE TO LOOK AROUND", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(750, 300, "SPACE TO SHOOT", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);
	Print(440, 50, "Made By: Asseel Sidique", sin(r), sin(g), sin(b), GLUT_BITMAP_HELVETICA_18);
	Print(440, 25, "Music: Erick Skiff - Arpanauts", 1.0f, 1.0f, 1.0f, GLUT_BITMAP_HELVETICA_18);

	Print(1024 / 2 - 85, 700, "EXTREME ASTEROIDS", sin(r), sin(g), sin(b), GLUT_BITMAP_HELVETICA_18);
};