#include <iostream>
#include <string>
#include "Shape.h"
#ifndef THREEDSHAPES_H
#define THREEDSHAPES_H

using namespace std;

class ThreeDShape:public shape{ /*ThreeDShape inherits shape class. */
	public:
		ThreeDShape(string name): shape(name){} /*constructor for ThreeDShape */
		/*Area and volume functions are purely virtual, perimeter function is virtual. */
		virtual float area() = 0;       
		virtual float perimeter() ;
		virtual float volume()  = 0;
};

/*Perimeter directly returns 0 for threeDShapes. */
float ThreeDShape::perimeter(){
	return 0;
}

class box:public ThreeDShape{
	public:
		box(float w, float l,float h,string name): ThreeDShape(name){ /*constructor for the box. */
			width = w;
			length = l;
			height = h;
		}
		virtual float area();
		virtual float volume();
	protected:
		float width; 
		float length;
		float height;

};

/*Area function returns float, it calculates area with 2*(width*length+width*height+length*height).*/
float box::area(){
	return 2*(width*length+width*height+length*height);
}

/*Volume function returns float, it calculates volume with width*length*height.*/
float box::volume(){
	return width*length*height;
}
#endif