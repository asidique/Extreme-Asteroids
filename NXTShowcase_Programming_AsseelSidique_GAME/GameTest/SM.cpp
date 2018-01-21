#include "stdafx.h"
#include "SM.h"

SM::SM() {
}

SM::~SM() {
	for (auto Scene : scenes) {
		Scene->OnDestroy();
		delete Scene;
	}
	scenes.clear();
	delete currentScene;
}

// Initialize and add the Menu, Game and Over Scenes here. Set the first scene number to 0 if starting the game. Set default options
bool SM::Initialize() {
	quit = false;
	musicOn = false;
	difficulty = false;
	mouseOn = true;
	scenes.clear();
	sceneNumber = 0;
	scenes.push_back(new MenuScene());
	scenes.push_back(new GameScene(difficulty));
	scenes.push_back(new OverScene());
	scenes.at(sceneNumber)->OnCreate();
	return true;
}

//Destroy the objects in the current scene, switch over to the next scene and keep all the options set
void SM::ChangeScene(int _sceneNumber) {
	if (sceneNumber == 0) {
		scenes.at(_sceneNumber)->mouseOn = scenes.at(0)->mouseOn;
	}
	scenes.at(sceneNumber)->OnDestroy();
	sceneNumber = _sceneNumber;
	quit = false;
	scenes.at(sceneNumber)->OnCreate();
	scenes.at(sceneNumber)->isSceneRunning = true;
	scenes.at(sceneNumber)->mouseOn = mouseOn;
}

//Update the scene, unless the scene is not running, else change the scene
void SM::Update(float deltaTime) {
	scenes.at(sceneNumber)->Update(deltaTime);
	quit = scenes.at(sceneNumber)->quit;
	if (scenes.at(sceneNumber)->isSceneRunning == false) {
		ChangeScene(scenes.at(sceneNumber)->nextScene);
	}

	if (quit) {
		SM::~SM();
		return;
	}
}



void SM::Render() {
	if (!quit) {
		scenes.at(sceneNumber)->Render();
	}
}


