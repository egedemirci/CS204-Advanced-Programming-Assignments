#include <iostream>
#include <string>
#ifndef SHAPE_H
#define SHAPE_H
using namespace std;

class shape /*base class this class will be inherited. */
{
public:
    // Constructors, Destructors
	shape(){} /*default constructor for shape. */
	shape(string name){
		shapeName = name;
	}
    // Area,perimeter, volume will be used in derived classes.
	virtual float area() = 0;     /*this function is pure virtual. */     	
	virtual float perimeter() =0; /*this function is pure virtual. */     	
	virtual float volume() = 0; /*this function is pure virtual. */     	
    string getName() const /*accessor function. */
		{return shapeName;}

protected: /*shapeName taken as protected, since derived classes should access it. */
    string shapeName;

};
#endif