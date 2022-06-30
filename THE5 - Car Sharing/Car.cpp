#include "Car.h"
#include <string>
#include <iostream>
using namespace std;

Car::Car(double flevel, double i_fee, double dist){
	distance = dist;
	insurancefee = i_fee;
	fuellevel = flevel;
	maxfuellevel = flevel;
}

void Car::setDistance(double dist){
	distance = dist;
}
void Car::setInsurance(double i_fee){
	insurancefee = i_fee;
}
void Car::setFuelLevel(double f_level){
	fuellevel = f_level;
}

double Car::getDistance(){
	return distance;
}
double Car::getInsurance(){
	return insurancefee;
}
double Car::getFuelLevel(){
	return fuellevel;
}

double Car::getMaxFuel(){
	return maxfuellevel;
}
void Car::display(){
	cout << "Fuel Level: " << fuellevel << endl;
	cout << "Insurance Fee: " << insurancefee << endl;
	cout << "Total distance that the car has travelled: " << distance << endl;
}