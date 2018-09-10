#include "Scene.h"

#ifndef _glm_transform_
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#define _glm_transform_
#endif

Scene::Scene(){
	cameraPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	viewMatrix = glm::lookAt(cameraPosition, glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	entities.clear();
}

Scene::~Scene(){
}

glm::mat4 Scene::getViewMatrix(){
	return viewMatrix;
}

void Scene::setCameraPosition(glm::vec3 newCameraPosition){
	viewMatrix *= glm::translate(newCameraPosition - cameraPosition);
	cameraPosition = newCameraPosition;
}

void Scene::cameraLookAt(glm::vec3 target, glm::vec3 up){
	viewMatrix = glm::lookAt(cameraPosition, target, up);
}

void Scene::addEntity(Entity* newEntity){
	entities.push_back(newEntity);
}

Entity* Scene::getEntity(unsigned int i){
	if (i < entities.size()) return entities[i];
	return 0;
}

int Scene::entityCount(){
	return entities.size();
}