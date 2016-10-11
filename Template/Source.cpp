
#include "iostream"
#include <string>
#include <vector>
#include "My2D.h"


MyPainter2D Obj_2D;

class Box {
private:
	int center_x=75, center_y=375;
	int x_edge=50, y_edge=50;
public:
	
	void draw() {
		Obj_2D.drawLine(center_x - x_edge / 2, center_y - y_edge / 2, center_x + x_edge / 2, center_y - y_edge / 2, 1.0f, 0.0f, 0.0f);
		Obj_2D.drawLine(center_x + x_edge / 2, center_y - y_edge / 2, center_x + x_edge / 2, center_y + y_edge / 2, 1.0f, 0.0f, 0.0f);
		Obj_2D.drawLine(center_x - x_edge / 2, center_y + y_edge / 2, center_x + x_edge / 2, center_y + y_edge / 2, 1.0f, 0.0f, 0.0f);
		Obj_2D.drawLine(center_x - x_edge / 2, center_y - y_edge / 2, center_x - x_edge / 2, center_y + y_edge / 2, 1.0f, 0.0f, 0.0f);
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
					Obj_2D.drawPixel(center_x - r_radius + b, center_y - r_radius + a, red, green, blue);
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
	Obj_2D.initialize();

	while (Obj_2D.Close())
	{
		Obj_2D.preprocessing();

		std::vector<GeometricObjectInterface*> obj_list;
		obj_list.push_back(new GeomericObject<Box>);
		obj_list.push_back(new GeomericObject<Circle>);

		for (auto itr : obj_list) {
			(itr)->draw();
		}
		Obj_2D.postprocessiong();
	}
	return 0;
}