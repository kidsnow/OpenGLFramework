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
	else if (_type == RenderableType::Test)
	{
		testReady();
	}
	else if (_type == RenderableType::Test2)
	{
		test2Ready();
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
	else if (_type == RenderableType::Test)
	{
		testRender();
	}
	else if (_type == RenderableType::Test2)
	{
		test2Render();
	}
}

void Renderable::test2Ready()
{
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	//glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	//glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

void Renderable::test2Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void Renderable::testReady()
{
	// set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
	/*
	unsigned int VBO, EBO;
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
	*/

	//glGenVertexArrays(1, &_vao);
	//glBindVertexArray(_vao);

	glGenBuffers(4, _vbo);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * 4, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//glEnableVertexAttribArray(0);

	//glBindVertexArray(0);
}

void Renderable::testRender()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	/*
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	*/

	
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
	}
	if (_colors != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * _vertexCount, _colors, GL_STATIC_DRAW);
	}
	if (_texCoords != nullptr)
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * _vertexCount, _texCoords, GL_STATIC_DRAW);
	}
	if (_indices != nullptr)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * _elementCount, _indices, GL_STATIC_DRAW);
	}
}

void Renderable::attribPointerRender()
{
	//glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//glEnableVertexAttribArray(0);
	//
	////glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	////glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	////
	////glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
	////glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
	//
	//if (_indices == nullptr)
	//{
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//}
	//else
	//{
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);
	//	glDrawElements(GL_TRIANGLES, _elementCount, GL_UNSIGNED_INT, (GLvoid*)0);
	//}

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[3]);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}