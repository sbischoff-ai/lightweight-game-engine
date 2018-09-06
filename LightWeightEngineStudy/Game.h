#pragma once
#ifndef _Game_h_
#define _Game_h_

class Scene;

#ifndef _glew_h_
#include <glew.h>
#define _glew_h_
#endif

#ifndef _glfw3_h_
#include <GLFW\glfw3.h>
#define _glfw3_h_
#endif

/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Scene.h"
#include "Model.h"
#include "Entity.h"
*/



class Game
{
public:
	Game();
	~Game();

	void initialize();
	int isRunning();
	Scene* getCurrentScene();
	bool setCurrentScene(Scene*);
	void renderCurrentScene(float fov, float nearClippingRange, float farClippingRange);
	void processEvents();

private:
	GLFWwindow* window;
	Scene* currentScene;
	bool glfw_initialized;
	bool glew_initialized;

	int width, height;
	float aspectRatio;

	GLuint loadShaders(const char*, const char*);
	GLuint shaders;
};

#endif //_Game_h_