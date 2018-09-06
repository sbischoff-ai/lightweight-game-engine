#pragma once
#ifndef _Model_h_
#define _Model_h_

#ifndef _glew_h_
#include <glew.h>
#define _glew_h_
#endif

class Model
{
public:
	Model();
	Model(const char* keyword);
	~Model();

	int triangleCount();
	GLuint getVertexArray();

private:
	int numTriangles;
	GLfloat* vertexBufferData;
	GLfloat* colorBufferData;
	GLuint vertexArray;
	GLuint vertexBuffer;
	GLuint colorBuffer;
};

#endif // _Model_h_