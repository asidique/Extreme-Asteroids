#pragma once
#include "stdafx.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "OverScene.h"
#include "App\app.h"
#include <vector>
#include <string>

using namespace App;

class SM {
	private:
		bool isRunning;
		std::vector<Scene*> scenes;

	public:
		SM();
		~SM();
		Scene *currentScene;
		void ChangeScene(int sceneNumber);
		bool isLoading = false;
		bool Initialize();
		void Update(const float deltaTime);
		void Render();
		int playState = 0;
		int sceneNumber;
		bool quit = false;
		bool musicOn = true;
		bool mouseOn = false;
		bool difficulty = false;
	};