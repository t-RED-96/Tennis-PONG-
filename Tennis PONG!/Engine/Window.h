#ifdef ENGINE
#pragma once

#include "stdio.h"
#include <cmath>
#include <string>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "BitBool.h"
class Window
{
public:
	Window();

	Window(GLint windowWidth, GLint windowHeight);

	Window(GLint windowWidth, GLint windowHeight, const std::string title);

	int Initialise();
	int Initialize(bool FULLSCREEN);

	GLint getBufferWidth() { return bufferWidth; }
	GLint getBufferHeight() { return bufferHeight; }

	bool ShouldClose() { return glfwWindowShouldClose(mainWindow); }

	auto& getsKeys() { return keys; }
	const unsigned char* getButtons();
	const float* getAxes();
	GLfloat getXChange();
	GLfloat getYChange();

	void pollJoystickAxes();

	void swapBuffers() { glfwSwapBuffers(mainWindow); }

	void ResetKeys();

	void CloseWindow(bool status) { if (status) glfwSetWindowShouldClose(mainWindow, GL_TRUE); }

	~Window();

private:
	GLFWwindow* mainWindow;
	std::string Title;

	GLint width, height;
	GLint bufferWidth, bufferHeight;

	BitBool<1024 /8> keys;
	BitBool<8 /8> mouseButtons;
	const float* axes;

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved;
	bool joystickFirstMoved;

	void createCallbacks();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);
	static void handleMouseButton(GLFWwindow* window, int button, int action, int mods);
	static void handleJoystickConnected(int joy, int event);
};
#endif // ENGINE

