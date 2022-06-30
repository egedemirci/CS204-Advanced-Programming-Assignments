#ifndef TEACHERSQUEUE_H
#define TEACHERSQUEUE_H
#include <string>
#include <vector>
using namespace std;

struct teacherInfo{ /*node structure for the teacher's info. */
	string function;
	string name;
	int id;
	teacherInfo(string f, string n, int i){ /*constructor with parameter. */
		function = f;
		name = n;
		id = i;
	}
	teacherInfo(){ /*default constructor. */
		function = "NULL";
		name = "NULL";
		id=0; 
	}
};


class TeachersQueue
{
private:
	vector<teacherInfo> queueVector; 
	int queueSize;  //capacity of queue
	int front;
	int rear;
	int numItems;  //# of elements currently in the queue
public:
	TeachersQueue(int size);  //constructor, parameter is capacity
  	void enqueue(teacherInfo); 
  	void dequeue(teacherInfo &);
  	bool isEmpty() const; 
  	bool isFull() const;
  	void clear();  //removes all elements
};
#endif