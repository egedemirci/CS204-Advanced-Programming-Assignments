#ifndef STUDENTSQUEUE_H
#define STUDENTSQUEUE_H
#include <string>
using namespace std;

struct studentInfo{ /*Struct for the student info which will be the part of the queue. */
	string function;
	string name;
	int id;
	studentInfo(string f, string n, int i){ /*parameters constructor. */
		function = f;
		name = n;
		id = i;
	}
	studentInfo(){ /*default constructor. */
		function = "NULL";
		name  = " NULL ";
		id = 0;
	}
};
struct QueueNode /*struct for the elements of the queue. */
{
	studentInfo info;
	QueueNode *next;
	QueueNode(studentInfo i, QueueNode *ptr = NULL)
	{
		info = i;
		next = ptr;
	}
};

class StudentsQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode *front;
	QueueNode *rear;	
public:
	// Constructor.
	StudentsQueue();
	~StudentsQueue(); /*destructor*/
	
	// Member functions.
	void enqueue(studentInfo);
	void dequeue(studentInfo &);
	bool isEmpty() const;     
	void clear();
};
#endif