#include "TheEngine.h"

#ifndef _iostream_
#include <iostream>
#define _iostream_
#endif

#ifndef _fstream_
#include <fstream>
#define _fstream_
#endif

#ifndef _string_
#include <string>
#define _string_
#endif

#ifndef _vector_
#include <vector>
#define _vector_
#endif

#ifndef _glm_
#include <glm\glm.hpp>
#define _glm_
#endif

#ifndef _glm_matrix_transform_
#include <glm\gtc\matrix_transform.hpp>
#define _glm_matrix_transform_
#endif

#ifndef _glfw3_h_
#include <GLFW\glfw3.h>
#define _glfw3_h_
#endif

int width;
int height;
float aspectRatio;
GLFWwindow* window;
GLuint shaders;
bool glfw_initialized = false;
bool glew_initialized = false;

// Callback functions for the glfw window
void error_callback(int error, const char* description){
	std::cerr << description << "\n";
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void windowResizeCallback(GLFWwindow* newWindow, int newWidth, int newHeight){
	width = newWidth;
	height = newHeight;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}

void terminateTheEngine(){
	if (glfw_initialized){
		if(window != 0) glfwDestroyWindow(window);
		glfwTerminate();
	}
}

void initializeTheEngine(){
	// glfw initialization
	glfwSetErrorCallback(error_callback);
	if(!glfw_initialized) if (!glfwInit()) exit(EXIT_FAILURE);
	glfw_initialized = true;
	width = 680;
	height = 400;
	aspectRatio = (float)width / (float)height;
	window = glfwCreateWindow(width, height, "Mein liebes Spiel", 0, 0);
	if (!window){
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetKeyCallback(window, key_callback); // has to be replaced with input system
	glfwSetFramebufferSizeCallback(window, windowResizeCallback);
	glfwMakeContextCurrent(window); // window is current OpenGL context
	glewExperimental = GL_TRUE;
	if (!glew_initialized) if (glewInit() != GLEW_OK) exit(EXIT_FAILURE);
	glew_initialized = true;

	glClearColor(0.45f, 0.7f, 0.9f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	shaders = loadShaders("..\\shaders\\simple_vertex_shader.glsl", "..\\shaders\\simple_fragment_shader.glsl");
	glUseProgram(shaders);
}

int theEngineIsRunning(){
	return !glfwWindowShouldClose(window);
}

void theEngineRender(Scene* scene, float fov, float nearClippingRange, float farClippingRange){
	glm::mat4 pvMatrix = glm::perspective(fov, aspectRatio, nearClippingRange, farClippingRange)*scene->getViewMatrix();
	GLuint uniformPVM = glGetUniformLocation(shaders, "transform");
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int i;
	if(scene->entityCount() > 0) for (i = 0; i < scene->entityCount(); i++){
		glm::mat4 pvmMatrix = pvMatrix*(scene->getEntity(i)->getModelMatrix());
		glBindVertexArray(scene->getEntity(i)->getModel()->getVertexArray());
		glUniformMatrix4fv(uniformPVM, 1, GL_FALSE, &pvmMatrix[0][0]);
		glDrawArrays(GL_TRIANGLES, 0, scene->getEntity(i)->getModel()->triangleCount()*3);
	}
	glfwSwapBuffers(window);
}

void theEngineProcessEvents(){
	glfwPollEvents();
}

// shader loading function
GLuint loadShaders(const char * vertex_file, const char * fragment_file){
	// declare shaders
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

	// read vertex shader from file
	std::string vs_code;
	std::ifstream vs_stream(vertex_file, std::ios::in);
	if (vs_stream.is_open()){
		std::string line = "";
		while (getline(vs_stream, line)) vs_code += "\n" + line;
		vs_stream.close();
	}

	// read fragment shader from file
	std::string fs_code;
	std::ifstream fs_stream(fragment_file, std::ios::in);
	if (fs_stream.is_open()){
		std::string line = "";
		while (getline(fs_stream, line))
			fs_code += "\n" + line;
		fs_stream.close();
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	char const * vs_source = vs_code.c_str();
	glShaderSource(vs, 1, &vs_source, NULL);
	glCompileShader(vs);

	// Check Vertex Shader
	glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> vs_error(infoLogLength);
	glGetShaderInfoLog(vs, infoLogLength, NULL, &vs_error[0]);
	std::cerr << &vs_error[0] << "\n";

	// Compile Fragment Shader
	char const * fs_source = fs_code.c_str();
	glShaderSource(fs, 1, &fs_source, NULL);
	glCompileShader(fs);

	// Check Fragment Shader
	glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> fs_error(infoLogLength);
	glGetShaderInfoLog(fs, infoLogLength, NULL, &fs_error[0]);
	std::cerr << &fs_error[0] << "\n";

	// Link the program
	GLuint shaders = glCreateProgram();
	glAttachShader(shaders, vs);
	glAttachShader(shaders, fs);
	glLinkProgram(shaders);

	// Check the program
	glGetProgramiv(shaders, GL_LINK_STATUS, &result);
	glGetProgramiv(shaders, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> shaders_error(glm::max(infoLogLength, int(1)));
	glGetProgramInfoLog(shaders, infoLogLength, NULL, &shaders_error[0]);
	std::cerr << &shaders_error[0] << "\n";

	glDeleteShader(vs);
	glDeleteShader(fs);

	return shaders;
}