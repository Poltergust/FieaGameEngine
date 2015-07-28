// OpenGL.cpp : Defines the entry point for the application.
//

#include "pch.h"
#include "Foo.h"

const float myColor[4] = { 0.0f, 0.5f, 0.0f, 1.0f };

using namespace Library;

int WINAPI _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	// Linking between this project and the library through calling a library function
	Foo foo;

	// creating a blank OpenGL window
	if (!glfwInit())
		return -1;

	GLFWwindow * window = glfwCreateWindow(640, 480, "OpenGL Window", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit() != 0)
		return -1;

	glViewport(0, 0, 640, 480);

	while (!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, &myColor[0]);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
