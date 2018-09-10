#include "TheEngine.h"
#include <iostream>
using namespace glm;

//main method
int main(){
	initializeTheEngine();

	Model boxModel = Model("PRIMITIVE_BOX");
	Entity myBox[6] = { Entity(&boxModel), Entity(&boxModel), Entity(&boxModel), Entity(&boxModel), Entity(&boxModel), Entity(&boxModel) };
	myBox[0].setPosition(vec3(0.0f, 0.0f, -1.0f));
	myBox[1].setPosition(vec3(0.0f, 0.0f, +1.0f));
	myBox[2].setPosition(vec3(0.0f, -1.0f, 0.0f));
	myBox[3].setPosition(vec3(0.0f, +1.0f, 0.0f));
	myBox[4].setPosition(vec3(-1.0f, 0.0f, 0.0f));
	myBox[5].setPosition(vec3(+1.0f, 0.0f, 0.0f));

	Scene myScene = Scene();
	int i;
	for (i = 0; i < 6; i++) myScene.addEntity(&myBox[i]);
	myScene.setCameraPosition(vec3(0.0f, 0.0f, 0.0f));
	myScene.cameraLookAt(vec3(10.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	//myBox.getPosition()

	// main loop
	while (theEngineIsRunning()){
		theEngineProcessEvents();
		theEngineRender(&myScene, 50.0f, 0.1f, 100.0f);
	}
	terminateTheEngine();
	return 0;
}