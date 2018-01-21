#pragma once
#include "stdafx.h"
#include "Scene.h"
#include <string>
#include "App\app.h"

using namespace App;

class OverScene : public Scene
{
public:
	OverScene();
	~OverScene();

	void OnCreate();
	void OnDestroy();
	void Update(float deltaTime);
	void Render();

	float timer;
	int score;

};

