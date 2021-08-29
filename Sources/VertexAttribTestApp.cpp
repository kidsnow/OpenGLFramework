#include "VertexAttribTestApp.h"

#include "ShaderManager.h"
#include "Renderable.h"


VertexAttribTestApp::VertexAttribTestApp() :
	_renderable(nullptr),
	_vertices(nullptr),
	_colors(nullptr),
	_texCoords(nullptr),
	_indices(nullptr),
	_vertexCount(0),
	_elementCount(0)
{
	_renderable = new Renderable(RenderableType::AttribPointer);
	_renderable->SetPosition(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	generateRectangleWithoutIndex(glm::vec2(1.0f, 1.0f));
	registerRectangleToRenderable();
}

VertexAttribTestApp::~VertexAttribTestApp()
{

}

void VertexAttribTestApp::generateRectangleWithIndex(glm::vec2 size)
{
	_vertexCount = 4;

	_vertices = new GLfloat[12]
	{
		 size.x / 2.0f,  size.y / 2.0f, 0.0f,  // top right
		 size.x / 2.0f, -size.y / 2.0f, 0.0f,  // bottom right
		-size.x / 2.0f, -size.y / 2.0f, 0.0f,  // bottom left
		-size.x / 2.0f,  size.y / 2.0f, 0.0f   // top left 
	};

	_colors = new GLfloat[12]
	{
		0.0f, 1.0f, 0.0f,	// top right
		0.0f, 0.0f, 1.0f,	// bottom right
		0.0f, 0.0f, 0.0f,	// bottom left
		1.0f, 0.0f, 0.0f	// top left
	};

	_texCoords = new GLfloat[8]
	{
		1.0f, 1.0f,		// top right
		1.0f, 0.0f,		// bottom right
		0.0f, 0.0f,		// bottom left
		0.0f, 1.0f		// top left
	};

	_elementCount = 6;

	_indices = new GLuint[6]
	{
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};
}

void VertexAttribTestApp::generateRectangleWithoutIndex(glm::vec2 size)
{
	_vertexCount = 6;

	_vertices = new GLfloat[18]
	{
		 size.x / 2.0f,  size.y / 2.0f, 0.0f,  // top right
		 size.x / 2.0f, -size.y / 2.0f, 0.0f,  // bottom right
		-size.x / 2.0f,  size.y / 2.0f, 0.0f,  // top left 
		 size.x / 2.0f, -size.y / 2.0f, 0.0f,  // bottom right
		-size.x / 2.0f, -size.y / 2.0f, 0.0f,  // bottom left
		-size.x / 2.0f,  size.y / 2.0f, 0.0f   // top left 
	};

	_colors = new GLfloat[18]
	{
		0.0f, 1.0f, 0.0f,	// top right
		0.0f, 0.0f, 1.0f,	// bottom right
		1.0f, 0.0f, 0.0f,	// top left
		0.0f, 0.0f, 1.0f,	// bottom right
		0.0f, 0.0f, 0.0f,	// bottom left
		1.0f, 0.0f, 0.0f	// top left
	};

	_texCoords = new GLfloat[12]
	{
		1.0f, 1.0f,		// top right
		1.0f, 0.0f,		// bottom right
		0.0f, 1.0f,		// top left
		1.0f, 0.0f,		// bottom right
		0.0f, 0.0f,		// bottom left
		0.0f, 1.0f		// top left
	};
}

void VertexAttribTestApp::registerRectangleToRenderable()
{
	_renderable->SetVertexBuffer(_vertices);
	_renderable->SetColorBuffer(_colors);
	_renderable->SetTexCoordBuffer(_texCoords);
	_renderable->SetIndexBuffer(_indices);
	_renderable->SetVertexCount(_vertexCount);
	_renderable->SetElementCount(_elementCount);
	_renderable->ReadyToRender();
}

void VertexAttribTestApp::Update()
{
	glEnable(GL_DEPTH_TEST);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//glViewport(0, 0, _window->GetWidth(), _window->GetHeight());
	glClearColor(0.4f, 0.4f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader* shader = ShaderManager::Instance()->GetShader("simple");
	shader->Use();
	//shader->SetMatrix4("MVP", GetViewProjectionMatrix() * _renderable->GetTransform());
	//glm::mat4 identity(1.0f);
	//shader->SetMatrix4("MVP", identity);

	_renderable->Render();

	return;
}