#ifndef CAR_H
#define CAR_H
#include <string>
using namespace std;

class Car
{
private:
	double distance;
	double insurancefee;
	double fuellevel;
	double maxfuellevel;
public:
	Car(double, double, double );
	void setDistance(double  dist);
	void setInsurance(double ifee);
	void setFuelLevel(double fuel);
	double getFuelLevel();
	double getMaxFuel();
	double getDistance();
	double getInsurance();
	void display();
};
#endif