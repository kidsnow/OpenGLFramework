#pragma once

#include "Object.h"
#include "GL/glew.h"

class Texture;

enum class RenderableType
{
	BeginEnd,
	Pointer,
	AttribPointer
};

class Renderable : public Object
{
public:
	Renderable(RenderableType type);
	virtual ~Renderable();

	void SetVertexBuffer(GLfloat* vertices) { _vertices = vertices; }
	void SetColorBuffer(GLfloat* colors) { _colors = colors; }
	void SetTexCoordBuffer(GLfloat* texCoords) { _texCoords = texCoords; }
	void SetIndexBuffer(GLuint* indices) { _indices = indices; }
	void SetVertexCount(int vertexCount) { _vertexCount = vertexCount; }
	void SetElementCount(int elementCount) { _elementCount = elementCount; }
	void BindTexture(Texture* texture) { _texture = texture; }
	void ReadyToRender();
	Texture* GetTexture() { return _texture; }

	virtual void Render();

private:
	void clearAndGenVBO();

	void pointerReady();
	void attribPointerReady();
	void beginEndRender();
	void pointerRender();
	void attribPointerRender();

protected:
	GLfloat*	_vertices;	// 3 components
	GLfloat*	_colors;	// 3 components
	GLfloat*	_texCoords;	// 2 components
	GLuint*		_indices;
	int			_vertexCount;
	int			_elementCount;
	Texture*	_texture;

private:
	RenderableType _type;
	GLuint _vao;
	GLuint _vbo[4];		// 0: vertices / 1: colors / 2: texCoords / 3: indices
};