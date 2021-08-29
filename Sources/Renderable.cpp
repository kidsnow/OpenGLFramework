#include "Renderable.h"
#include "Texture.h"

Renderable::Renderable(RenderableType type) :
	_type(type),
	_vertices(nullptr),
	_colors(nullptr),
	_texCoords(nullptr),
	_indices(nullptr),
	_vertexCount(0),
	_elementCount(0),
	_texture(nullptr)
{
	for (int i = 0; i < 4; i++)
		_vbo[i] = 0;
}

Renderable::~Renderable()
{

}

//void Renderable::initializeVAO()
//{
//	glGenVertexArrays(1, &_vao);
//	glBindVertexArray(_vao);
//
//	GLuint vbo;
//	glGenBuffers(1, &vbo);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 5, _vertices, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
//
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, vbo);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}

void Renderable::clearAndGenVBO()
{
	for (int i = 0; i < 4; i++)
	{
		if (_vbo[i] != 0)
		{
			glDeleteBuffers(1, &_vbo[i]);
			_vbo[i] = 0;
		}
	}

	glGenBuffers(4, _vbo);
}

void Renderable::ReadyToRender()
{
	if (_type == RenderableType::BeginEnd)
	{
		// nothing to do.
	}
	else if (_type == RenderableType::Pointer)
	{
		pointerReady();
	}
	else if (_type == RenderableType::AttribPointer)
	{
		attribPointerReady();
	}
}

void Renderable::Render()
{
	if (_texture != nullptr)
	{
		_texture->Render();
	}

	if (_type == RenderableType::BeginEnd)
	{
		beginEndRender();
	}
	else if (_type == RenderableType::Pointer)
	{
		pointerRender();
	}
	else if (_type == RenderableType::AttribPointer)
	{
		attribPointerRender();
	}
}

void Renderable::beginEndRender()
{
	if (_indices != nullptr)
		return;

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < _vertexCount; i++)
	{
		glVertex3f(_vertices[i * 3], _vertices[i * 3 + 1], _vertices[i * 3 + 2]);
	}
	glEnd();
}

void Renderable::pointerReady()
{
	clearAndGenVBO();
}

void Renderable::pointerRender()
{

}

void Renderable::attribPointerReady()
{
	clearAndGenVBO();

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	if (_vertices != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * _vertexCount, _vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
	if (_colors != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * _vertexCount, _colors, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
	}
	if (_texCoords != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * _vertexCount, _texCoords, GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
	}
	if (_indices != nullptr)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _elementCount, _indices, GL_STATIC_DRAW);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderable::attribPointerRender()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(_vao);

	if (_indices != nullptr)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	glBindVertexArray(0);
}