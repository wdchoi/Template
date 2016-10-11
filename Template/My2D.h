#pragma once
#pragma once
#include <GLFW/glfw3.h>
#include "iostream"
class MyPainter2D {
public:
	GLFWwindow* window;
	const int width;
	const int height;
	float *pixels;
	MyPainter2D()
		:window(nullptr), pixels(nullptr), width(640), height(480)
	{

	}
	~MyPainter2D()
	{
		std::cout << "Destructor" << std::endl;
		if (pixels != nullptr) {
			delete[] pixels;
		}
	}
	void initialize() {

		/* Initialize the library */
		if (!glfwInit()) {
			std::cout << "fdsaf" << std::endl;
			exit(1);
		}
		//return -1;

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			std::cout << "fdsaf" << std::endl;
			exit(1);
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);
		pixels = new float[width * height * 3];
	}
	void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
	{
		pixels[(i + width* j) * 3 + 0] = red;
		pixels[(i + width* j) * 3 + 1] = green;
		pixels[(i + width* j) * 3 + 2] = blue;
	}
	void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
	{
		if (i1 > i0) {
			if (j1 >= j0) {
				for (int i = i0; i <= i1; i++)
				{
					const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

					drawPixel(i, j, red, green, blue);
				}
			}
			else {
				for (int i = i0; i <= i1; i++)
				{
					const int j = j0 - (j0 - j1)*(i - i0) / (i1 - i0);

					drawPixel(i, j, red, green, blue);
				}
			}
		}
		else if (i1 < i0) {
			if (j1 >= j0) {
				for (int i = i1; i <= i0; i++)
				{
					const int j = j1 - (j1 - j0)*(i - i1) / (i0 - i1);
					drawPixel(i, j, red, green, blue);
				}
			}
			else {
				for (int i = i1; i <= i0; i++)
				{
					const int j = j1 + (j0 - j1)*(i - i1) / (i0 - i1);

					drawPixel(i, j, red, green, blue);
				}
			}
		}
		else {
			for (int j = j0; j <= j1; j++) {
				drawPixel(i0, j, 1.0f, 0.0f, 0.0f);
			}
		}
	}
	void preprocessing() {
		glClear(GL_COLOR_BUFFER_BIT);
		for (int j = 0; j <height; j++)
			for (int i = 0; i < width; i++) {
				pixels[(i + width*j) * 3 + 0] = 1.0f;
				pixels[(i + width*j) * 3 + 1] = 1.0f;
				pixels[(i + width*j) * 3 + 2] = 1.0f;
			}
	}
	void postprocessiong() {
		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	bool Close() {
		return !glfwWindowShouldClose(window);
	}
};