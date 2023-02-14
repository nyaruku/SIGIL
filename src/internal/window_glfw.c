#include "GLFW/glfw3.h"
#ifdef __MINGW32__
#include <windows.h>
#endif
static GLFWwindow* sliProgramWindow = NULL;
static int sliWindowWidth = 0;
static int sliWindowHeight = 0;

enum { false, true };
typedef int bool;
/*
@param If vsync is false, refreshRate will be used.
*/

void sliOpenWindow(int width, int height, const char* title, int fullScreen, int refreshRate, int vsync, int resizable, int borderless)
{
	if (borderless == 1) {
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	}
	// types enabling us to access WGL functionality for enabling vsync in Windows
	//#ifdef __MINGW32__
		//typedef BOOL (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int interval);
		//PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = NULL;
	//#endif

	// start up GLFW
	glfwInit();
	if (borderless == 1) {
		glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	}
	// set our OpenGL context to something that doesn't support any old-school shit
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	if (resizable == 1) {
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}
	if (resizable == 0) {
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	if (vsync == 1) {
		glfwSwapInterval(1);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
	}
	if (vsync == 0) {
		glfwSwapInterval(0);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
	}
	glGetString(GL_VERSION);
	// create our OpenGL window
	sliProgramWindow = glfwCreateWindow(width, height, title, fullScreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	glfwMakeContextCurrent(sliProgramWindow);
	if (vsync == 1) {
		glfwSwapInterval(1);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
	}
	if (vsync == 0) {
		glfwSwapInterval(0);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
	}

	// record window size
	sliWindowWidth = width;
	sliWindowHeight = height;

	// GLFW doesn't handle vsync well in all cases, so we have to go straight to WGL to do this
	//#ifdef __MINGW32__
		//wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
		//wglSwapIntervalEXT(1);
	//#endif

	// enable OpenGL debugging context if we're in a debug build
#ifdef DEBUG
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif

	if (resizable == 1) {
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}
	if (resizable == 0) {
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	}

	if (vsync == 1) {
		glfwSwapInterval(1);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
	}
	if (vsync == 0) {
		glfwSwapInterval(0);
		glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);
	}
}

void sliSetRefreshRate(int HZ, int vsync) {
	if (vsync == 1) {
		glfwSwapInterval(1);
		glfwWindowHint(GLFW_REFRESH_RATE, HZ);
	}
	if (vsync == 0) {
		glfwSwapInterval(0);
		glfwWindowHint(GLFW_REFRESH_RATE, HZ);
	}
}

void sliShowCursor(int showCursor)
{
	glfwSetInputMode(sliProgramWindow, GLFW_CURSOR, showCursor ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void sliSetWindowPos(int posX, int posY)
{
	glfwSetWindowPos(sliProgramWindow, posX, posY);
}

int sliGetWindowPosX() {
	int xpos, ypos;
	glfwGetWindowPos(sliProgramWindow, &xpos, &ypos);
	return xpos;
}

int sliGetWindowPosY() {
	int xpos, ypos;
	glfwGetWindowPos(sliProgramWindow, &xpos, &ypos);
	return ypos;
}

void sliCloseWindow()
{
	glfwDestroyWindow(sliProgramWindow);
	glfwTerminate();
	sliProgramWindow = NULL;
}

void sliSetWindowTitle(char* title) {
	glfwSetWindowTitle(sliProgramWindow, title);
}

int sliGetWindowHeight() {
	return sliWindowHeight;
}

void sliSetWindowSize(int x, int y) {
	glfwSetWindowSize(sliProgramWindow, x, y);

	// glfwSetFramebufferSizeCallback(sliProgramWindow, x, y);
	// glViewport(0, 0, x, y);
}

int sliGetWindowWidth() {
	return sliWindowWidth;
}

int sliIsWindowOpen()
{
	return sliProgramWindow != NULL;
}

int sliShouldClose()
{
	return glfwWindowShouldClose(sliProgramWindow);
}

int sliGetKey(int key)
{
	return glfwGetKey(sliProgramWindow, key) == GLFW_PRESS;
}

int sliGetMouseButton(int button)
{
	return glfwGetMouseButton(sliProgramWindow, button) == GLFW_PRESS;
}

void sliGetMousePos(int* posX, int* posY)
{
	double x, y;
	glfwGetCursorPos(sliProgramWindow, &x, &y);
	*posX = (int)x;
	*posY = sliWindowHeight - (int)y;
}

double sliGetTime()
{
	return glfwGetTime();
}

void sliPollAndSwap()
{
	glfwPollEvents();
	glfwSwapBuffers(sliProgramWindow);
}

//
// ADDITION
//

unsigned char sliOpenGLVersion() {
	return glGetString(GL_VERSION);
}