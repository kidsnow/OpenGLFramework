#include "Application.h"


int main()
{
	Application* app = new VertexAttribTestApp();

	app->Run();

	delete app;

	return 0;
}