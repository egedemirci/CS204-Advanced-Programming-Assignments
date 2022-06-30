#include <iostream>
#include <string>
#ifndef TWODSHAPES_H
#define TWODSHAPES_H

using namespace std;

class TwoDShape:public shape{ /*TwoDShape inherits shape class. */
	public:
    // Constructor for TwoDShape.
		TwoDShape(string name): shape(name){
		} 
		/*These functions are still virtual, they will be overridden. */
		virtual float area()  = 0;       	
		virtual float perimeter()  = 0;
		virtual float volume();
		
};

float TwoDShape::volume(){ /*volume should return 0 in TwoDShape. */
	return 0;
}


class rectangle:public TwoDShape{ /*TwoDShape is baseclass, rectangle is derived class. */
	public:
		rectangle(float w, float l, string name): TwoDShape(name){ /*constructor for rectangle */
			width = w;
			length = l;
		}
		virtual float area();
		virtual float perimeter();
	protected: /*width and length is protected. */
		float width; 
		float length;

};

/*Area function returns float, it calculates area with width*length.*/
float rectangle::area(){
	return width*length;
}
/*Perimeter functions returns float, it calculates perimeter with  2*(width+length) */
float rectangle::perimeter(){
	return 2*(width+length);
}
#endif