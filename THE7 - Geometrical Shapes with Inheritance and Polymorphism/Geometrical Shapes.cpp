#include "Shape.h"
#include "TwoDShapes.h"
#include "ThreeDShapes.h"

/*getShape function works like a menu and it returns shape pointer. */
shape* getShape() {
	float width,length,height;
	string option;
	string name; /*Name will be shape's name. */
	shape*returnPtr; /*ReturnPtr will be used in polymorphism and it will be returned. */
	cout << endl << "Choose an option < 1 or 2>:" << endl;
	cout << "1. Rectangle" << endl;
	cout << "2. Box" << endl;
	cin >> option;
	/*Option input will be taken from the user. */
	while (option != "1" && option != "2"){ /*if option is not equal to 1 or 2, user will be asked again until he/she enters correct input. */
		cout << "UNAVAILABLE OPTION CHOSEN. Try again." << endl << endl;
		cout << "Choose an option <1 or 2>:" << endl;
		cout << "1. Rectangle" << endl;
		cout << "2. Box" << endl;
		cin >> option; /*take input again. */
	}
	if (option == "1"){ /*If option equals to 1, it means user chose rectangle. */
		cout << "You chose rectangle. Give it's width, length and name:" << endl;
		cin >> width >> length >> name;
		returnPtr = new rectangle(width,length,name); /*polymorphism.*/
		return returnPtr; /*return it. */
	}
	if (option == "2"){ /*same process as above but now it's for box. */
		cout << "You chose box. Give it's width, length, height and name:" << endl;
		cin >> width >> length >> height >> name;
		returnPtr = new box(width,length,height,name); /*polymorphism. */
		return returnPtr;
	}
}//getShape()

/*Rest is sample main file. */
int main()
{
	cout<<"WELCOME TO THE SHAPE COMPARISONN PROGRAM"<<endl;
	cout<<"FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY"<<endl;
	shape *shape_1, *shape_2; /* define two varibles, named shape_1 and shape_2 of the class shape.*/
	/*What should they be in order to enable proper polymorphism?*/
	char c;
	while (tolower(c = getchar())!='y')
	{
		cout<<"Defining (getting) shape 1..."<<endl;
		
		shape_1 = getShape();
		cout<<"Defining (getting) shape 2..."<<endl;
		shape_2 = getShape();
		cout<<"********************************************************************"<<endl;
		cout<<"PRINTING SHAPE_1 INFOS:"<<endl<<"Name: "<<shape_1->getName()<<", perimeter: "
			<<shape_1->perimeter()<<", area: "<<shape_1->area()<<", volume: "<<shape_1->volume()<<endl<<endl;
		cout<<"PRINTING SHAPE_2 INFOS:"<<endl<<"Name: "<<shape_2->getName()<<", perimeter: "
			<<shape_2->perimeter()<<", area: "<<shape_2->area()<<", volume: "<<shape_2->volume()<<endl;		
		bool nothingInCommon=true; // to check whether they have anything in common (perimeter, area, volume)
		if(shape_1->perimeter()==shape_2->perimeter())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same perimeter, which is: "
				<<shape_1->perimeter()<<" cm."<<endl;
		}
		if(shape_1->area()==shape_2->area())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same area, which is: "
				<<shape_1->area()<<" cm^2."<<endl;
		}
		if(shape_1->volume()==shape_2->volume())
		{
			nothingInCommon = false;
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" have the same volume, which is: "
				<<shape_1->volume()<<" cm^3."<<endl;
		}
		if (nothingInCommon)
			cout<<shape_1->getName()<<" and "<<shape_2->getName()<<" don't have anything in common."<<endl;		
		
		delete shape_1;
		delete shape_2;

		cout<<"********************************************************************"<<endl;
		cout<<"FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY"<<endl<<endl;
		cin.ignore();//flushing the buffer for remaining character(s), in order getchar() to work
  	}//while(tolower(c = getchar())!='y')
	cout<<"PROGRAM EXITING. THANKS FOR USING IT."<<endl;
	system("pause");
	return 0;
}