#include <iostream>
#include "TeachersQueue.h"
#include <vector>
using namespace std;

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************
TeachersQueue::TeachersQueue(int s)
{
	queueVector = vector<teacherInfo> (s);
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;

}

//********************************************
// Function enqueue inserts the value info of the instructor *
// at the rear of the queue.                 *
//********************************************
void TeachersQueue::enqueue(teacherInfo teacher)
{
	if (isFull())
    { 
		cout << "The queue is full. " << teacher.name << " not enqueued\n";
    }
	else
	{
		// Calculate the new rear position circularly.
		rear = (rear + 1) % queueSize;
		// Insert new item.
		queueVector[rear] = teacher;
		// Update item count.
		numItems++;
	}
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into teacherInfo. *
//**********************************************
void TeachersQueue::dequeue(teacherInfo&teacher)
{
	if (isEmpty())
	{
       cout << "Attempting to dequeue on empty queue, exiting program...\n";
       exit(1);
    }
	else
	{
		// Move front.
		front = (front + 1) % queueSize;
		// Retrieve the front item.
		teacher = queueVector[front];
		// Update item count.
		numItems--;
	}
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool TeachersQueue::isEmpty() const
{
	if (numItems > 0)
		return false;
	else
		return true;	
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool TeachersQueue::isFull() const
{
	if (numItems < queueSize)
		return false;
	else
		return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void TeachersQueue::clear()
{
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}