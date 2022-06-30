#include "Driver.h"
#include "Car.h"
#include <iostream>
using namespace std;


Driver::Driver(Car & car,const double & b)
 : budget(b), sharedCar(car)
{ } 

void Driver::drive(double km){
	double distance = sharedCar.getDistance();
	distance += km;
	sharedCar.setDistance(distance);
	double fuellevel = sharedCar.getFuelLevel();
	fuellevel -= (0.25)*km;
	sharedCar.setFuelLevel(fuellevel);
}

void Driver::repairCar(string accident){
	double insurancefee = sharedCar.getInsurance();;
	if (accident == "SMALL"){
		budget-=50;
		cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl;
		insurancefee = insurancefee * 105/100;
		cout << "Yearly insurance fee is increased to " << insurancefee << " because of the SMALL accident" << endl;
		sharedCar.setInsurance(insurancefee);
	}
	if ( accident == "MEDIUM"){
		budget-=150;
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl;
		insurancefee = insurancefee * 110/100;
		cout << "Yearly insurance fee is increased to " << insurancefee << " because of the MEDIUM accident" << endl;
		sharedCar.setInsurance(insurancefee);
	}
	if (accident == "LARGE"){
		budget -= 300;
		cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl;
		insurancefee = insurancefee * 120/100;
		cout << "Yearly insurance fee is increased to " << insurancefee << " because of the LARGE accident" << endl;
		sharedCar.setInsurance(insurancefee);
	}	
}

void Driver::display(){
	cout << "Driver Budget: " << budget << endl;
}

void Driver::fullFuel(){
	double flevel = sharedCar.getFuelLevel();
	sharedCar.setFuelLevel(sharedCar.getMaxFuel());
	cout << "Fuel is full" << endl;
	budget -= (sharedCar.getMaxFuel()-flevel);

}