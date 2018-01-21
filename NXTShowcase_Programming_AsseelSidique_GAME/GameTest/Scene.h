#pragma once

class Scene {
	public:
		Scene() {};
		virtual ~Scene() {};
		int nextScene;
		virtual void OnCreate() = 0;
		virtual void OnDestroy() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;
		bool isSceneRunning;
		bool quit;
		bool musicOn;
		bool mouseOn;
};