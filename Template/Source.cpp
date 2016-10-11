#include <GLFW/glfw3.h>
#include "iostream"
#include <string>
#include <vector>
const int width = 640;
const int height = 480;

//color = (Red, Green, Blue)
float *pixels = new float[width * height * 3];
//float *pixels = (float*)malloc(sizeof(float)*width*height * 3);
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
class Box {
private:
	int center_x=75, center_y=375;
	int x_edge=50, y_edge=50;
public:
	
	void draw() {
		drawLine(center_x - x_edge / 2, center_y - y_edge / 2, center_x + x_edge / 2, center_y - y_edge / 2, 1.0f, 0.0f, 0.0f);
		drawLine(center_x + x_edge / 2, center_y - y_edge / 2, center_x + x_edge / 2, center_y + y_edge / 2, 1.0f, 0.0f, 0.0f);
		drawLine(center_x - x_edge / 2, center_y + y_edge / 2, center_x + x_edge / 2, center_y + y_edge / 2, 1.0f, 0.0f, 0.0f);
		drawLine(center_x - x_edge / 2, center_y - y_edge / 2, center_x - x_edge / 2, center_y + y_edge / 2, 1.0f, 0.0f, 0.0f);
	}
};

class Circle  {
private:
	int center_x=75, center_y=150;
	int r_radius=30;
	int pos_x, pos_y;
	float red = 1.0f, green = 0.0, blue = 0.0;
	double dLength;
public:
	void draw() {
		for (int a = 0; a <= 2 * r_radius; a++)
		{
			for (int b = 0; b <= 2 * r_radius; b++)
			{
				int f = (r_radius - b)*(r_radius - b) + (r_radius - a)*(r_radius - a) - r_radius*r_radius;
				if (f < 0 && -200 < f)
				{
					drawPixel(center_x - r_radius + b, center_y - r_radius + a, red, green, blue);
				}
			}
		}
	}
};

class GeometricObjectInterface {
public:
	virtual void draw()=0;
};

template <class T_OPERATION>
class GeomericObject :public GeometricObjectInterface {
public:
	void draw() {
		T_OPERATION operation;
		operation.draw();
	}
};


int main() {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		//assign all pixels red color 
		for (int j = 0; j <height; j++)
			for (int i = 0; i < width; i++) {
				pixels[(i + width*j) * 3 + 0] = 1.0f;
				pixels[(i + width*j) * 3 + 1] = 1.0f;
				pixels[(i + width*j) * 3 + 2] = 1.0f;
			}



		std::vector<GeometricObjectInterface*> obj_list;
		obj_list.push_back(new GeomericObject<Box>);
		obj_list.push_back(new GeomericObject<Circle>);

		for (auto itr : obj_list) {
			(itr)->draw();
		}
		
		


		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);


		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		std::cout << xpos << "   " << 480 - ypos << std::endl;
		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels;
	//free(pixels);
	return 0;
}