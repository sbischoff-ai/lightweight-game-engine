#pragma once
#ifndef _Entity_h_
#define _Entity_h_

class Model;

#ifndef _glm_
#include <glm\glm.hpp>
#define _glm_
#endif

class Entity
{
public:
	Entity();
	Entity(Model* newModel);
	~Entity();

	void setPosition(glm::vec3 newPosition);
	glm::vec3 getPosition();
	glm::mat4 getModelMatrix();
	Model* getModel();

private:
	glm::mat4 translationMatrix;
	glm::vec3 position;
	glm::mat4 rotationMatrix;
	glm::mat4 scaleMatrix;
	glm::vec3 scale;
	Model* model;
};

#endif //_Model_h_