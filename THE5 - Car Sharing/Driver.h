#ifndef DRIVER_H
#define DRIVER_H
#include "Car.h"
using namespace std;

class Driver
{
private:
	Car & sharedCar;
	double budget;

public:
	Driver(Car&car,const double & budget); /*constructor for the class. */
	void drive(double km); /*. */
	void repairCar(string ); /*deletes element. */
	void display();
	void fullFuel();
};
#endif
