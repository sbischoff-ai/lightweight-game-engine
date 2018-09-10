#include "Entity.h"

#ifndef _glm_transform_
#define GLM_ENABLE_EXPERIMENTAL
#include <glm\gtx\transform.hpp>
#define _glm_transform_
#endif

Entity::Entity(){
	translationMatrix = glm::mat4(1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	model = NULL;
}

Entity::Entity(Model* newModel){
	translationMatrix = glm::mat4(1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotationMatrix = glm::mat4(1.0f);
	scaleMatrix = glm::mat4(1.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	model = newModel;
}

Entity::~Entity(){
}

void Entity::setPosition(glm::vec3 newPosition){
	position = newPosition;
	translationMatrix = glm::translate(position);
}

glm::vec3 Entity::getPosition(){
	return position;
}

glm::mat4 Entity::getModelMatrix(){
	return translationMatrix*rotationMatrix*scaleMatrix;
}

Model* Entity::getModel(){
	return model;
}