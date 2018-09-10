#include "Scene.h"
#include "Entity.h"
#include "Model.h"

void initializeTheEngine();
void terminateTheEngine();
int theEngineIsRunning();
void theEngineRender(Scene* scene, float fov, float nearClippingRange, float farClippingRange);
void theEngineProcessEvents();

GLuint loadShaders(const char*, const char*);