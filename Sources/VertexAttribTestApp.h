#pragma once

#include "Application.h"


class Renderable;

class VertexAttribTestApp : public Application
{
public:
	VertexAttribTestApp();
	~VertexAttribTestApp();

	virtual void Update();

private:
	void generateRectangleWithIndex(glm::vec2 size);
	void generateRectangleWithoutIndex(glm::vec2 size);
	void registerRectangleToRenderable();

private:
	Renderable*	_renderable;
	GLfloat*	_vertices;
	GLfloat*	_colors;
	GLfloat*	_texCoords;
	GLuint*		_indices;
	int			_vertexCount;
	int			_elementCount;
};