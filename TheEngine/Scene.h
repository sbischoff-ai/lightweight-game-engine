#pragma once
#ifndef _Scene_h_
#define _Scene_h_

class Entity;

#ifndef _glm_
#include <glm\glm.hpp>
#define _glm_
#endif

#ifndef _vector_
#include <vector>
#define _vector_
#endif

class Scene
{
public:
	Scene();
	~Scene();

	glm::mat4 getViewMatrix();
	void setCameraPosition(glm::vec3 newCameraPosition);
	void cameraLookAt(glm::vec3 lookAtPosition, glm::vec3 upDirection);
	void addEntity(Entity*);
	Entity* getEntity(unsigned int index);
	int entityCount();

private:
	std::vector<Entity*> entities;
	glm::mat4 viewMatrix;
	glm::vec3 cameraPosition;
};

#endif //_Scene_h_